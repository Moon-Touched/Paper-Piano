#include <wiringPi.h>

// LED Pin - wiringPi pin 0 是 BCM_GPIO 17。
// 利用 wiringPiSetupSys 进行初始化时必须使用 BCM 编号
// 选择其他 pin 编号时，请同时使用 BCM 编号
// 更新 Property Pages - Build Events - Remote Post-Build Event 命令
// 它使用 gpio 导出进行 wiringPiSetupSys 的设置
#define	LED	17

int main(void)
{
	wiringPiSetupSys();

	pinMode(LED, OUTPUT);

	while (true)
	{
		digitalWrite(LED, HIGH);  // 开
		delay(500); // 毫秒
		digitalWrite(LED, LOW);	  // 关
		delay(500);
	}
	return 0;
}