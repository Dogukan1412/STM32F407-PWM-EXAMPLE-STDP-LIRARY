
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// TIM4  clock bus speed = 84MHz
// pin D12 --> TIM4_CH1
// pin D13 --> TIM4_CH2
// pin D14 --> TIM4_CH3
// pin D15 --> TIM4_CH4


void LED_Config(void);
void TIM4_Config(void);
void TIM4_PWM(void);

TIM_OCInitTypeDef pwm;

int main(void)
{
	LED_Config();
	TIM4_Config();

  while (1)
  {
	  TIM4_PWM();
  }
}


void LED_Config(void)
{
	GPIO_InitTypeDef led;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	led.GPIO_Mode = GPIO_Mode_AF;
	led.GPIO_OType = GPIO_OType_PP;
	led.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	led.GPIO_PuPd = GPIO_PuPd_NOPULL;
	led.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &led);
}


void TIM4_Config(void)               // this configuration counts up to 10000 per second.
{
	TIM_TimeBaseInitTypeDef tim4 = {0};

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);            // tim4 clock buss is activated

	tim4.TIM_ClockDivision = TIM_CKD_DIV1;                          // default clock speed / divided 1 = 84MHz
	tim4.TIM_CounterMode = TIM_CounterMode_Up;                      // counting up
	tim4.TIM_Period = 9999;                                         //  84 000 000 / ( (9999 + 1) * (8399 + 1) ) = 1 Hertz = 1 second
	tim4.TIM_Prescaler = 8399;
	tim4.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &tim4);									// initialized tim4
	TIM_Cmd(TIM4, ENABLE);


	pwm.TIM_OCMode = TIM_OCMode_PWM1;
	pwm.TIM_OCPolarity = TIM_OCPolarity_High;
	pwm.TIM_OutputState = TIM_OutputState_Enable;
}


void TIM4_PWM(void)
{
	pwm.TIM_Pulse = 9999;									// 100% duty cycle
	TIM_OC1Init(TIM4, &pwm);   								// pin D12 --> TIM4_CH1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	pwm.TIM_Pulse = 7499;									// 75% duty cycle
	TIM_OC2Init(TIM4, &pwm);   								// pin D13 --> TIM4_CH2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	pwm.TIM_Pulse = 4999;									// 50% duty cycle
	TIM_OC3Init(TIM4, &pwm);   								// pin D14 --> TIM4_CH3
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	pwm.TIM_Pulse = 2499;									// 25% duty cycle
	TIM_OC4Init(TIM4, &pwm);   								// pin D15 --> TIM4_CH4
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
}



/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
