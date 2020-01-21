/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-02-11

Description:

**************************************************************************/
#include <stdlib.h>
#include "cp_daemon.h"
#include "cp_include.h"




#if defined(WIN32)
#define	CP_PID_FILE				"./configs/cp_app_pid.txt"
#else
#define	CP_PID_FILE				"./configs/cp_app_pid.txt"
#define CP_MASTER_LOG_FILE		"./configs/cp_master.log"
#endif

#define CP_MASTER_DEFAULT_BUFFER_LENGTH					512				//����Ĭ�ϵĻ����С
#define CP_MASTER_DEFAULT_FORK_TIMES					10				//�����ӽ��̵�������
#define	CP_MAX_BACKTRACE_ARRAY_NUMBER					128
#define	CP_MAX_BACKTRACE_INFORMATION_BUFFFER_LENGTH		256


//ȫ��app��������
CP_EXTERN_APP_PARAMETER();


#if defined(__linux__)
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#if defined(USED_BACKTRACE)
#include <execinfo.h> 
#endif



enum cp_signal_type_enum
{
	cp_signal_type_process_ignore = 0x01,				//���̺���
	cp_signal_type_thread_ignore = 0x02,				//�̺߳���
	cp_signal_type_process_action = 0x04,				//���̲���
};


typedef	void(*sig_handler)(int sig);

typedef struct {
	int     signo;
	int		flag;
	char   *signame;
	char   *name;
	void  (*handler)(int signo);
} cp_signal_t;




char *cp_get_exe_path_ex(char *buf, int count);
int cp_close_stdfile();
static int cp_start_server();
static void cp_worker_process(int sig);
static void cp_master_process();
static int cp_kill_worker_process();
static void cp_signal_chld(int sig);
static void cp_signal_chld_restart(int sig);
static void cp_dump(int sig);
static void cp_exit(int sig);
static void cp_general(int sig);
static int cp_sigignore(int sig);

inline int cp_save_signal(const char *file_path, int sig, const char *desri);
static int cp_write_log(const char *file_path, const char *fmt, ...);
static int cp_write_log_to_file(const char *file_path, const char *log);
static char* cp_master_snprintf(char *buf, int len, const char *fmt, ...);
static char* cp_get_time_string(char *buf, int len);
static int cp_signal(int sig, sig_handler handler);
void cp_set_rlimit_core();
void cp_set_rlimit_soft_npoc();
void cp_set_rlimit_stack();
void cp_printf_backtrace();
void cp_system_exit();
int cp_safe_strtoul(const char *str, uint32_t *out);
int cp_ignore_signal();
int cp_set_action_signal();
int cp_set_pthread_sigmask();
static int cp_save_pid(const char *pid_file);
static int cp_clear_pid(const char *pid_file);



