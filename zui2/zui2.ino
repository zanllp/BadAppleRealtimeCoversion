/*
 Name:		zui2.ino
 Created:	2018/9/7 00:39:25
 Author:	zanllp
*/
//复制到zui2.ino里面，我用的vs2017的visual micro有点bug只能这么做

//#include "zui_lcd5110_lite.h"
#include "zui_lcd5110.h"
#include<avr/pgmspace.h>

void UI()
{
	/***************根据页面编号进行切换****************/
	switch (ui.GetPage())//页面切换，分配页面编号
	{
	case 0:
		home();//主页
		break;
	case 1:
		timer();
		break;
	case 2:
		brightness();
		break;
	default://默认相当于没分配页面编号
		ui.SetPage(0);//必须指出home的页面编号为0，不然出现home键
		home();//主页
		break;
	}
}
boolean led_open = false;//led灯状态
void home()
{
	ui.Text(0, 0, "This a led");
	ui.Text(0, 1, "light controller");
	ui.Text(0, 2, "based on zui.");
	ui.Text(0, 3, "status:");
	if (led_open)
	{
		ui.ButtonText(50, 3, "open");
	}
	else
	{
		ui.ButtonText(50, 3, "false");
	}
	if (ui.Click(0))
	{
		led_open = !led_open;
	}
	ui.ButtonText(0, 4, "To timer");
	if (ui.Click(1))
	{
		ui.ToPage(1);
	}
	ui.ButtonText(0, 5, "To brightness");
	if (ui.Click(2))
	{
		ui.ToPage(2);
	}
	ui.ReverseDisplayEnd();//页面结束,当前页面使用反显,使用纵向电位器对面光标进行控制,必须放在页面末尾
}
void timer()
{
	ui.Text(0, 0, "this is");
	ui.Text(0, 1, "timer page");
	ui.ReverseDisplayEnd();
}
int bright_num = 100;//亮度
void brightness()
{
	ui.Text(0, 0, "this is");
	ui.Text(0, 1, "brightness");
	ui.Text(0, 2, "page");
	ui.Var(40, 3, bright_num, 3);//实时刷新
	ui.ButtonText(0, 4, "click me");
	if (ui.Click(0))//第0个按键按下
	{
		ui.MsgBox(bright_num, 3, 0, 10);//弹出个修改框来修改亮度
	}
	ui.ReverseDisplayEnd();
}
unsigned long time_last;
bool back_light = true;
unsigned long time_temp;
unsigned long time_temp_0;

void setup()
{
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	ui.SetLcd(6, 7, 5, 4, 3);//rst,ce,dc,din,clk
	ui.SetPS2(A2, A1, A0);//用于控制界面的ps2摇杆的按键，纵向选项电位器针脚，横向选项电位器针脚
	Serial.begin(9600);
	time_temp = millis();
	time_temp_0 = millis();
}
void loop()
{
	//这部分不用管，我拿来当电灯控制器用的，可以直接删除
	digitalWrite(12, !led_open);
	digitalWrite(11, !back_light);
	if (ui.PS2VRXDown()||ui.PS2VRXUp()||ui.PS2VRYDown()||ui.PS2VRYUp())
	{
		led_open = !led_open;
		back_light = true;
		time_temp = millis();
		delay(500);
	}
	if (millis()-time_temp>10000)
	{
		back_light = false;
	}
	//可以直接删掉
	//time_temp_0 = millis();
	//UI();//启动界面
	//Serial.println(millis() - time_temp_0);

	//本体
	if (Serial.available())
	{
		digitalWrite(11, 0);//背光常亮，我用的继电器控制所以是低电平
		int pos=0;
		char temp[504] = { 0 };//保存点阵数据
		while (true)
		{
			if (Serial.available())
			{
				char* temp_0=temp+pos*42;//指针偏移
				Serial.readBytes(temp_0, 42);//一次读42个字节，也就是半行，所以要收12次
				pos++;
				if (pos>=12)//收够数据画图
				{
					pos = 0;
					ui.Draw(0, 0, 84, 48, temp, false, true);
				}
				time_temp = millis();
			}
			if (millis() - time_temp > 10000)//10秒没收到数据清屏
			{
				ui.Clear();
				time_temp = millis();
				pos = 0;
				
			}
		}
		
		
	}
	
}
