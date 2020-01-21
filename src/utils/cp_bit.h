/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_BIT_INCLUDE_H_
#define _CP_BIT_INCLUDE_H_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B00000000 00
#define B00000001 01
#define B00000010 02
#define B00000011 03
#define B00000100 04
#define B00000101 05
#define B00000110 06
#define B00000111 07
#define B00001000 08
#define B00001001 09
#define B00001010 0A
#define B00001011 0B
#define B00001100 0C
#define B00001101 0D
#define B00001110 0E
#define B00001111 0F
#define B00010000 10
#define B00010001 11
#define B00010010 12
#define B00010011 13
#define B00010100 14
#define B00010101 15
#define B00010110 16
#define B00010111 17
#define B00011000 18
#define B00011001 19
#define B00011010 1A
#define B00011011 1B
#define B00011100 1C
#define B00011101 1D
#define B00011110 1E
#define B00011111 1F
#define B00100000 20
#define B00100001 21
#define B00100010 22
#define B00100011 23
#define B00100100 24
#define B00100101 25
#define B00100110 26
#define B00100111 27
#define B00101000 28
#define B00101001 29
#define B00101010 2A
#define B00101011 2B
#define B00101100 2C
#define B00101101 2D
#define B00101110 2E
#define B00101111 2F
#define B00110000 30
#define B00110001 31
#define B00110010 32
#define B00110011 33
#define B00110100 34
#define B00110101 35
#define B00110110 36
#define B00110111 37
#define B00111000 38
#define B00111001 39
#define B00111010 3A
#define B00111011 3B
#define B00111100 3C
#define B00111101 3D
#define B00111110 3E
#define B00111111 3F
#define B01000000 40
#define B01000001 41
#define B01000010 42
#define B01000011 43
#define B01000100 44
#define B01000101 45
#define B01000110 46
#define B01000111 47
#define B01001000 48
#define B01001001 49
#define B01001010 4A
#define B01001011 4B
#define B01001100 4C
#define B01001101 4D
#define B01001110 4E
#define B01001111 4F
#define B01010000 50
#define B01010001 51
#define B01010010 52
#define B01010011 53
#define B01010100 54
#define B01010101 55
#define B01010110 56
#define B01010111 57
#define B01011000 58
#define B01011001 59
#define B01011010 5A
#define B01011011 5B
#define B01011100 5C
#define B01011101 5D
#define B01011110 5E
#define B01011111 5F
#define B01100000 60
#define B01100001 61
#define B01100010 62
#define B01100011 63
#define B01100100 64
#define B01100101 65
#define B01100110 66
#define B01100111 67
#define B01101000 68
#define B01101001 69
#define B01101010 6A
#define B01101011 6B
#define B01101100 6C
#define B01101101 6D
#define B01101110 6E
#define B01101111 6F
#define B01110000 70
#define B01110001 71
#define B01110010 72
#define B01110011 73
#define B01110100 74
#define B01110101 75
#define B01110110 76
#define B01110111 77
#define B01111000 78
#define B01111001 79
#define B01111010 7A
#define B01111011 7B
#define B01111100 7C
#define B01111101 7D
#define B01111110 7E
#define B01111111 7F
#define B10000000 80
#define B10000001 81
#define B10000010 82
#define B10000011 83
#define B10000100 84
#define B10000101 85
#define B10000110 86
#define B10000111 87
#define B10001000 88
#define B10001001 89
#define B10001010 8A
#define B10001011 8B
#define B10001100 8C
#define B10001101 8D
#define B10001110 8E
#define B10001111 8F
#define B10010000 90
#define B10010001 91
#define B10010010 92
#define B10010011 93
#define B10010100 94
#define B10010101 95
#define B10010110 96
#define B10010111 97
#define B10011000 98
#define B10011001 99
#define B10011010 9A
#define B10011011 9B
#define B10011100 9C
#define B10011101 9D
#define B10011110 9E
#define B10011111 9F
#define B10100000 A0
#define B10100001 A1
#define B10100010 A2
#define B10100011 A3
#define B10100100 A4
#define B10100101 A5
#define B10100110 A6
#define B10100111 A7
#define B10101000 A8
#define B10101001 A9
#define B10101010 AA
#define B10101011 AB
#define B10101100 AC
#define B10101101 AD
#define B10101110 AE
#define B10101111 AF
#define B10110000 B0
#define B10110001 B1
#define B10110010 B2
#define B10110011 B3
#define B10110100 B4
#define B10110101 B5
#define B10110110 B6
#define B10110111 B7
#define B10111000 B8
#define B10111001 B9
#define B10111010 BA
#define B10111011 BB
#define B10111100 BC
#define B10111101 BD
#define B10111110 BE
#define B10111111 BF
#define B11000000 C0
#define B11000001 C1
#define B11000010 C2
#define B11000011 C3
#define B11000100 C4
#define B11000101 C5
#define B11000110 C6
#define B11000111 C7
#define B11001000 C8
#define B11001001 C9
#define B11001010 CA
#define B11001011 CB
#define B11001100 CC
#define B11001101 CD
#define B11001110 CE
#define B11001111 CF
#define B11010000 D0
#define B11010001 D1
#define B11010010 D2
#define B11010011 D3
#define B11010100 D4
#define B11010101 D5
#define B11010110 D6
#define B11010111 D7
#define B11011000 D8
#define B11011001 D9
#define B11011010 DA
#define B11011011 DB
#define B11011100 DC
#define B11011101 DD
#define B11011110 DE
#define B11011111 DF
#define B11100000 E0
#define B11100001 E1
#define B11100010 E2
#define B11100011 E3
#define B11100100 E4
#define B11100101 E5
#define B11100110 E6
#define B11100111 E7
#define B11101000 E8
#define B11101001 E9
#define B11101010 EA
#define B11101011 EB
#define B11101100 EC
#define B11101101 ED
#define B11101110 EE
#define B11101111 EF
#define B11110000 F0
#define B11110001 F1
#define B11110010 F2
#define B11110011 F3
#define B11110100 F4
#define B11110101 F5
#define B11110110 F6
#define B11110111 F7
#define B11111000 F8
#define B11111001 F9
#define B11111010 FA
#define B11111011 FB
#define B11111100 FC
#define B11111101 FD
#define B11111110 FE
#define B11111111 FF