//�����źŴ�����Ϣ
cp_signal_t m_signal_list[] = {
	{
		SIGHUP,						//Ĭ��:	��ֹ����	-	�ն���·�Ҷ�	
		cp_signal_type_process_ignore | cp_signal_type_thread_ignore,
		"SIGHUP",
		"SIGHUP",
		NULL
	},
	{
		SIGINT,						//Ĭ��:	��ֹ����	-	�жϽ���	
		cp_signal_type_process_ignore | cp_signal_type_thread_ignore,
		"SIGINT",
		"SIGINT",
		NULL
	},
	{
		SIGQUIT,					//Ĭ��:	����CORE�ļ���ֹ���̣���������core�ļ�	-		
		cp_signal_type_process_ignore | cp_signal_type_thread_ignore,
		"SIGQUIT",
		"SIGQUIT",
		NULL
	},
	{
		SIGILL,						//Ĭ��:	����CORE�ļ�	-	�Ƿ�ָ��	
		cp_signal_type_process_action,
		"SIGILL",
		"SIGILL",
		cp_dump
	},
	// 	{
	// 		SIGTRAP,					//Ĭ��:	����CORE�ļ�	-	��������	
	// 		cp_signal_type_process_action,
	// 		"SIGTRAP",
	// 		"SIGTRAP",
	// 		NULL
	// 	},
	{
		SIGBUS,						//Ĭ��:	����CORE�ļ�	-	���ߴ���	
		cp_signal_type_process_action,
		"SIGBUS",
		"SIGBUS",
		cp_dump
	},
	{
		SIGSEGV,					//Ĭ��:	����CORE�ļ�	-	�ηǷ�����	
		cp_signal_type_process_action,
		"SIGSEGV",
		"SIGSEGV",
		cp_dump
	},
	{
		SIGFPE,						//Ĭ��:	����CORE�ļ�	-	�����쳣	
		cp_signal_type_process_action,
		"SIGFPE",
		"SIGFPE",
		cp_dump
	},
	// 	{
	// 		SIGIOT,						//Ĭ��:	����CORE�ļ�	-	ִ��I/O����	
	// 		cp_signal_type_process_action,
	// 		"SIGIOT",
	// 		"SIGIOT",
	// 		NULL
	// 	},
	{
		SIGKILL,					//Ĭ��:	��ֹ����	-	ɱ������	
		cp_signal_type_process_action,
		"SIGKILL",
		"SIGKILL",
		cp_exit
	},
	{
		SIGPIPE,					//Ĭ��:	��ֹ����	-	��һ��û�ж����̵Ĺܵ�д����	
		cp_signal_type_process_ignore | cp_signal_type_thread_ignore,
		"SIGPIPE",
		"SIGPIPE",
		NULL
	},
#ifdef SIGALARM
		{
			SIGALARM,					//Ĭ��:	��ֹ����	-	��ʱ����ʱ	
			cp_signal_type_process_ignore | cp_signal_type_thread_ignore,
			"SIGALARM",
			"SIGALARM",
			NULL
		},
#endif
			{
				SIGTERM,					//Ĭ��:	��ֹ����	-	�����ֹ�ź�	
				cp_signal_type_process_action,
				"SIGTERM",
				"SIGTERM",
				cp_exit
			},
			{
				SIGSTOP,					//Ĭ��:	ֹͣ����	-	���ն�����ֹͣ�ź�	
				cp_signal_type_process_action,
				"SIGSTOP",
				"SIGSTOP",
				cp_dump
			},
			// 	{
			// 		SIGTSTP,					//Ĭ��:	ֹͣ����	-	�ն�����ֹͣ�ź�	
			// 		cp_signal_type_process_action,
			// 		"SIGTSTP",
			// 		"SIGTSTP",
			// 		NULL
			// 	},
			// 	{
			// 		SIGCONT,					//Ĭ��:	�����ź�	-	����ִ��һ��ֹͣ�Ľ���	
			// 		cp_signal_type_process_action,
			// 		"SIGCONT",
			// 		"SIGCONT",
			// 		NULL
			// 	},
			// 	{
			// 		SIGURG,						//Ĭ��:	�����ź�	-	I/O�����ź�	
			// 		cp_signal_type_process_action,
			// 		"SIGURG",
			// 		"SIGURG",
			// 		NULL
			// 	},
			{
				SIGIO,						//Ĭ��:	�����ź�	-	�������Ͽ��Խ���I/O	
				cp_signal_type_process_ignore | cp_signal_type_thread_ignore,
				"SIGIO",
				"SIGIO",
				NULL
			},
			{
				SIGCHLD,					//Ĭ��:	�����ź�	-	���ӽ���ֹͣ���˳�ʱ֪ͨ������	
				cp_signal_type_process_action,
				"SIGCHLD",
				"SIGCHLD",
				cp_signal_chld_restart
			},
			// 	{
			// 		SIGTTOU,					//Ĭ��:	ֹͣ����	-	��̨����д�ն�	
			// 		cp_signal_type_process_action,
			// 		"SIGTTOU",
			// 		"SIGTTOU",
			// 		NULL
			// 	},
			// 	{
			// 		SIGTTIN,					//Ĭ��:	ֹͣ����	-	��̨���̶��ն�	
			// 		cp_signal_type_process_action,
			// 		"SIGTTIN",
			// 		"SIGTTIN",
			// 		NULL
			// 	},
#ifdef SIGXGPU
				{
					SIGXGPU,					//Ĭ��:	��ֹ����	-	CPUʱ�޳�ʱ	
					cp_signal_type_process_action,
					"SIGXGPU",
					"SIGXGPU",
					cp_dump
				},
#endif
#ifdef SIGXFSZ
					{
						SIGXFSZ,					//Ĭ��:	��ֹ����	-	�ļ����ȹ���	
						cp_signal_type_process_action,
						"SIGXFSZ",
						"SIGXFSZ",
						cp_dump
					},
#endif
					// 	{
					// 		SIGWINCH,					//Ĭ��:	�����ź�	-	���ڴ�С�����仯	
					// 		cp_signal_type_process_action,
					// 		"SIGWINCH",
					// 		"SIGWINCH",
					// 		NULL
					// 	},
#ifdef SIGPROF
						{
							SIGPROF,					//Ĭ��:	��ֹ����	-	ͳ�Ʒֲ�ͼ�ü�ʱ����ʱ	
							cp_signal_type_process_ignore | cp_signal_type_thread_ignore,
							"SIGPROF",
							"SIGPROF",
							NULL
						},
#endif
						// 	{
						// 		SIGUSR1,					//Ĭ��:	��ֹ����	-	�û������ź�1	
						// 		cp_signal_type_process_action,
						// 		"SIGUSR1",
						// 		"SIGUSR1",
						// 		NULL
						// 	},
						// 	{
						// 		SIGUSR2,					//Ĭ��:	��ֹ����	-	�û������ź�2	
						// 		cp_signal_type_process_action,
						// 		"SIGUSR2",
						// 		"SIGUSR2",
						// 		NULL
						// 	},
#ifdef SIGVTALRM
							{
								SIGVTALRM,					//Ĭ��:	��ֹ����	-	�����ʱ����ʱ	
								cp_signal_type_process_ignore | cp_signal_type_thread_ignore,
								"SIGVTALRM",
								"SIGVTALRM",
								NULL
							},
#endif
};



char *cp_get_exe_path_ex(char *buf, int count)
{
	int i;
	int rslt = readlink("/proc/self/exe", buf, count - 1);
	if (rslt < 0 || (rslt >= count - 1))
	{
		return NULL;
	}

	buf[rslt] = '\0';
	for (i = rslt; i >= 0; i--)
	{
		if (buf[i] == '/')
		{
			buf[i + 1] = '\0';
			break;
		}
	}

	return buf;
}



int cp_close_stdfile()
{
	cp_int32_t  fd;




	fd = open("/dev/null", O_RDWR);
	if (fd == -1)
	{
		cp_log_printf("open(\"/dev/null\") failed");
		return -3;
	}

	if (dup2(fd, STDIN_FILENO) == -1)
	{
		cp_log_printf("dup2(STDIN) failed");
		return -4;
	}

	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		cp_log_printf("dup2(STDOUT) failed");
		return -5;
	}

