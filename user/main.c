#include "stm32f10x.h"
#include "public.h"

float pitch,roll,yaw;
 unsigned char rxBuffer[250];
 u16 p_r,i_r,d_r;
int main(void) {
	NvicConfiguration(3);
	UartsInit(115200,3);
	delay_init();
	MPU_Init();
	while(mpu_dmp_init());
	
	
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef timer;
	TIM_OCInitTypeDef timerOC;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	
	timer.TIM_Period = 1439;
	timer.TIM_Prescaler = 0;
	timer.TIM_ClockDivision = 0;
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &timer);
	
	timerOC.TIM_OCMode = TIM_OCMode_PWM2;
	timerOC.TIM_OutputState = TIM_OutputState_Enable;
	timerOC.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM2, &timerOC);	
	TIM_OC1Init(TIM2, &timerOC);
	TIM_OC3Init(TIM2, &timerOC);
	TIM_OC4Init(TIM2, &timerOC);
	
	TIM_Cmd(TIM2, ENABLE);
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

	int PWMA, PWMB, PWMC, PWMD;
	PWMA = PWMB = PWMC = PWMD = 250;
	
	Pid pidRed;
	Pid pidBlack;
	pidInit(&pidRed);
	pidInit(&pidBlack);
	
	

	
	while(1) {
	
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		
		GPIO_SetBits(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	
		
		if (pitch >= 10) {
			PWMA = 750;
		} else if (pitch <= -10) {
			PWMC = 750;
		}
		if (roll >= 10) {
			PWMD = 750;
		} else if (roll <= -10) {
			PWMB = 750;
		}
		
//		
		TIM_SetCompare1(TIM2, PWMA);
		TIM_SetCompare2(TIM2, PWMB);
		TIM_SetCompare3(TIM2, PWMC);
		TIM_SetCompare4(TIM2, PWMD);
		
		PWMA = PWMB = PWMC = PWMD = 250;
		
//		switch(Direction()) {
//			case 1: PWMA = PWMA * pidCalculator(&pid);
//			case 2: PWMB = PWMB * pidCalculator(&pid);
//			case 3: PWMC = PWMC * pidCalculator(&pid);
//			case 4: PWMD = PWMD * pidCalculator(&pid);
//		}
//		
	}
	return 0;
}
