/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "uv.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>


#define WRITES            1
#if defined(__arm__) /* Decrease the chunks so the test passes on arm CI bots */
#define CHUNKS_PER_WRITE  2048
#else
#define CHUNKS_PER_WRITE  4096
#endif

#define		CHUNK_SIZE								10024 /* 10 kb */
#define		READ_BUFFER_LENGTH						1024

#define TOTAL_BYTES       (WRITES * CHUNKS_PER_WRITE * CHUNK_SIZE)

static char* send_buffer;

static int shutdown_cb_called = 0;
static int connect_cb_called = 0;
static int write_cb_called = 0;
static int close_cb_called = 0;
static size_t bytes_sent = 0;
static size_t bytes_sent_done = 0;
static size_t bytes_received_done = 0;

static uv_connect_t connect_req;
static uv_shutdown_t shutdown_req;
static uv_write_t write_reqs[WRITES];
static FILE		*send_file = 0;
int send_buffer_length = 0;
static int				read_length = 0;
static unsigned char	read_buf[READ_BUFFER_LENGTH] = { 0, };

static void alloc_cb(uv_handle_t* handle, size_t size, uv_buf_t* buf) {
	buf->base = read_buf;
	buf->len = sizeof(read_buf);
}


static void close_cb(uv_handle_t* handle) {
	ASSERT(handle != NULL);
	close_cb_called++;
}


static void read_cb(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
	ASSERT(tcp != NULL);

	uv_shutdown_t* sreq;

	if (nread < 0) {
		/* Error or EOF */
		ASSERT(nread == UV_EOF);
		printf("read_cb() error.");
		return;
	}

	if (nread == 0) {
		/* Everything OK, but nothing read. */
		//free(buf->base);
		return;
	}

	read_length += nread;
	printf("curent read[%d] total[%d]\r\n", nread, read_length);
}


static void write_cb(uv_write_t* req, int status) {
	ASSERT(req != NULL);

	if (status) {
		fprintf(stderr, "uv_write error: %s\n", uv_strerror(status));
		ASSERT(0);
	}

	printf("write data to sever successed...\r\n");
}


static void connect_cb(uv_connect_t* req, int status) {
	uv_buf_t send_bufs[CHUNKS_PER_WRITE];
	uv_stream_t* stream;
	int i, j, r;



	ASSERT(req == &connect_req);
	ASSERT(status == 0);

	printf("connect server successed...\r\n");

	stream = req->handle;
	uv_write_t* write_req = write_reqs;
	send_bufs[0] = uv_buf_init(send_buffer, send_buffer_length);

	/* Write a lot of data */
	r = uv_write(write_req, stream, send_bufs, 1, write_cb);
	ASSERT(r == 0);

	/* Start reading */
	r = uv_read_start(stream, alloc_cb, read_cb);
	ASSERT(r == 0);
}


int main(int argc, char** argv) {
	struct sockaddr_in addr;
	uv_tcp_t client;
	int r;
	int len = 0;


	if (argc < 4) {
		printf("program parameters error.\r\n");
		printf("usage: test_libuv_tcp_client 192.168.1.67 9123 send_data.data\r\n");
		return -1;
	}
	else {
		printf("set address [%s:%s] ...\r\n",
			argv[1],
			argv[2]);
	}

	if (uv_ip4_addr(argv[1], atoi(argv[2]), &addr)) {
		printf("program parameters error. input address [%s:%s] error.\r\n",
			argv[1],
			argv[2]);
		return -1;
	}

	send_file = fopen(argv[3], "rb");
	if (!send_file) {
		printf("program parameters error. open file [%s] error.\r\n",
			argv[3]);
		return -1;
	}

	send_buffer = calloc(1, TOTAL_BYTES);
	ASSERT(send_buffer != NULL);

	len = fread(send_buffer, 1, TOTAL_BYTES, send_file);
	if (len <= 0) {
		printf("program parameters error. open file [%s] error.\r\n",
			argv[3]);
		return -1;
	}
	else {
		printf("read file [%s] length[%d].\r\n",
			argv[3],
			len);
	}
	send_buffer_length = len;

	r = uv_tcp_init(uv_default_loop(), &client);
	ASSERT(r == 0);

	r = uv_tcp_connect(&connect_req,
		&client,
		(const struct sockaddr*) &addr,
		connect_cb);
	ASSERT(r == 0);

	uv_run(uv_default_loop(), UV_RUN_DEFAULT);

	ASSERT(shutdown_cb_called == 1);
	ASSERT(connect_cb_called == 1);
	ASSERT(write_cb_called == WRITES);
	ASSERT(close_cb_called == 1);
	ASSERT(bytes_sent == TOTAL_BYTES);
	ASSERT(bytes_sent_done == TOTAL_BYTES);
	ASSERT(bytes_received_done == TOTAL_BYTES);

	free(send_buffer);

	MAKE_VALGRIND_HAPPY();
	return 0;
}