#if 0
	if (dup2(fd, STDERR_FILENO) == -1)
	{
		cp_log_printf("dup2(STDERR) failed");
		return -6;
	}
#endif

	if (fd > STDERR_FILENO)
	{
		if (close(fd) == -1)
		{
			cp_log_printf("close() failed");
			return -7;
		}
	}

	return 0;
}

static int cp_start_server()
{
	return cp_general_start_app(&cp_global_app_info);
}

static void cp_worker_process(int sig)
{
	cp_global_daemon_info->work_pid = fork();
	switch (cp_global_daemon_info->work_pid)
	{
		case -1:
		{
			cp_write_log(CP_MASTER_LOG_FILE, 
				"start worker process failed!fork() failed");
			exit(EXIT_FAILURE);
		}
		break;
		case 0:
		{
			//������ӽ��̣��򴴽�server����
			cp_global_daemon_info->work_pid = getpid();

			cp_set_rlimit_core();

			cp_set_rlimit_soft_npoc();

			cp_set_rlimit_stack();

			cp_write_log(CP_MASTER_LOG_FILE, 
				"start worker process[%d] success.\r\n", cp_global_daemon_info->work_pid);

			if (0 == cp_start_server())
			{
				cp_write_log(CP_MASTER_LOG_FILE, 
					"start worker process[%d] success.\r\n", cp_global_daemon_info->work_pid);
			}
			else
			{
				cp_write_log(CP_MASTER_LOG_FILE, 
					"start worker process[%d] failed. cp_start_server() failed!", 
					cp_global_daemon_info->work_pid);
				cp_system_exit();
			}
		}
		break;
		default:
		{

		}
		break;
	}
}