#define __B8(B0)              0x##B0
#define _B8(B0)               __B8(B0)
#define B8(B0)                _B8(B##B0)

#define __B16(B1, B0)         0x##B1##B0
#define _B16(B1, B0)          __B16(B1, B0)
#define B16(B1, B0)           _B16(B##B1, B##B0)

#define __B32(B3, B2, B1, B0) 0x##B3##B2##B1##B0
#define _B32(B3, B2, B1, B0)  __B32(B3, B2, B1, B0)
#define B32(B3, B2, B1, B0)   _B32(B##B3, B##B2, B##B1, B##B0)


#if 0

const char * bin(unsigned int value, int width)
{
	static char binstr[33];
	int pos;

	if (width < 0 || width > 32) return NULL;

	binstr[width] = 0;
	for (pos = width - 1; pos >= 0; pos--)
	{
		binstr[pos] = (value & 0x01) ? '1' : '0';
		value >>= 1;
	}

	return binstr;
}



int main()
{
	int value8 = B8(10011001);
	int value16 = B16(10011001, 10101010);
	int value32 = B32(10011001, 10101010, 10111011, 11001100);
	int i;

	printf("0x%08X, 0b%s\n", value8, bin(value8, 8));
	printf("0x%08X, 0b%s\n", value16, bin(value16, 16));
	printf("0x%08X, 0b%s\n", value32, bin(value32, 32));

	for (i = 0; i < 256; i++)
	{
		printf("#define B%s %02X\n", bin(i, 8), i);
	}

	system("PAUSE");
	return 0;
}
#endif


#endif


