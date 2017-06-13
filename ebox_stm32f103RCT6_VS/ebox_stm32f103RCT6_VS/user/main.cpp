#include "ebox.h"
#include "led.h"
#include "drv8825.h"

Led led(&PC13, 1);
DRV8825 step1(&PA6, &PB12);
DRV8825 step2(&PA7, &PB13);

void setup()
{
    ebox_init();
    uart1.begin(115200);
	led.begin();
	step1.begin();
	step2.begin();
}


//��Ӧ����
//int main(void)
//{
//	setup();
//	float pct = 100;
//	while (1)
//	{
//
//		step1.setPercent(pct);
//		step2.setPercent(pct);
//
//		pct = -pct;
//
//		led.toggle();
//		uart1.printf("%f\r\n", step1.getPercent());
//		delay_ms(100);
//
//	}
//
//}

//�ٶȷ�Χ����
int main(void)
{
	setup();
	float pct = 0, increase = 0.005;
	while (1)
	{

		step1.setPct(pct);
		step2.setPct(pct);

		pct += increase;
		if (pct >= 1 || pct <= -1)
		{
			increase = -increase;
		}

		led.toggle();
		uart1.printf("%f\r\n", step1.getPct());
		delay_ms(1);

	}

}