static void cp_master_process()
{
	int					status;
	int					sig = 0;




	cp_log_printf("");
	cp_global_daemon_info->is_daemon = cp_true;
	cp_global_daemon_info->master_pid = fork();
	switch (cp_global_daemon_info->master_pid)
	{
		case -1:
		{
			cp_write_log(CP_MASTER_LOG_FILE, 
				"-----create master_process failed!fork() failed-----");
			exit(EXIT_FAILURE);
		}
		break;
		case 0:
		{
			cp_global_daemon_info->master_pid = getpid();
			cp_write_log(CP_MASTER_LOG_FILE, 
				"-----create master_process[%d]-----", 
				cp_global_daemon_info->master_pid);
		}
		break;
		default:
			exit(0);
	}

	if (cp_save_pid(CP_PID_FILE))
	{
		cp_write_log(CP_MASTER_LOG_FILE, 
			"start master_process[%d] failed! save pid into file error!", 
			cp_global_daemon_info->master_pid);
		exit(EXIT_FAILURE);
	}

	if (setsid() == -1)
	{
		cp_write_log(CP_MASTER_LOG_FILE, 
			"start master_process[%d] failed!setsid() failed", 
			cp_global_daemon_info->master_pid);
		exit(EXIT_FAILURE);
	}

	umask(0);

	//��������core�ļ��Ĵ�С
	cp_set_rlimit_core();

	//������󲢷�����������
	cp_set_rlimit_soft_npoc();

	//�������ջ��С������
	cp_set_rlimit_stack();

	//���Բ����ź�
	cp_ignore_signal();

	//Wait for signal indicating time to shut down.
	//�����̺߳��Ե��ź�
	cp_set_pthread_sigmask();

	//������Ҫ������ź�����
	cp_set_action_signal();

	cp_worker_process(0);

	//�ر��ļ�������
	cp_close_stdfile();

	//������������־��Ϣ
	cp_write_log(CP_MASTER_LOG_FILE, 
		"-----start master_process[%d] work_process[%d] success-----", 
		cp_global_daemon_info->master_pid, 
		cp_global_daemon_info->work_pid);

	while (1)
	{
		//�ȴ��ӽ����жϻ���ֹ���ͷ��ӽ�����Դ�������������ӽ��̻��ɽ�ʬ����
		waitpid(-1, &status, 0);

		cp_log_printf("parent wake up");
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 0)
			{
				cp_log_printf("parent wake up EXIT, status[%d]", status);
				//exit(0);
			}
		}

		//����ӽ���������ĳ���ź��˳��ģ�������ź�
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			switch (sig)
			{
				case SIGKILL:
				{
					cp_log_printf("parent wake up SIGKILL");
				}
				break;
				case SIGINT:
				case SIGTERM:
				{
					cp_log_printf("parent wake up SIGTERM");
				}
				break;
				default:
				{
					cp_log_printf("parent wake up signed[%d]", sig);
				}
				break;
			}
		}

		cp_sleep_msec(200);
	}
}


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_kill_worker_process
*
* ����ȫ��: cp_kill_worker_process
*
* ��������: public static 
*
* ����˵��: ��ֹ��������
*
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-30 17:39:39
********************************************************************************/
static int cp_kill_worker_process()
{
	if (cp_global_daemon_info->work_pid > 0)
	{
		if (kill(cp_global_daemon_info->work_pid, SIGKILL) < 0)
		{
			cp_write_log(CP_MASTER_LOG_FILE, 
				"send signal[SIGKILL] to work_process[%d] success", 
				cp_global_daemon_info->work_pid);
			return 0;
		}
	}

	cp_write_log(CP_MASTER_LOG_FILE, 
		"send signal[SIGKILL] to work_process[%d] failed", 
		cp_global_daemon_info->work_pid);

	return -1;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_get_executable_path
*
* ����ȫ��: cp_get_executable_path
*
* ��������: public 
*
* ����˵��: ��ȡ��������·��
*
* ��    ��: char * buf						[in/out]����˵��
* ��    ��: size_t len						[in/out]����˵��
*
* �� �� ֵ: size_t
*          �� 0  : �ɹ�
*         С��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-28 10:18:49
********************************************************************************/
size_t cp_get_executable_path(char* buf, size_t len)
{
	int					i = 0;
	ssize_t				tmp_ret = 0;


	tmp_ret = readlink("/proc/self/exe", buf, len - 1);
	if (tmp_ret <= 0)
	{
		return tmp_ret;
	}

	//���������ڡ�/opt/css_server/css_media_server/css_server (deleted)�������
	buf[tmp_ret] = '\0';
	for (i = tmp_ret; i >= 0; i--)
	{
		if (buf[i] == '/')
		{
			break;
		}

		if (buf[i] == ' ' || buf[i] == '(')
		{
			buf[i] = '\0';
		}
	}

	return tmp_ret;
}

static void cp_signal_chld(int sig)
{  
	pid_t   pid;  
	int     stat;  

	//ѭ������waitpid���������ⲻ���ֽ�ʬ���̶������ӽ��̲������´�������
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		cp_write_log(CP_MASTER_LOG_FILE, "child %d terminated\n", pid);
	}

	cp_worker_process(0);
}  


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_signal_chld_restart
*
* ����ȫ��: cp_signal_chld_restart
*
* ��������: public static 
*
* ����˵��: �������н���
*
* ��    ��: int sig						[in/out]����˵��
*
* �� �� ֵ: void
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-28 10:36:32
********************************************************************************/
static void cp_signal_chld_restart(int sig)  
{  
	pid_t			tmp_pid = 0;  
	int				tmp_stat = 0;
	int				i = 0;
	char			tmp_buf[CP_MASTER_DEFAULT_BUFFER_LENGTH] = { 0, };
	char			tmp_command_buf[CP_MASTER_DEFAULT_BUFFER_LENGTH] = { 0, };
	size_t			tmp_size = 0;


	cp_save_signal(CP_MASTER_LOG_FILE, sig, "restart process.");

	//ѭ������waitpid���������ⲻ���ֽ�ʬ���̶������ӽ��̲������´�������
	while ((tmp_pid = waitpid(-1, &tmp_stat, WNOHANG)) > 0) {
		printf("child %d terminated\n", tmp_pid);
	}

	//������Ҫ������²����ȣ������ӽ�������ֹͣʱ
	//������������������Ҳ������
	tmp_size = cp_get_executable_path(tmp_buf, CP_MASTER_DEFAULT_BUFFER_LENGTH);
	if (tmp_size < 0)
	{
		//���������ӽ���
		cp_worker_process(0);

		cp_write_log(CP_MASTER_LOG_FILE, 
			"cp_get_executable_path() failed! return [%d]. restart work_process[%d]",
			tmp_size,
			cp_global_daemon_info->work_pid);
	}
	else
	{
		//���tmp_pid�ļ�
		if (cp_clear_pid(CP_PID_FILE))
		{
			cp_write_log(CP_MASTER_LOG_FILE, "cp_clear_pid file[%s] failed!", CP_PID_FILE);
		}
		else
		{
			cp_write_log(CP_MASTER_LOG_FILE, "cp_clear_pid file[%s] success!", CP_PID_FILE);
		}

		//ͨ��ִ��shellִ�У�ʵ��ֹͣ������ͬʱ������������
		sprintf(tmp_command_buf, "kill -9 %d; %s ;", cp_global_daemon_info->master_pid, tmp_buf);
		//sprintf(tmp_buf, "%s ;", tmp_buf);

		//���ﴴ��һ���ӽ�����ִ��tmp_command_buf����
		//�����ʵ�ַ��������������system(tmp_command_buf); ����
		for (i = 0; i < CP_MASTER_DEFAULT_FORK_TIMES; i++) {
			if((tmp_pid = fork()) < 0) {
				cp_write_log(CP_MASTER_LOG_FILE, 
					"pc_signal_chld_restart() fork() process times[%d] failed. execute command [%s] failed.",
					i,
					tmp_command_buf);
				cp_sleep_msec(1000);
				continue;
			} 

			if(tmp_pid == 0) {				
				if(execl("/bin/sh", "sh", "-c", tmp_command_buf, (char *)0) < 0) {
					cp_write_log(CP_MASTER_LOG_FILE, 
						"execute command [%s] failed. errno[%d]", 
						tmp_command_buf,
						errno,
						strerror(errno));
				}
				else {
					cp_write_log(CP_MASTER_LOG_FILE, 
						"execute command [%s] success.", 
						tmp_command_buf);
				}

				exit(EXIT_FAILURE);
			}

			break;
		}

		cp_write_log(CP_MASTER_LOG_FILE, "execute command [%s] success.", tmp_command_buf);

#if 0
		//execl("/bin/sh", "sh", "-c", tmp_command_buf, (char *)0);
		system(tmp_command_buf);
#endif
	}
} 

static void cp_dump(int sig)
{
	cp_save_signal(CP_MASTER_LOG_FILE, sig, "obtained stack frames.");

	//��ӡ��ǰ����ջ��Ϣ
	cp_printf_backtrace();

	exit(EXIT_SUCCESS);
}

static void cp_exit(int sig)
{
	cp_save_signal(CP_MASTER_LOG_FILE, sig, "-----exit process-----");
	exit(EXIT_SUCCESS);
}

static void cp_general(int sig)
{
	cp_save_signal(CP_MASTER_LOG_FILE, sig, "print information.");
}

