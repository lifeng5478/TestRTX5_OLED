#include "eeprom.h"
#include "delay.h"

//2015-6-2 16:51:29
//by @creep

//����EEPROM�Ĵ�СΪ1K
//�ɸ���ʵ�ʵ�����С
u16 STMFLASH_BUFF[STMFLASH_SIZE];
//Ҫд���ݵ���ʼ��ַΪ0-STMFLASH_SIZE,����ΪHalfWord����
//ֻ��д��������ΪHalfWord�����ݵ�EEPROM ����
void STMFLASH_Write(u16 WriteAddr,u16 *pBuffer,u16 NumToWrite)
{
	u16 j;
	STMFLASH_Read_Backup();															//�����������������
	FLASH_Unlock();                    								 //����
	FLASH_ErasePage(FLASH_PAGE255_ADDR); 							//������255ҳ
	for(j=0;j<NumToWrite;j++)
	{
		STMFLASH_BUFF[j+WriteAddr] = *(pBuffer+j);			//������д��������ȥ
	}	
	STMFLASH_Write_NoErase();													//������д�ص���255ҳ��
	FLASH_Lock();																			//����	
}
//��ȡ����Ϊ�ֽ�����
//��EEEPROM��1K�ֽڶ�����
void STMFLASH_Read_Backup(void)
{
	u16  t;
	for(t=0;t<STMFLASH_SIZE;t++) 
	{
		*(STMFLASH_BUFF+t) = *(u16*)(FLASH_PAGE255_ADDR+t*2);		
	}	
}
//��EEPROM��1K������д�ص���255ҳ
//д����ǰ������
void STMFLASH_Write_NoErase(void)
{
	u16 t;
	for(t=0;t<STMFLASH_SIZE;t++)
	{		
		FLASH_ProgramHalfWord(FLASH_PAGE255_ADDR+t*2,*(STMFLASH_BUFF+t));
	}	
}
//��eeprom�ж�����
void STMFLASH_Read(u16 ReadAddr,u16 *pstr,u16 NumberToRead)
{
	u16 t;
	for(t=0;t<NumberToRead;t++)
	{
		*(pstr+t) = *(u16*)(FLASH_PAGE255_ADDR+ReadAddr+t*2);	
	}
}




















