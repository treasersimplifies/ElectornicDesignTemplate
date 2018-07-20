#include "matrixkey.h"
#include "sys.h"
#include "delay.h" 
#include "usart.h"

//������̳�ʼ������

void MATRI4X4KEY_Init(void){
	int i;
	RCC->AHB1ENR|=1<<1;//ʹ��PORTBʱ�� 
	GPIO_Set(GPIOB,PIN0|PIN1|PIN2|PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PB0-PB3����Ϊ���ģʽ
	GPIO_Set(GPIOA,PIN0|PIN1|PIN2|PIN3,GPIO_MODE_IN,0,0,GPIO_PUPD_PD); //PB4-PB7����Ϊ����ģʽ
	for(i=0;i<4;i++){//��ȫ���������0��
		BIT_ADDR(GPIOB_ODR_Addr,i)=0;  
	}	
}
//����ɨ�跨��
int MATRI4_4KEY_Scan(int * row, int * column){
	
	int i =5;
	int j =5;
	
	for(i=3;i>=0;i--){
		PBout(i)=1;
		for(j=0;j<4;j++){
			if(PAin(j)==1){
				delay_ms(10);
				if(PAin(j)==1){//˫���жϣ�����
					printf("into PBin(%d)=1\n",j);
					*row = 5-(i+1);
					*column = j+1;
					PBout(i)=0;
					//printf("row = %d, column = %d \n",i,j);
					//delay_ms(1000);
					return 0;
				}
			}
		}
		PBout(i)=0;//һ��Ҫ�ǵý���һ�е������������
	}
	return -1;
	
}
//���з�ת����
int MATRI4X4KEY_Scan(int * row, int * column){
	int i,j;
	delay_ms(1);
	
	//PB0-PB3
	GPIO_Set(GPIOB,PIN0|PIN1|PIN2|PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PB0-PB3����Ϊ���ģʽ
	GPIO_Set(GPIOB,PIN4|PIN5|PIN6|PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_PD); //PB4-PB7����Ϊ����ģʽ
	for(i=0;i<4;i++){//��ȫ���������1��
		BIT_ADDR(GPIOB_ODR_Addr,i)=1;  
	}	
	delay_ms(1);
	for(j=4;j<8;j++){//�ж���һ��������
		if(BIT_ADDR(GPIOA_IDR_Addr,j)==1){
			*row=j-3;//�õ������µ��Ǹ�������ֵ
			printf("ROW!!!\n");
			break;
		}
	}
	
	
	for(i=0;i<4;i++){			//��ȫ���������0��
		BIT_ADDR(GPIOB_ODR_Addr,i)=0;  
	}	
	//PB4-PB8
	GPIO_Set(GPIOB,PIN0|PIN1|PIN2|PIN3,GPIO_MODE_IN,0,0,GPIO_PUPD_PD); //PB0-PB3����Ϊ����ģʽ
	GPIO_Set(GPIOB,PIN4|PIN5|PIN6|PIN7,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //PB4-PB7����Ϊ���ģʽ
	//���з�תһ�£��õ���ֵ��
	for(j=4;j<8;j++){//��ȫ���������1��
		BIT_ADDR(GPIOB_ODR_Addr,j)=1;  
	}	
	delay_ms(1);
	for(i=0;i<4;i++){//�ж���һ��������
		if(BIT_ADDR(GPIOA_IDR_Addr,i)==1){
			*column=i+1;//�õ������µ��Ǹ�������ֵ
			printf("COL!!!\n");
			break;
		}
	}
	if(*row>=0)
		return 0;
	else
		return -1;
}