static int cp_sigignore(int sig)
{
	struct sigaction sig_handler;

	sig_handler.sa_handler = SIG_IGN;
	sig_handler.sa_flags = 0;

	if (sigemptyset(&sig_handler.sa_mask) == -1 || sigaction(sig, &sig_handler, 0) == -1)
	{
		return -1;
	}
	return 0;
}


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_get_signal_name
*
* ����ȫ��: cp_get_signal_name
*
* ��������: public 
*
* ����˵��: ��ȡ�ź�����
*
* ��    ��: int sig						[in/out]����˵��
*
* �� �� ֵ: char*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-12-1 14:38:05
********************************************************************************/
static char* cp_get_signal_name(int sig)
{
	int				i = 0;


	for (i = 0; i < cp_ary_size(m_signal_list); i++) {
		if (sig == m_signal_list[i].signo)
		{
			return m_signal_list[i].signame;
		}
	}

	return "unknow signal";
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_save_signal
*
* ����ȫ��: cp_save_signal
*
* ��������: public 
*
* ����˵��: �����ź���Ϣ
*
* ��    ��: const char * file_path						[in/out]����˵��
* ��    ��: int sig						[in/out]����˵��
* ��    ��: const char * desri						[in/out]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-30 16:08:02
********************************************************************************/
inline int cp_save_signal(const char *file_path, int sig, const char *desri)
{
	char				*tmp_p = NULL;
	char				tmp_buf[CP_MASTER_DEFAULT_BUFFER_LENGTH] = {0, };


	tmp_p = cp_master_snprintf(tmp_buf, sizeof(tmp_buf), 
		"get signal[ %s ( %d : %s )]: %s", cp_get_signal_name(sig), sig, strsignal(sig), desri);

	//BOOST_LOG_WRITE(CP_LOG_CRITICAL, CP_CRITICAL, cp_format_std_string("%1%", %tmp_buf));

	cp_write_log(file_path, "%s", tmp_buf);

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_write_log
*
* ����ȫ��: cp_write_log
*
* ��������: public static 
*
* ����˵��: ����־��ʽ�������浽�ļ���
*
* ��    ��: const char * file_path						[in/out]����˵��
* ��    ��: const char * fmt						[in/out]����˵��
* ��    ��: ...						[in/out]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-30 15:15:06
********************************************************************************/
static int cp_write_log(const char *file_path, const char *fmt, ...)
{
	char				*tmp_p = NULL;
	int					tmp_int_return = 0;
	char				tmp_buf[CP_MASTER_DEFAULT_BUFFER_LENGTH] = {0, };
	va_list				tmp_marker;



	va_start(tmp_marker, fmt);
	tmp_int_return = /*_vsnprintf*/vsnprintf(tmp_buf, sizeof(tmp_buf), fmt, tmp_marker);
	if (tmp_int_return < 0)
	{
		tmp_buf[sizeof(tmp_buf) - 4] = '.';
		tmp_buf[sizeof(tmp_buf) - 3] = '.';
		tmp_buf[sizeof(tmp_buf) - 2] = '.';
	}
	tmp_buf[sizeof(tmp_buf) - 1] = 0;
	va_end(tmp_marker);

	//д���ļ���
	cp_write_log_to_file(file_path, tmp_buf);

	//��ӡ������
	fprintf(stderr, "%s\r\n", tmp_buf);

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_write_log_to_file
*
* ����ȫ��: cp_write_log_to_file
*
* ��������: public static 
*
* ����˵��: ����־���ݱ��浽�ļ�
*
* ��    ��: const char * file_path						[in/out]����˵��
* ��    ��: const char * log						[in/out]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-30 15:14:21
********************************************************************************/
static int cp_write_log_to_file(const char *file_path, const char *log)
{
	FILE						*tmp_fd = NULL;
	char						*tmp_p = NULL;
	char						tmp_buf[CP_MASTER_DEFAULT_BUFFER_LENGTH] = {0, };


	if (!file_path || !log)
	{
		return -1;
	}

	tmp_p = cp_get_exe_path_ex(tmp_buf, CP_MASTER_DEFAULT_BUFFER_LENGTH);
	if (!tmp_p)
	{
		fprintf(stderr, "%s get exe path error.", __FUNCTION__);
		return -1;
	}

	if (chdir(tmp_buf))
	{
		fprintf(stderr, "%s set working directory error.", __FUNCTION__);
		return -2;
	}

	if ((tmp_fd = fopen(file_path, "a+")) == NULL)
	{
		fprintf(stderr, "%s could not open the signal file %s for writing", __FUNCTION__, file_path);
		return -4;
	}

	fprintf(tmp_fd, "[%s] (pid:%d) %s\r\n", cp_get_time_string(tmp_buf, sizeof(tmp_buf)), getpid(), log);
	if (fclose(tmp_fd) == -1)
	{
		fprintf(stderr, "%s could not close the pid_file[%s]", __FUNCTION__, file_path);
		return -5;
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_master_snprintf
*
* ����ȫ��: cp_master_snprintf
*
* ��������: public static
*
* ����˵��: ��ʽ���ַ���
*
* ��    ��: char * buf						[in/out]����˵��
* ��    ��: int len						[in/out]����˵��
* ��    ��: const char * fmt						[in/out]����˵��
* ��    ��: ...						[in/out]����˵��
*
* �� �� ֵ: char*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-30 15:34:27
********************************************************************************/
static char* cp_master_snprintf(char *buf, int len, const char *fmt, ...)
{
	int					tmp_int_return = -1;
	va_list				tmp_marker;


	if (len < 4)
	{
		return buf;
	}
	cp_memset(buf, 0, len);

	va_start(tmp_marker, fmt);
	tmp_int_return = /*_vsnprintf*/vsnprintf(buf, len, fmt, tmp_marker);
	if (tmp_int_return < 0)
	{
		buf[len - 4] = '.';
		buf[len - 3] = '.';
		buf[len - 2] = '.';
	}
	buf[len - 1] = 0;
	va_end(tmp_marker);

	return buf;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_get_time_string
*
* ����ȫ��: cp_get_time_string
*
* ��������: public static
*
* ����˵��: ��ȡʱ���ַ���
*
* ��    ��: char * buf						[in/out]����˵��
* ��    ��: int len						[in/out]����˵��
*
* �� �� ֵ: char*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-30 15:24:15
********************************************************************************/
static char* cp_get_time_string(char *buf, int len)
{
	struct tm		*tmp_tm_p;
	time_t			tmp_tt;


	if (!buf || len <= 0)
	{
		return NULL;
	}
	memset(buf, 0, len);

	time(&tmp_tt);
	tmp_tm_p = localtime(&tmp_tt);

	sprintf(buf, "%4d-%02d-%02d %02d:%02d:%02d",
		tmp_tm_p->tm_year + 1900, tmp_tm_p->tm_mon + 1, tmp_tm_p->tm_mday,
		tmp_tm_p->tm_hour, tmp_tm_p->tm_min, tmp_tm_p->tm_sec);

	return buf;
}

static int cp_signal(int sig, sig_handler handler)
{
	struct sigaction sig_handler;

	sig_handler.sa_handler = handler;
	sig_handler.sa_flags = 0;

	if (sigemptyset(&sig_handler.sa_mask) == -1 || sigaction(sig, &sig_handler, 0) == -1)
	{
		return -1;
	}

	return 0;
}

//��������core�ļ��Ĵ�С
void cp_set_rlimit_core()
{
	struct rlimit rlim, rlim_new;

	if (getrlimit(RLIMIT_CORE, &rlim) == 0) {
		rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;
		if (setrlimit(RLIMIT_CORE, &rlim_new) != 0) {
			/* failed. try raising just to the old max */
			rlim_new.rlim_cur = rlim_new.rlim_max = rlim.rlim_max;
			(void)setrlimit(RLIMIT_CORE, &rlim_new);
		}
	}

	if ((getrlimit(RLIMIT_CORE, &rlim) != 0) || rlim.rlim_cur == 0) {
		cp_write_log(CP_MASTER_LOG_FILE, "failed to ensure corefile creation");
		exit(EXIT_FAILURE);
	}
}

//������󲢷�����������
void cp_set_rlimit_soft_npoc()
{
	struct rlimit rlim, rlim_new;



	if (getrlimit(RLIMIT_NPROC, &rlim) == 0) {
		rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;
		if (setrlimit(RLIMIT_NPROC, &rlim_new) != 0) {
			/* failed. try raising just to the old max */
			rlim_new.rlim_cur = rlim_new.rlim_max = rlim.rlim_max;
			(void)setrlimit(RLIMIT_NPROC, &rlim_new);
		}
	}

	if ((getrlimit(RLIMIT_NPROC, &rlim) != 0) || rlim.rlim_cur == 0) {
		cp_write_log(CP_MASTER_LOG_FILE, "failed to ensure nproc creation");
		exit(EXIT_FAILURE);
	}
}

//�������ջ��С������
void cp_set_rlimit_stack()
{
	struct rlimit rlim, rlim_new;



	if (getrlimit(RLIMIT_STACK, &rlim) == 0) {
		rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;
		if (setrlimit(RLIMIT_STACK, &rlim_new) != 0) {
			/* failed. try raising just to the old max */
			rlim_new.rlim_cur = rlim_new.rlim_max = rlim.rlim_max;
			(void)setrlimit(RLIMIT_STACK, &rlim_new);
		}
	}

	if ((getrlimit(RLIMIT_STACK, &rlim) != 0) || rlim.rlim_cur == 0) {
		cp_write_log(CP_MASTER_LOG_FILE, "failed to ensure nproc creation");
		exit(EXIT_FAILURE);
	}
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: pc_printf_backtrace
*
* ����ȫ��: pc_printf_backtrace
*
* ��������: public 
*
* ����˵��: ��ӡ�����ջ��Ϣ
*
*
* �� �� ֵ: void
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-12-4 14:51:34
********************************************************************************/
void cp_printf_backtrace()
{
#if defined(USED_BACKTRACE)
	void					*array[CP_MAX_BACKTRACE_ARRAY_NUMBER];
	char					buf[CP_MAX_BACKTRACE_INFORMATION_BUFFFER_LENGTH] = {0,};
	size_t					size = 0;
	char					**strings = NULL;
	size_t					i = 0;



	size = backtrace(array, CP_MAX_BACKTRACE_ARRAY_NUMBER);
	if (size > CP_MAX_BACKTRACE_ARRAY_NUMBER)
	{
		cp_write_log(CP_MASTER_LOG_FILE, "backtrace() failed!");
		return;
	}

	strings = backtrace_symbols(array, size);
	if (!strings)
	{
		cp_write_log(CP_MASTER_LOG_FILE, "backtrace_symbols() failed!");
		return;
	}

	for (i = 0; i < size; i++)
	{
		memset(buf, 0, CP_MAX_BACKTRACE_INFORMATION_BUFFFER_LENGTH);
		pc_sprintf(buf, "#%d  %s\r\n", i, strings[i]);
		cp_write_log(CP_MASTER_LOG_FILE, buf);
	}

	free(strings);
#endif
}

void cp_system_exit()
{
	int tmp_retval = 0;


	tmp_retval = kill(cp_global_daemon_info->master_pid, SIGKILL);
	if (tmp_retval)
	{
		cp_write_log(CP_MASTER_LOG_FILE, 
			"kill master_process[%d] failed.\r\n", cp_global_daemon_info->master_pid);
	}
	else
	{
		cp_write_log(CP_MASTER_LOG_FILE, 
			"-----kill master_process[%d] success-----", cp_global_daemon_info->master_pid);
	}

	exit(EXIT_FAILURE);
}

int cp_safe_strtoul(const char *str, uint32_t *out)
{
	char *endptr = NULL;
	unsigned long l = 0;



	assert(out);
	assert(str);
	*out = 0;
	errno = 0;

	l = strtoul(str, &endptr, 10);
	if ((errno == ERANGE) || (str == endptr))
	{
		return 0;
	}

	if (isspace((unsigned char)(*endptr)) || (*endptr == '\0' && endptr != str))
	{
		if ((long)l < 0)
		{
			/* only check for negative signs in the uncommon case when
			* the unsigned number is so big that it's negative as a
			* signed number. */
			if (strchr(str, '-') != NULL)
			{
				return 0;
			}
		}
		*out = l;
		return 1;
	}

	return 0;
}


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ignore_signal
*
* ����ȫ��: cp_ignore_signal
*
* ��������: public 
*
* ����˵��: �����̺��Ե��ź�
*
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-30 18:22:31
********************************************************************************/
int cp_ignore_signal()
{
	int				i = 0;


	for (i = 0; i < cp_ary_size(m_signal_list); i++) {
		if (m_signal_list[i].flag & cp_signal_type_process_ignore)
		{
			if (cp_sigignore(m_signal_list[i].signo) == -1) 
			{
				cp_save_signal(CP_MASTER_LOG_FILE, m_signal_list[i].signo, "process ignore failed");
			}
			else
			{
				cp_save_signal(CP_MASTER_LOG_FILE, m_signal_list[i].signo, "process ignore success");
			}
		}
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_set_action_signal
*
* ����ȫ��: cp_set_action_signal
*
* ��������: public 
*
* ����˵��: ���������ź�
*
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-12-1 11:38:44
********************************************************************************/
int cp_set_action_signal()
{
	int				i = 0;


	for (i = 0; i < cp_ary_size(m_signal_list); i++) {
		if ((m_signal_list[i].flag & cp_signal_type_process_action) && m_signal_list[i].handler)
		{
			if (signal(m_signal_list[i].signo, m_signal_list[i].handler) == SIG_ERR)
			{
				cp_save_signal(CP_MASTER_LOG_FILE, m_signal_list[i].signo, "process set action signal failed");
			}
			else
			{
				cp_save_signal(CP_MASTER_LOG_FILE, m_signal_list[i].signo, "process set action signal success");
			}
		}
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_set_pthread_sigmask
*
* ����ȫ��: cp_set_pthread_sigmask
*
* ��������: public
*
* ����˵��: �����̺߳��Ե��ź�
*
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-11-30 18:24:22
********************************************************************************/
int cp_set_pthread_sigmask()
{
	int				i = 0;
	sigset_t		tmp_wait_mask;



	sigemptyset(&tmp_wait_mask);

	for (i = 0; i < cp_ary_size(m_signal_list); i++) {
		if (m_signal_list[i].flag & cp_signal_type_thread_ignore)
		{
			sigaddset(&tmp_wait_mask, m_signal_list[i].signo);

			cp_save_signal(CP_MASTER_LOG_FILE, 
				m_signal_list[i].signo, "pthread_sigmask() ignore success");
		}
	}

	pthread_sigmask(SIG_BLOCK, &tmp_wait_mask, 0);
	sigemptyset(&tmp_wait_mask);

	return 0;
}

static int cp_save_pid(const char *pid_file)
{
	FILE						*tmp_fd = NULL;
	char						*tmp_p = NULL;
	char						tmp_buf[CP_MASTER_DEFAULT_BUFFER_LENGTH] = {0, };



	tmp_p = cp_get_exe_path_ex(tmp_buf, CP_MASTER_DEFAULT_BUFFER_LENGTH);
	if (!tmp_p)
	{
		cp_write_log(CP_MASTER_LOG_FILE, "%s get exe path error.", __FUNCTION__);
		return -1;
	}

	if (chdir(tmp_buf))
	{
		cp_write_log(CP_MASTER_LOG_FILE, "%s set working directory error.", __FUNCTION__);
		return -2;
	}

	if (access(pid_file, F_OK) == 0) 
	{
		if ((tmp_fd = fopen(pid_file, "r")) != NULL)
		{
			char buffer[CP_MASTER_DEFAULT_BUFFER_LENGTH];
			if (fgets(buffer, sizeof(buffer), tmp_fd) != NULL)
			{
				unsigned int pid;
				if (cp_safe_strtoul(buffer, &pid) && kill((pid_t)pid, 0) == 0)
				{
					cp_write_log(CP_MASTER_LOG_FILE, 
						"%s WARNING: the pid file contained the following (running) pid: %u\n", 
						__FUNCTION__,
						pid);

					fclose(tmp_fd);
					return -3;
				}
			}
			fclose(tmp_fd);
		}
	}

	if ((tmp_fd = fopen(pid_file, "w")) == NULL)
	{
		cp_write_log(CP_MASTER_LOG_FILE, 
			"%s could not open the pid_file[%s] for writing",
			__FUNCTION__,
			pid_file);

		remove(pid_file);
		return -4;
	}

	fprintf(tmp_fd,"%ld\n", (long)getpid());
	if (fclose(tmp_fd) == -1) 
	{
		cp_write_log(CP_MASTER_LOG_FILE, 
			"%s could not close the pid_file[%s]",
			__FUNCTION__,
			pid_file);

		remove(pid_file);
		return -5;
	}

	return 0;
}


static int cp_clear_pid(const char *pid_file)
{
	FILE						*tmp_fd = NULL;
	char						*tmp_p = NULL;
	char						tmp_buf[CP_MASTER_DEFAULT_BUFFER_LENGTH] = {0, };



	tmp_p = cp_get_exe_path_ex(tmp_buf, CP_MASTER_DEFAULT_BUFFER_LENGTH);
	if (!tmp_p)
	{
		cp_write_log(CP_MASTER_LOG_FILE, "%s get exe path error.", __FUNCTION__);
		return -1;
	}

	if (chdir(tmp_buf))
	{
		cp_write_log(CP_MASTER_LOG_FILE, "%s set working directory error.", __FUNCTION__);
		return -2;
	}

	//����ļ�����
	if ((tmp_fd = fopen(pid_file, "wb")) != NULL)
	{
		cp_write_log(CP_MASTER_LOG_FILE, "%s clear pid_file[%s].", __FUNCTION__, pid_file);
		fclose(tmp_fd);
	}

	return 0;
}

#endif

int windows_start()
{
	return cp_general_start_app(&cp_global_app_info);
}

int linux_start()
{
#if defined(__linux__)
	cp_global_daemon_info = (cp_daemon_info_t*)cp_malloc(cp_sizeof(cp_daemon_info_t));
	if (!cp_global_daemon_info) {
		cp_log_printf("create daemon information failed!");
		return -1;
	}
	cp_memset(cp_global_daemon_info, 0, cp_sizeof(cp_daemon_info_t));
	cp_global_daemon_info->signal_thread_cb = cp_daemon_signal_thread_cb;

	cp_master_process();
#endif

	return 0;
}

//��ʾ�ػ���ʽ����app
int cp_daemon_start_app(cp_app_info_t *app_info)
{
#if defined(WIN32)
	windows_start();
#else
	linux_start();
#endif
	return 0;
}

//��ʾ��ͨ��ʽ����app
int cp_general_start_app(cp_app_info_t *app_info)
{
	int					ret_int = 0;
	cp_app_t			*tmp_app = CP_NULL;
	char				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	cp_log_printf("-------------------------------------------%s / %s (%d)-------------------------------------------",
		app_info->name,
		cp_version_itoa(app_info->version, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
		app_info->version);

	cp_log_printf("starting app : \t%s", cp_print_app_info(app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	cp_log_printf("library info : \t%s", cp_get_format_version(tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));

	//�����豸
	tmp_app = cp_global_app_create_handle(app_info);
	if (!tmp_app) {
		cp_log_printf("create app failed! : \t%s",
			cp_print_app_info(app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}
	else {
		//����global
		cp_global_app = tmp_app;
		tmp_app->daemon_info = cp_global_daemon_info;
		CP_UPDATE_APP_APP_INFO(tmp_app, app_info);
		CP_UPDATE_APP_REGISTER_INFO(tmp_app, app_info, cp_global_app_create_handle, cp_global_app_destroy_handle);
		cp_log_printf("create app success! : \t%s",
			cp_print_app_info(app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	/*��ʼ���豸������
	*��ȡ�豸�����ļ�
	*��־ģ��
	*��ʼ��TCP/UDP��������
	*/
	ret_int = tmp_app->init(tmp_app, app_info);
	if (ret_int) {
		cp_log_printf("init app failed! : \t%s",
			cp_print_app_info(app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	else {
		cp_log_notice(tmp_app->logger, "init app success! : %s",
			cp_print_app_info(app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	ret_int = tmp_app->start(tmp_app, app_info);
	if (ret_int) {
		cp_log_fatal(tmp_app->logger, "start app failed! : %s",
			cp_print_app_info(app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -3;
	}
	else {
		cp_log_notice(tmp_app->logger, "start app success! : %s",
			cp_print_app_info(app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	while (1) {
		cp_sleep_msec(10000);
	}
	return 0;
}

//�ػ���ʽʱ���ӽ��̼���������״̬
void cp_daemon_signal_thread_cb(void *argv)
{
	cp_app_t			*tmp_app = (cp_app_t *)argv;
	char				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	cp_log_printf("start cp_app[%s]. master_process[%d]. worker process[%d].",
		cp_print_app_info(tmp_app->app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
		cp_global_daemon_info->master_pid,
		cp_global_daemon_info->work_pid);

	for (;;)
	{
#if defined(__linux__)
		if (kill(cp_global_daemon_info->master_pid, 0) < 0)
		{
			cp_app_log(fatal, tmp_app, 
				"stop cp_app[%s]. master_process[%d] is exit. worker process[%d] is exit now.",
				cp_print_app_info(tmp_app->app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				cp_global_daemon_info->master_pid,
				cp_global_daemon_info->work_pid
				);

			exit(0);
		}
#endif
		cp_sleep_msec(CP_DAEMON_SIGNAL_THREAD_SLEEP_INTERVAL_MS);
	}
}