#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x.h"

//����EEPROM��ģ����ʼ��ַΪFLASH�ĵ�255ҳ����ʼ��ַ
#define FLASH_PAGE255_ADDR  0x0800F800
//���ڱ�������Ĵ�СΪ50���ֽ�
//���Ը�����Ҫ����
#define STMFLASH_SIZE			2048

void STMFLASH_Read_Backup(void);
void STMFLASH_Write_NoErase(void);
void STMFLASH_Read(u16 ReadAddr,u16 *pstr,u16 NumberToRead);
void STMFLASH_Write(u16 WriteAddr,u16 *pBuffer,u16 NumToWrite);			   
#endif

















