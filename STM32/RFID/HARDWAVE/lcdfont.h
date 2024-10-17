#ifndef __OLEDFONT_H
#define __OLEDFONT_H 

struct typFNT_GB16x16
{
	unsigned char Msk[32];
	unsigned char Index[2];
};

const u8 asc2_1608[1520]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x18,0x18,0x00,0x00,
0x00,0x48,0x6C,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x24,0x24,0x24,0x7F,0x12,0x12,0x12,0x7F,0x12,0x12,0x12,0x00,0x00,
0x00,0x00,0x08,0x1C,0x2A,0x2A,0x0A,0x0C,0x18,0x28,0x28,0x2A,0x2A,0x1C,0x08,0x08,
0x00,0x00,0x00,0x22,0x25,0x15,0x15,0x15,0x2A,0x58,0x54,0x54,0x54,0x22,0x00,0x00,
0x00,0x00,0x00,0x0C,0x12,0x12,0x12,0x0A,0x76,0x25,0x29,0x11,0x91,0x6E,0x00,0x00,
0x00,0x06,0x06,0x04,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00,
0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00,
0x00,0x00,0x00,0x00,0x08,0x08,0x6B,0x1C,0x1C,0x6B,0x08,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x04,0x03,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00,
0x00,0x00,0x80,0x40,0x40,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x00,
0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,
0x00,0x00,0x00,0x08,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,
0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x20,0x20,0x10,0x08,0x04,0x42,0x7E,0x00,0x00,
0x00,0x00,0x00,0x3C,0x42,0x42,0x20,0x18,0x20,0x40,0x40,0x42,0x22,0x1C,0x00,0x00,
0x00,0x00,0x00,0x20,0x30,0x28,0x24,0x24,0x22,0x22,0x7E,0x20,0x20,0x78,0x00,0x00,
0x00,0x00,0x00,0x7E,0x02,0x02,0x02,0x1A,0x26,0x40,0x40,0x42,0x22,0x1C,0x00,0x00,
0x00,0x00,0x00,0x38,0x24,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x24,0x18,0x00,0x00,
0x00,0x00,0x00,0x7E,0x22,0x22,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00,
0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x64,0x58,0x40,0x40,0x24,0x1C,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x04,
0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00,
0x00,0x00,0x00,0x3C,0x42,0x42,0x46,0x40,0x20,0x10,0x10,0x00,0x18,0x18,0x00,0x00,
0x00,0x00,0x00,0x1C,0x22,0x5A,0x55,0x55,0x55,0x55,0x2D,0x42,0x22,0x1C,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00,
0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x1E,0x22,0x42,0x42,0x42,0x22,0x1F,0x00,0x00,
0x00,0x00,0x00,0x7C,0x42,0x42,0x01,0x01,0x01,0x01,0x01,0x42,0x22,0x1C,0x00,0x00,
0x00,0x00,0x00,0x1F,0x22,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1F,0x00,0x00,
0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x42,0x42,0x3F,0x00,0x00,
0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x02,0x02,0x07,0x00,0x00,
0x00,0x00,0x00,0x3C,0x22,0x22,0x01,0x01,0x01,0x71,0x21,0x22,0x22,0x1C,0x00,0x00,
0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,
0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,
0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x0F,
0x00,0x00,0x00,0x77,0x22,0x12,0x0A,0x0E,0x0A,0x12,0x12,0x22,0x22,0x77,0x00,0x00,
0x00,0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x7F,0x00,0x00,
0x00,0x00,0x00,0x77,0x36,0x36,0x36,0x36,0x2A,0x2A,0x2A,0x2A,0x2A,0x6B,0x00,0x00,
0x00,0x00,0x00,0xE3,0x46,0x46,0x4A,0x4A,0x52,0x52,0x52,0x62,0x62,0x47,0x00,0x00,
0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,
0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x42,0x3E,0x02,0x02,0x02,0x02,0x07,0x00,0x00,
0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x4D,0x53,0x32,0x1C,0x60,0x00,
0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x3E,0x12,0x12,0x22,0x22,0x42,0xC7,0x00,0x00,
0x00,0x00,0x00,0x7C,0x42,0x42,0x02,0x04,0x18,0x20,0x40,0x42,0x42,0x3E,0x00,0x00,
0x00,0x00,0x00,0x7F,0x49,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00,
0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,
0x00,0x00,0x00,0xE7,0x42,0x42,0x22,0x24,0x24,0x14,0x14,0x18,0x08,0x08,0x00,0x00,
0x00,0x00,0x00,0x6B,0x49,0x49,0x49,0x49,0x55,0x55,0x36,0x22,0x22,0x22,0x00,0x00,
0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00,
0x00,0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00,
0x00,0x00,0x00,0x7E,0x21,0x20,0x10,0x10,0x08,0x04,0x04,0x42,0x42,0x3F,0x00,0x00,
0x00,0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00,
0x00,0x00,0x02,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x40,0x40,
0x00,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00,
0x00,0x38,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0x00,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x78,0x44,0x42,0x42,0xFC,0x00,0x00,
0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x26,0x1A,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x02,0x02,0x02,0x44,0x38,0x00,0x00,
0x00,0x00,0x00,0x60,0x40,0x40,0x40,0x78,0x44,0x42,0x42,0x42,0x64,0xD8,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x02,0x02,0x42,0x3C,0x00,0x00,
0x00,0x00,0x00,0xF0,0x88,0x08,0x08,0x7E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x22,0x22,0x1C,0x02,0x3C,0x42,0x42,0x3C,
0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,
0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,
0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x22,0x1E,
0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x72,0x12,0x0A,0x16,0x12,0x22,0x77,0x00,0x00,
0x00,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x92,0x92,0x92,0x92,0x92,0xB7,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3B,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x26,0x42,0x42,0x42,0x22,0x1E,0x02,0x07,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x4C,0x04,0x04,0x04,0x04,0x1F,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x42,0x02,0x3C,0x40,0x42,0x3E,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3E,0x08,0x08,0x08,0x08,0x08,0x30,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x42,0x42,0x42,0x42,0x62,0xDC,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x14,0x08,0x08,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEB,0x49,0x49,0x55,0x55,0x22,0x22,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x24,0x18,0x18,0x18,0x24,0x6E,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x14,0x18,0x08,0x08,0x07,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x22,0x10,0x08,0x08,0x44,0x7E,0x00,0x00,
0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0xC0,0x00,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x00,0x06,0x08,0x08,0x08,0x08,0x08,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x06,0x00,
0x0C,0x32,0xC2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
const struct typFNT_GB16x16 codeGB_16x16[]=
{
	

0x00,0x00,0xFC,0x1F,0x84,0x10,0x84,0x10,0xF4,0x17,0x84,0x10,0x84,0x10,0xFC,0x1F,
0x04,0x10,0xE4,0x13,0x24,0x12,0x24,0x12,0xE4,0x13,0x02,0x10,0x02,0x14,0x01,0x08,"周",//0*/
0xFE,0x3F,0x40,0x00,0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x08,0x08,
0xF8,0x0F,0x10,0x00,0xF8,0x0F,0x14,0x04,0x22,0x02,0xC0,0x01,0x38,0x0E,0x07,0x70,"夏",//1*/
0x40,0x00,0x80,0x00,0xFE,0x7F,0x02,0x40,0x01,0x20,0xFC,0x1F,0x80,0x00,0x80,0x00,
0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00,"宇",//2*/

	
0x00,0x01,0x04,0x02,0x08,0x02,0xE8,0x3F,0x00,0x08,0x40,0x08,0x8F,0x04,0x08,0x05,
0x08,0x02,0x08,0x05,0x88,0x08,0x48,0x10,0x28,0x10,0x14,0x00,0xE2,0x7F,0x00,0x00,"这",//0
0xF8,0x0F,0x08,0x08,0x08,0x08,0xF8,0x0F,0x08,0x08,0x08,0x08,0xF8,0x0F,0x00,0x00,
0xFF,0x7F,0x80,0x00,0x88,0x00,0x88,0x1F,0x88,0x00,0x94,0x00,0xA2,0x00,0xC1,0x7F,"是",//1
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x7F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"一",//2
0x20,0x00,0x20,0x00,0xF0,0x0F,0x18,0x04,0x26,0x02,0xC0,0x01,0xB8,0x0E,0x87,0x70,
0x80,0x00,0xFE,0x3F,0x80,0x00,0x90,0x04,0x88,0x08,0x84,0x10,0xA2,0x20,0x40,0x00,"条",//3
0x00,0x20,0xE4,0x23,0x28,0x22,0x28,0x2A,0xA1,0x2A,0xA2,0x2A,0xA2,0x2A,0xA8,0x2A,
0xA8,0x2A,0xA4,0x2A,0xA7,0x2A,0x84,0x20,0x44,0x21,0x44,0x22,0x24,0x28,0x10,0x10,"测",//4
0x00,0x14,0x04,0x24,0x08,0x24,0x08,0x04,0xE0,0x7F,0x00,0x04,0x0F,0x04,0xE8,0x07,
0x88,0x04,0x88,0x08,0x88,0x08,0xA8,0x08,0x98,0x53,0xE8,0x50,0x40,0x60,0x00,0x40,"试",//5
0x00,0x00,0xE2,0x3F,0x04,0x02,0x04,0x02,0xC0,0x1F,0x00,0x11,0x07,0x11,0xE4,0x7F,
0x04,0x00,0x04,0x00,0xC4,0x1F,0x44,0x10,0x54,0x10,0x4C,0x10,0xC4,0x1F,0x40,0x10,"语",//6
0x10,0x00,0x10,0x00,0x08,0x00,0xF8,0x1F,0x04,0x10,0x02,0x10,0xF9,0x11,0x08,0x11,
0x08,0x11,0x08,0x11,0x08,0x11,0xF8,0x11,0x08,0x11,0x00,0x10,0x00,0x0A,0x00,0x04,"句",//7
0x00,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,
0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,"！",//8
0x40,0x00,0x80,0x00,0xFE,0x7F,0x02,0x40,0x11,0x21,0x20,0x01,0x20,0x01,0x08,0x01,
0x10,0x01,0x10,0x01,0xFF,0x7F,0x80,0x02,0x40,0x04,0x20,0x08,0x18,0x10,0x06,0x20,"实",//0
0x00,0x04,0x1F,0x04,0x10,0x0A,0x12,0x0A,0x12,0x11,0x92,0x20,0x52,0x5F,0x3E,0x00,
0x20,0x22,0x20,0x24,0xB8,0x24,0x27,0x15,0x22,0x11,0x20,0x08,0xD4,0x7F,0x08,0x00,"验",//1
0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,"二",//2
0x00,0x01,0x04,0x02,0x08,0x02,0xE8,0x3F,0x00,0x08,0x40,0x08,0x8F,0x04,0x08,0x05,
0xC4,0x1F,0x44,0x10,0xC4,0x1F,0x44,0x10,0xD4,0x1F,0x4C,0x10,0x44,0x14,0x40,0x08,"请",//0
0x00,0x00,0xE2,0x1F,0x04,0x08,0x84,0x05,0x00,0x02,0xE0,0x3F,0x27,0x22,0x24,0x22,
0xE4,0x3F,0x24,0x22,0x24,0x22,0xE4,0x3F,0x24,0x22,0x24,0x2A,0x2A,0x10,0xF1,0x7F,"通",//1
0x00,0x08,0x04,0x08,0x08,0x08,0xE8,0x7F,0x00,0x08,0x00,0x08,0x4F,0x08,0x88,0x08,
0x88,0x08,0x08,0x08,0x08,0x08,0x08,0x0A,0x08,0x04,0x14,0x00,0xE2,0x7F,0x00,0x00,"过",//2
0x80,0x00,0x80,0x00,0xFC,0x1F,0x84,0x10,0x84,0x10,0xFC,0x1F,0x80,0x00,0x80,0x00,
0xFE,0x3F,0x82,0x20,0x82,0x20,0xFE,0x3F,0x82,0x20,0x80,0x00,0x80,0x00,0x80,0x00,"串",//3
0x00,0x00,0x00,0x00,0xFC,0x1F,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x10,
0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0xFC,0x1F,0x04,0x10,0x00,0x00,"口",//4
0x00,0x00,0xE2,0x3F,0x24,0x22,0x24,0x22,0xA0,0x2F,0x20,0x22,0x27,0x22,0xE4,0x3F,
0x24,0x20,0xA4,0x2F,0xA4,0x28,0xB4,0x28,0xAC,0x2F,0x24,0x20,0x20,0x28,0x10,0x10,"调",//5
0x00,0x14,0x04,0x24,0x08,0x24,0x08,0x04,0xE0,0x7F,0x00,0x04,0x0F,0x04,0xE8,0x07,
0x88,0x04,0x88,0x08,0x88,0x08,0xA8,0x08,0x98,0x53,0xE8,0x50,0x40,0x60,0x00,0x40,"试",//6
0x00,0x04,0x3E,0x04,0x22,0x04,0x22,0x04,0x22,0x3F,0x3E,0x24,0x22,0x24,0x22,0x24,
0x3E,0x24,0x22,0x24,0x22,0x24,0x22,0x22,0x72,0x22,0x0F,0x21,0x80,0x14,0x40,0x08,"助",//7
0x00,0x08,0x00,0x1F,0xFC,0x00,0x80,0x00,0x80,0x00,0xFC,0x1F,0x80,0x00,0x80,0x00,
0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00,"手",//8
0x80,0x00,0x88,0x08,0x88,0x10,0x44,0x00,0xFC,0x3F,0x40,0x00,0x20,0x00,0xE0,0x1F,
0x50,0x10,0x90,0x10,0x88,0x08,0x08,0x05,0x04,0x02,0x02,0x05,0xC0,0x18,0x38,0x60,"发",//9
0x40,0x10,0x84,0x10,0x88,0x08,0xE8,0x3F,0x00,0x02,0x00,0x02,0x0F,0x02,0xE8,0x7F,
0x08,0x02,0x08,0x05,0x08,0x09,0x88,0x10,0x48,0x10,0x14,0x00,0xE2,0x7F,0x00,0x00,"送",//10
0x10,0x04,0x10,0x04,0xFF,0x7F,0x10,0x04,0x80,0x00,0x80,0x00,0xF8,0x0F,0x88,0x08,
0x88,0x08,0x88,0x08,0xFF,0x7F,0x40,0x01,0x20,0x02,0x10,0x04,0x0C,0x18,0x03,0x60,"英",//11
0x40,0x00,0x80,0x00,0x80,0x00,0xFF,0x7F,0x08,0x08,0x08,0x08,0x10,0x04,0x10,0x04,
0x20,0x02,0x40,0x01,0x80,0x00,0x40,0x01,0x20,0x02,0x10,0x04,0x0C,0x18,0x03,0x60,"文",//12
0x40,0x00,0x80,0x00,0xFE,0x7F,0x02,0x40,0x01,0x20,0xF8,0x07,0x00,0x02,0x00,0x01,
0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00,"字",//13
0x08,0x02,0x08,0x02,0xFC,0x7E,0x12,0x09,0xA1,0x10,0x10,0x08,0x10,0x08,0xC8,0x7F,
0x0C,0x08,0x8A,0x08,0x09,0x09,0x08,0x09,0x08,0x08,0x08,0x08,0x08,0x0A,0x08,0x04,"符",//14
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x08,0x00,0x04,0x00,0x00,0x00,"，",//0
0x08,0x08,0x10,0x08,0x10,0x04,0x00,0x00,0xFE,0x3F,0x10,0x04,0x10,0x04,0x10,0x04,
0x10,0x04,0xFF,0x7F,0x10,0x04,0x10,0x04,0x08,0x04,0x08,0x04,0x04,0x04,0x02,0x04,"并",//1
0x00,0x08,0x20,0x08,0x44,0x08,0x84,0x08,0x84,0x08,0x04,0x08,0x04,0x08,0x04,0x04,
0x04,0x04,0x04,0x04,0x24,0x02,0x14,0x0A,0x0C,0x11,0x84,0x20,0x40,0x40,0x20,0x40,"以",//2
0x00,0x00,0xFC,0x1F,0x04,0x10,0x04,0x10,0xE4,0x13,0x24,0x12,0x24,0x12,0x24,0x12,
0x24,0x12,0x24,0x12,0xE4,0x13,0x04,0x10,0x04,0x10,0xFC,0x1F,0x04,0x10,0x00,0x00,"回",//3
0x40,0x00,0x40,0x00,0x40,0x00,0xFE,0x3F,0x20,0x00,0x90,0x00,0x88,0x00,0x84,0x00,
0xFC,0x1F,0x80,0x00,0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,"车",//4
0x08,0x01,0x08,0x01,0x08,0x1F,0x88,0x10,0x5F,0x08,0xA8,0x3F,0x88,0x24,0x98,0x24,
0x8C,0x24,0x8B,0x24,0xE8,0x7F,0x08,0x0A,0x08,0x0A,0x08,0x11,0x8A,0x20,0x64,0x40,"换",//0
0x10,0x00,0x90,0x3F,0x08,0x00,0x04,0x00,0x12,0x00,0x10,0x00,0xC8,0x7F,0x0C,0x04,
0x0A,0x04,0x09,0x04,0x08,0x04,0x08,0x04,0x08,0x04,0x08,0x04,0x08,0x05,0x08,0x02,"行",//1
0x08,0x04,0x08,0x04,0x04,0x04,0xE4,0x7F,0x22,0x04,0x1F,0x04,0x88,0x3F,0x04,0x00,
0x02,0x00,0xBF,0x3F,0x82,0x20,0x80,0x20,0xB8,0x20,0x87,0x20,0x82,0x3F,0x80,0x20,"结",//5
0x00,0x00,0xFC,0x3F,0x04,0x20,0x04,0x20,0xFC,0x3F,0x04,0x00,0x04,0x0F,0xF4,0x00,
0x84,0x00,0x84,0x0F,0xF4,0x00,0x84,0x00,0x84,0x1F,0xFA,0x40,0x82,0x40,0x01,0x7F,"尾",//6

0x00,0x00,0xC4,0x1F,0x48,0x10,0x48,0x10,0xC1,0x1F,0x42,0x10,0x42,0x10,0xC8,0x1F,
0x08,0x00,0xE4,0x3F,0x27,0x25,0x24,0x25,0x24,0x25,0x24,0x25,0xF4,0x7F,0x00,0x00,"温",//0
0x00,0x00,0xE4,0x1F,0x28,0x10,0x28,0x10,0xE1,0x1F,0x22,0x10,0x22,0x10,0xE8,0x1F,
0x88,0x04,0x84,0x04,0x97,0x24,0xA4,0x14,0xC4,0x0C,0x84,0x04,0xF4,0x7F,0x00,0x00,"湿",//1
0x80,0x00,0x00,0x01,0xFC,0x7F,0x44,0x04,0x44,0x04,0xFC,0x3F,0x44,0x04,0x44,0x04,
0xC4,0x07,0x04,0x00,0xF4,0x0F,0x24,0x08,0x42,0x04,0x82,0x03,0x61,0x0C,0x1C,0x70,"度",//2
0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,"二",//3
0x04,0x00,0xFC,0x3F,0x02,0x00,0xF9,0x0F,0x00,0x00,0xFE,0x0F,0x88,0x08,0x50,0x08,
0xFE,0x0B,0x20,0x08,0xFC,0x09,0x20,0x48,0xFF,0x57,0x20,0x50,0x20,0x60,0x20,0x40,"氧",//4
0x10,0x01,0x10,0x01,0x10,0x21,0x08,0x11,0x08,0x09,0x0C,0x05,0x0C,0x03,0x0A,0x01,
0x89,0x01,0x48,0x01,0x28,0x01,0x08,0x41,0x08,0x41,0x08,0x41,0x08,0x7E,0x08,0x00,"化",//5
0x00,0x04,0x80,0x24,0x9F,0x24,0x84,0x24,0x84,0x3F,0x02,0x01,0x1E,0x01,0xD2,0x7F,
0x13,0x09,0x92,0x08,0x92,0x4A,0x52,0x2A,0x5E,0x15,0x32,0x14,0x10,0x22,0x00,0x41,"碳",//6
0x00,0x00,0xFC,0x1F,0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,0x84,0x10,0x84,0x10,
0x84,0x10,0xFC,0x1F,0x84,0x10,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,"甲",//7
0x08,0x02,0x08,0x04,0xC8,0x7F,0x68,0x40,0x3A,0x20,0x8A,0x1F,0x0A,0x00,0x09,0x00,
0xC8,0x7F,0x08,0x09,0x08,0x09,0x14,0x09,0xA4,0x48,0x82,0x48,0x42,0x70,0x21,0x00,"烷",//8
0x08,0x08,0x08,0x0A,0x29,0x0A,0x2A,0x0A,0x1A,0x11,0x08,0x11,0xBF,0x20,0x4C,0x5F,
0x1C,0x12,0x2A,0x12,0x2A,0x12,0x09,0x12,0x08,0x11,0x08,0x11,0x88,0x14,0x48,0x08,"粉",//9
0x80,0x00,0x80,0x00,0x90,0x04,0x90,0x08,0x88,0x10,0x84,0x20,0x82,0x20,0x00,0x00,
0x80,0x00,0x80,0x00,0xFC,0x1F,0x80,0x00,0x80,0x00,0x80,0x00,0xFF,0x7F,0x00,0x00,"尘",//10
0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,
0x40,0x01,0x40,0x01,0x20,0x02,0x20,0x02,0x10,0x04,0x08,0x08,0x04,0x10,0x03,0x60,"大",//11
0x08,0x00,0x08,0x00,0xFC,0x3F,0x04,0x00,0xF2,0x0F,0x01,0x00,0xFC,0x0F,0x00,0x08,
0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x50,0x00,0x50,0x00,0x60,0x00,0x40,"气",//12
0x00,0x00,0xFC,0x7F,0x04,0x00,0x04,0x01,0x04,0x01,0x04,0x01,0x04,0x01,0xF4,0x3F,
0x04,0x01,0x04,0x01,0x04,0x09,0x04,0x11,0x04,0x11,0x02,0x01,0xFA,0x7F,0x01,0x00,"压",//13
0xC0,0x1F,0x40,0x10,0x4F,0x10,0xC9,0x1F,0x09,0x00,0xE9,0x3D,0x29,0x25,0x29,0x25,
0xE9,0x3D,0x09,0x02,0xFF,0x7F,0x89,0x06,0x40,0x0A,0x20,0x12,0x18,0x62,0x00,0x02,"噪",//14
0x80,0x00,0x80,0x00,0xFF,0x7F,0x80,0x00,0xFE,0x3F,0x00,0x00,0xFC,0x1F,0x84,0x10,
0x84,0x10,0xFC,0x1F,0x04,0x00,0x04,0x00,0x04,0x00,0x02,0x00,0x02,0x00,0x01,0x00,"声",//15
0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xFC,0x1F,0x80,0x00,
0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xFF,0x7F,0x00,0x00,"土",//16
0x04,0x02,0xE4,0x3F,0x04,0x00,0xC4,0x1D,0x4F,0x15,0xC4,0x1D,0x84,0x08,0xE4,0x3F,
0x84,0x08,0xE4,0x3F,0x8C,0x08,0xF7,0x7F,0x82,0x14,0xC0,0x08,0xB0,0x12,0x80,0x61,"壤",//17
0x04,0x00,0xFC,0x3F,0x02,0x00,0xF9,0x0F,0x00,0x00,0xFE,0x0F,0x20,0x08,0x24,0x09,
0xD0,0x08,0x08,0x09,0x06,0x0A,0x20,0x48,0x24,0x51,0xD0,0x50,0x08,0x61,0x06,0x42,"氮",//18
0x00,0x04,0x80,0x24,0x1F,0x15,0xC4,0x7F,0x04,0x15,0x82,0x24,0x5E,0x44,0x92,0x20,
0x93,0x20,0x92,0x7B,0x52,0x22,0xB2,0x2A,0x1E,0x79,0x92,0x20,0x40,0x20,0x20,0x20,"磷",//19
0x08,0x00,0x88,0x3F,0xBC,0x24,0x84,0x24,0x82,0x24,0xBD,0x3F,0x88,0x24,0x88,0x24,
0xBF,0x24,0x88,0x3F,0x88,0x24,0x08,0x04,0x28,0x04,0x18,0x04,0x08,0x04,0x00,0x04,"钾",//20
0x80,0x00,0x80,0x00,0xFE,0x3F,0x80,0x00,0xF8,0x0F,0x08,0x08,0x08,0x08,0xF8,0x0F,
0x08,0x08,0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x08,0x08,0x08,0x08,0xFF,0x7F,0x00,0x00,"直",//21
0x40,0x00,0x80,0x00,0x80,0x00,0xFF,0x7F,0x00,0x00,0x08,0x08,0x08,0x10,0x04,0x24,
0x12,0x24,0x20,0x02,0x40,0x01,0x80,0x00,0x40,0x01,0x30,0x02,0x0C,0x0C,0x03,0x70,"交",//22
0x00,0x01,0x04,0x02,0xE8,0x7F,0x08,0x01,0x81,0x08,0x42,0x10,0xE2,0x3F,0x08,0x20,
0x08,0x00,0x44,0x12,0x47,0x12,0x44,0x12,0x44,0x12,0x44,0x52,0x24,0x52,0x10,0x62,"流",//23
0x80,0x00,0x80,0x00,0x80,0x00,0xFC,0x1F,0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,
0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,0x84,0x50,0x80,0x40,0x80,0x40,0x00,0x7F,"电",//24
0x06,0x00,0x89,0x2F,0x69,0x30,0x36,0x20,0x10,0x20,0x18,0x00,0x18,0x00,0x18,0x00,
0x18,0x00,0x18,0x00,0x18,0x00,0x10,0x00,0x30,0x20,0x60,0x10,0x80,0x0F,0x00,0x00,"℃",//25
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0C,0x00,0x0C,0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,"：",//26
0x00,0x00,0x18,0x20,0x24,0x10,0x24,0x08,0x24,0x04,0x24,0x02,0x24,0x01,0x98,0x00,
0x40,0x06,0x20,0x09,0x10,0x09,0x08,0x09,0x04,0x09,0x02,0x09,0x00,0x06,0x00,0x00,"％",//27
0xFF,0x7F,0x20,0x02,0xFC,0x1F,0x24,0x12,0xFC,0x1F,0x00,0x00,0xF8,0x0F,0x08,0x08,
0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,"覃",//0.
0x08,0x00,0x88,0x1F,0x08,0x08,0x3E,0x04,0x2A,0x02,0x2A,0x01,0xBE,0x3F,0x2A,0x2A,
0x2A,0x2A,0x2A,0x29,0xBE,0x24,0x2A,0x24,0x08,0x22,0x08,0x21,0x88,0x14,0x08,0x08,"畅",//1.
0x04,0x00,0xE8,0x3F,0x00,0x21,0x02,0x25,0x02,0x29,0xFA,0x2F,0x02,0x21,0x72,0x25,
0x52,0x25,0x72,0x25,0x02,0x23,0x62,0x2A,0x1A,0x2D,0x82,0x28,0x42,0x20,0x02,0x30,"阈",//0
0x10,0x02,0x10,0x02,0xF0,0x3F,0x08,0x02,0x08,0x02,0xCC,0x1F,0x4C,0x10,0xCA,0x1F,
0x49,0x10,0xC8,0x1F,0x48,0x10,0xC8,0x1F,0x48,0x10,0x48,0x10,0xF8,0x7F,0x08,0x00,"值",//1
0x00,0x00,0x84,0x0F,0x88,0x08,0x88,0x08,0x80,0x08,0x40,0x70,0x2F,0x00,0xC8,0x1F,
0x88,0x10,0x88,0x08,0x08,0x09,0x28,0x05,0x18,0x02,0x08,0x05,0xC0,0x18,0x30,0x60,"设",//2
0x40,0x00,0x80,0x00,0xFE,0x7F,0x02,0x40,0x01,0x20,0x00,0x00,0xFC,0x1F,0x80,0x00,
0x80,0x00,0x88,0x00,0x88,0x1F,0x88,0x00,0x88,0x00,0x94,0x00,0xE2,0x7F,0x01,0x00,"定",//3
0x00,0x08,0x00,0x1F,0xFC,0x00,0x80,0x00,0x80,0x00,0xFC,0x1F,0x80,0x00,0x80,0x00,
0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00,"手",//0
0x00,0x02,0x00,0x02,0x3E,0x02,0x00,0x02,0x80,0x3F,0x00,0x22,0x7F,0x22,0x04,0x22,
0x04,0x22,0x04,0x21,0x12,0x21,0x22,0x21,0xBF,0x20,0xA2,0x20,0x40,0x14,0x20,0x08,"动",//1
0x88,0x08,0x88,0x08,0xE8,0x3F,0x88,0x08,0x3F,0x00,0xC8,0x1F,0x4C,0x10,0xDC,0x1F,
0x6A,0x10,0xCA,0x1F,0x09,0x02,0xE8,0x3F,0x08,0x05,0x88,0x08,0x48,0x10,0x28,0x60,"模",//2
0x00,0x12,0x00,0x22,0x00,0x22,0x00,0x02,0xFF,0x7F,0x00,0x02,0x00,0x02,0x7C,0x02,
0x10,0x02,0x10,0x02,0x10,0x04,0x10,0x44,0xF0,0x48,0x1E,0x50,0x04,0x60,0x00,0x40,"式",//3
0x00,0x00,0xFE,0x3F,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0xFF,0x7F,
0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x08,0x04,0x08,0x04,0x04,0x04,0x02,0x04,"开",//0
0x08,0x04,0x08,0x04,0x08,0x04,0x08,0x02,0x3F,0x12,0x24,0x21,0xA4,0x7F,0x24,0x41,
0x24,0x00,0x12,0x3F,0x14,0x21,0x08,0x21,0x14,0x21,0x22,0x21,0x01,0x3F,0x00,0x21,"始",//1
0x00,0x08,0x00,0x1F,0xFC,0x00,0x40,0x00,0x88,0x08,0x90,0x08,0x10,0x04,0x80,0x00,
0xFE,0x3F,0xC0,0x01,0xA0,0x02,0x90,0x04,0x88,0x08,0x84,0x10,0x83,0x60,0x80,0x00,"采",//2
0x90,0x00,0x10,0x01,0xF8,0x3F,0x0C,0x01,0xFA,0x1F,0x09,0x01,0xF8,0x1F,0x08,0x01,
0xF8,0x3F,0x88,0x00,0xFF,0x7F,0xA0,0x02,0x90,0x04,0x8C,0x18,0x83,0x60,0x80,0x00,"集",//3

0x20,0x02,0x24,0x02,0x24,0x3E,0x24,0x02,0x24,0x09,0x24,0x11,0xA4,0x10,0x20,0x00,
0x00,0x00,0xFC,0x1F,0x24,0x12,0x24,0x12,0x24,0x12,0x24,0x12,0xFF,0x7F,0x00,0x00,"监",//0
0x00,0x20,0xE4,0x23,0x28,0x22,0x28,0x2A,0xA1,0x2A,0xA2,0x2A,0xA2,0x2A,0xA8,0x2A,
0xA8,0x2A,0xA4,0x2A,0xA7,0x2A,0x84,0x20,0x44,0x21,0x44,0x22,0x24,0x28,0x10,0x10,"测",//1
0x00,0x1F,0xFC,0x00,0x20,0x00,0x10,0x04,0x08,0x02,0xFC,0x01,0x80,0x00,0x60,0x08,
0x18,0x10,0xFE,0x3F,0x80,0x20,0x90,0x04,0x88,0x08,0x84,0x10,0xA2,0x20,0x40,0x00,"系",//2
0x08,0x02,0x08,0x04,0x04,0x04,0xC4,0x7F,0x12,0x02,0x1F,0x11,0x88,0x20,0xC4,0x7F,
0x02,0x49,0x1F,0x09,0x02,0x09,0x00,0x09,0x98,0x48,0x87,0x48,0x42,0x70,0x20,0x00,"统",//3
0xC4,0x1F,0x44,0x10,0x44,0x10,0xC4,0x1F,0x1F,0x00,0xE4,0x3D,0x24,0x25,0x34,0x25,
0xEC,0x3D,0x07,0x02,0xF4,0x7F,0x84,0x06,0x44,0x0A,0x24,0x12,0x1D,0x62,0x02,0x02,"操",//0
0x90,0x00,0x90,0x00,0x90,0x00,0x88,0x7F,0x48,0x01,0x4C,0x01,0x2C,0x01,0x0A,0x1F,
0x09,0x01,0x08,0x01,0x08,0x01,0x08,0x3F,0x08,0x01,0x08,0x01,0x08,0x01,0x08,0x01,"作",//1
0x40,0x10,0x84,0x10,0x88,0x08,0x08,0x04,0xC0,0x1F,0x40,0x10,0x4F,0x10,0x48,0x10,
0xC8,0x1F,0x08,0x05,0x08,0x05,0xA8,0x04,0x98,0x44,0x48,0x44,0x20,0x78,0x10,0x00,"说",//2
0x00,0x00,0x00,0x3F,0x3E,0x21,0x22,0x21,0x22,0x21,0x22,0x3F,0x3E,0x21,0x22,0x21,
0x22,0x21,0x22,0x3F,0x3E,0x21,0x22,0x21,0x80,0x20,0x80,0x20,0x40,0x28,0x20,0x10,"明",//3
0x88,0x08,0x88,0x08,0xE8,0x3F,0x88,0x08,0x3F,0x00,0xC8,0x1F,0x4C,0x10,0xDC,0x1F,
0x6A,0x10,0xCA,0x1F,0x09,0x02,0xE8,0x3F,0x08,0x05,0x88,0x08,0x48,0x10,0x28,0x60,"模",//0
0x00,0x12,0x00,0x22,0x00,0x22,0x00,0x02,0xFF,0x7F,0x00,0x02,0x00,0x02,0x7C,0x02,
0x10,0x02,0x10,0x02,0x10,0x04,0x10,0x44,0xF0,0x48,0x1E,0x50,0x04,0x60,0x00,0x40,"式",//1
0x08,0x00,0x08,0x00,0x88,0x3F,0x08,0x22,0x08,0x22,0x78,0x22,0x0F,0x22,0x08,0x22,
0x08,0x22,0x48,0x22,0x28,0x22,0x18,0x21,0x08,0x21,0x80,0x20,0x40,0x14,0x20,0x08,"切",//2
0x08,0x01,0x08,0x01,0x08,0x1F,0x88,0x10,0x5F,0x08,0xA8,0x3F,0x88,0x24,0x98,0x24,
0x8C,0x24,0x8B,0x24,0xE8,0x7F,0x08,0x0A,0x08,0x0A,0x08,0x11,0x8A,0x20,0x64,0x40,"换",//3
0x00,0x02,0x00,0x02,0x3F,0x3E,0x08,0x21,0x88,0x10,0x44,0x7F,0x3C,0x49,0x26,0x49,
0x26,0x7F,0x25,0x49,0x24,0x49,0x24,0x7F,0x3C,0x49,0xA4,0x48,0x84,0x50,0x40,0x20,"确",//0
0x10,0x01,0x10,0x02,0x10,0x02,0x08,0x00,0xE8,0x3F,0x0C,0x00,0x0C,0x10,0x4A,0x10,
0x49,0x10,0x88,0x08,0x88,0x08,0x88,0x08,0x88,0x04,0x08,0x04,0xF8,0x7F,0x08,0x00,"位",//0
0x10,0x04,0x92,0x04,0x54,0x04,0x10,0x7C,0xFF,0x22,0x54,0x22,0x92,0x22,0x11,0x25,
0x08,0x14,0x7F,0x14,0x44,0x08,0x42,0x08,0x26,0x14,0x18,0x14,0x2C,0x22,0x43,0x41,"数",//1
0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x3E,0x7F,0x22,0x48,0x22,0x48,0x22,0x48,0x22,
0x48,0x22,0x48,0x22,0x48,0x22,0x48,0x22,0x44,0x22,0x44,0x3E,0x52,0x22,0x21,0x00,"加",//0
0x00,0x28,0x02,0x48,0x04,0x08,0xE4,0x7F,0x20,0x08,0x20,0x08,0xA8,0x0B,0x28,0x48,
0x24,0x48,0xA7,0x2B,0xA4,0x2A,0xA4,0x12,0xA4,0x5B,0x24,0x54,0x14,0x62,0x08,0x41,"减",//1
0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0xC0,0x1F,0x40,0x00,
0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0xFF,0x7F,0x00,0x00,"上",//0
0x10,0x02,0x10,0x02,0x10,0x02,0xC8,0x1F,0x08,0x02,0x0C,0x01,0xEC,0x7F,0x0A,0x01,
0x89,0x00,0xC8,0x1F,0x08,0x10,0x88,0x08,0x08,0x05,0x08,0x02,0x08,0x04,0x08,0x04,"传",//1
0x10,0x04,0x92,0x04,0x54,0x04,0x10,0x7C,0xFF,0x22,0x54,0x22,0x92,0x22,0x11,0x25,
0x08,0x14,0x7F,0x14,0x44,0x08,0x42,0x08,0x26,0x14,0x18,0x14,0x2C,0x22,0x43,0x41,"数",//2
0x04,0x00,0xC4,0x3F,0x44,0x20,0x44,0x20,0xDF,0x3F,0x44,0x04,0x44,0x04,0xD4,0x7F,
0x4C,0x04,0x47,0x04,0x44,0x3F,0x44,0x21,0x44,0x21,0x24,0x21,0x25,0x3F,0x12,0x21,"据",//3


0x08,0x00,0x08,0x00,0xC8,0x7F,0x08,0x04,0x2A,0x04,0x1A,0x04,0x0A,0x04,0x09,0x04,
0x08,0x04,0x08,0x04,0x08,0x04,0x14,0x04,0x24,0x04,0x22,0x04,0x02,0x05,0x01,0x02,"灯",//0*/
0x80,0x00,0x84,0x10,0x88,0x10,0x90,0x08,0x90,0x04,0x80,0x00,0xFF,0x7F,0x20,0x02,
0x20,0x02,0x20,0x02,0x20,0x02,0x10,0x42,0x10,0x42,0x08,0x42,0x04,0x7C,0x03,0x00,"光",//1*/
0x08,0x02,0x08,0x04,0x08,0x04,0xC8,0x7F,0x5F,0x40,0x28,0x29,0x88,0x10,0x58,0x20,
0x0C,0x00,0x8B,0x3F,0x08,0x04,0x08,0x04,0x08,0x04,0x08,0x04,0xEA,0x7F,0x04,0x00,"控",//2*/
0x20,0x20,0x24,0x20,0x24,0x20,0xFC,0x25,0x22,0x24,0x20,0x24,0xFF,0x27,0x20,0x24,
0x20,0x24,0xFC,0x25,0x24,0x25,0x24,0x25,0x64,0x21,0xA4,0x20,0x20,0x28,0x20,0x10,"制",//3*/




};
#endif
