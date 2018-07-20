#include "stepmotor.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 							  
////////////////////////////////////////////////////////////////////////////////// 	 

//��ʼ������
void STEPMOTOR_Init(void)
{
	
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��

  //GPIOF1,F2,F3��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��
	
  PFout(1)=0;
  PFout(2)=1;//DIR = 1
  PFout(3)=1;//ENA = 1
} 

int Step_Ouput(int frequency)
{	 
	 PFout(1)=1;
	 delay_ms(500/frequency);
	 PFout(1)=0;
	 delay_ms(500/frequency);
}




















