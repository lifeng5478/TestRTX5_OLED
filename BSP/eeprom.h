#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x.h"

//定义EEPROM的模拟起始地址为FLASH的第255页的起始地址
#define FLASH_PAGE255_ADDR  0x0800F800
//定于备份区域的大小为50个字节
//可以根据需要调整
#define STMFLASH_SIZE			2048

void STMFLASH_Read_Backup(void);
void STMFLASH_Write_NoErase(void);
void STMFLASH_Read(u16 ReadAddr,u16 *pstr,u16 NumberToRead);
void STMFLASH_Write(u16 WriteAddr,u16 *pBuffer,u16 NumToWrite);			   
#endif

















