#include "ebox.h"
#include "led.h"
#include "drv8825.h"

Led led(&PC13, 1);
DRV8825 step(&PB8, &PC9,15000);

void setup()
{
	ebox_init();
	uart1.begin(115200);
	led.begin();
	step.begin();
}
int main(void)
{
	setup();
	float pct = 0, increase = 1;
	while (1)
	{
		pct += increase;
		if (pct >= 100 || pct <= -100)
		{
			increase = -increase;
		}
		
		step.setPct(pct);


		led.toggle();
		uart1.printf("%f\r\n", step.getPct());
		delay_ms(5);

	}

}


