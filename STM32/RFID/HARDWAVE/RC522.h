#ifndef RFID_RC522_H
#define RFID_RC522_H
#include "sys.h"

/*
RC522射频模块外部的接口:    
*1--SDA <----->PF0--片选脚 
*2--SCK <----->PA5--时钟线
*3--MOSI<----->PA7--输出
*4--MISO<----->PA6--输入
*5--悬空
*6--GND <----->GND
*7--RST <----->PF1--复位脚
*8--VCC <----->VCC
*/

//#define RC522_OUTPUT PAout(7)
//#define RC522_INPUT PAin(6)
//#define RC522_SCLK PAout(5)
//#define RC522_CS PFout(0)
//#define RC522_RST PFout(1)

extern int LOCK_PASSWD;


#define RC522_OUTPUT PCout(8)
#define RC522_INPUT PBin(6)
#define RC522_SCLK PCout(7)
#define RC522_CS PCout(6)
#define RC522_RST PCout(9)


//MF522命令字
#define PCD_IDLE              0x00               //取消当前命令
#define PCD_AUTHENT           0x0E               //验证密钥
#define PCD_RECEIVE           0x08               //接收数据
#define PCD_TRANSMIT          0x04               //发送数据
#define PCD_TRANSCEIVE        0x0C               //发送并接收数据
#define PCD_RESETPHASE        0x0F               //复位
#define PCD_CALCCRC           0x03               //CRC计算


//Mifare_One卡片命令字
#define PICC_REQIDL           0x26               //寻天线区内未进入休眠状态,返回的是卡的类型
#define PICC_REQALL           0x52               //寻天线区内全部卡，返回的是卡的类型
#define PICC_ANTICOLL1        0x93               //防冲撞
#define PICC_ANTICOLL2        0x95               //防冲撞
#define PICC_AUTHENT1A        0x60               //验证A密钥
#define PICC_AUTHENT1B        0x61               //验证B密钥   命令认证代码
#define PICC_READ             0x30               //读块
#define PICC_WRITE            0xA0               //写块
#define PICC_DECREMENT        0xC0               //扣款
#define PICC_INCREMENT        0xC1               //充值
#define PICC_RESTORE          0xC2               //调块数据到缓冲区
#define PICC_TRANSFER         0xB0               //保存缓冲区中数据
#define PICC_HALT             0x50               //休眠

//MF522 FIFO长度定义
#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte
#define MAXRLEN  18


//MF522寄存器定义
// PAGE 0
#define     RFU00                 0x00    
#define     CommandReg            0x01    
#define     ComIEnReg             0x02    
#define     DivlEnReg             0x03    
#define     ComIrqReg             0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     RFU0F                 0x0F
// PAGE 1     
#define     RFU10                 0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     RFU1A                 0x1A
#define     RFU1B                 0x1B
#define     MifareReg             0x1C
#define     RFU1D                 0x1D
#define     RFU1E                 0x1E
#define     SerialSpeedReg        0x1F
// PAGE 2    
#define     RFU20                 0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     RFU23                 0x23
#define     ModWidthReg           0x24
#define     RFU25                 0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F

// PAGE 3      
#define     RFU30                 0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     RFU3C                 0x3C   
#define     RFU3D                 0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F		  		        0x3F


//和MF522通讯时返回的错误代码
#define 	MI_OK                 0
#define 	MI_NOTAGERR           1
#define 	MI_ERR                2

#define	SHAQU1		0X01
#define	KUAI4			0X04
#define	KUAI7			0X07
#define	REGCARD		0xa1
#define	CONSUME		0xa2
#define READCARD	0xa3
#define ADDMONEY	0xa4

/*
    RC522各种驱动函数
*/
void RC522_Init(void);																            //功    能：RC522射频卡模块初始化
void RC522_ClearBitMask(u8 reg,u8 mask);							            //功    能：清RC522寄存器位
void RC522_WriteRawRC(u8 Address, u8 value);					            //功    能：写RC632寄存器
void RC522_SetBitMask(u8 reg,u8 mask);							             	//功    能：置RC522寄存器位
char RC522_PcdComMF522(u8 Command,u8*pIn,u8 InLenByte,u8*pOut,u8*pOutLenBit);	//功能：通过RC522和ISO14443卡通讯
void RC522_CalulateCRC(u8 *pIn,u8 len,u8 *pOut );		              //功    能：用MF522计算CRC16函数
u8 RC522_ReadRawRC(u8 Address);													          //功    能：读RC632寄存器

char RC522_PcdReset(void);																						//功    能：复位RC522
char RC522_PcdRequest(unsigned char req_code,unsigned char *pTagType);//功    能：寻卡
void RC522_PcdAntennaOn(void);																				//功    能：开启天线 
void RC522_PcdAntennaOff(void);																				//功    能：关闭天线
char M500PcdConfigISOType(unsigned char type);									      //功    能：设置RC632的工作方式 
char RC522_PcdAnticoll(unsigned char *pSnr);													//功    能：防冲撞
char RC522_PcdSelect(unsigned char *pSnr);														//功    能：选定卡片
char RC522_PcdAuthState(unsigned char auth_mode,unsigned char addr,unsigned char *pKey,unsigned char *pSnr);//功    能：验证卡片密码
char RC522_PcdWrite(unsigned char addr,unsigned char *pData);					//功    能：写数据到M1卡一块
char RC522_PcdRead(unsigned char addr,unsigned char *pData);					//功    能：读取M1卡一块数据
char RC522_PcdHalt(void);																							//功    能：命令卡片进入休眠状态
void RC522_Reset(void);																					      //功    能：复位RC522
u8 RC522_MFRC522_SelectTag(u8 *serNum);                               //功    能：读取卡存储器容量
u8 RC522_SPI_ReadWriteOneByte(u8 tx_data);
void  notarize_type1();
void  notarize_type3();
#endif

