// zui_lcd5110_lite.h

#ifndef _ZUI_LCD5110_LITE_h
#define _ZUI_LCD5110_LITE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class ZuiLite
{
public:
	ZuiLite();
	~ZuiLite();


	//LCD初始化函数
	void SetLcd(int RST0, int CE0, int DC0, int DIN0, int CLK0);
	//LCD清屏函数
	void Clear(void);
	//设置字符位置函数  xy坐标
	void SetPostion(unsigned char X, unsigned char Y);
	//数据写入到lcd dat数据，command 0命令1数据选择
	void WriteData(unsigned char dat, unsigned char command);


	//点          xy坐标
	void point(int x, int y);
	//画图        xy坐标(0-83,0-5)，width宽度,length长度,l点阵数据,是否反显，是否从内存读取数据
	void Draw(int x, int y, int width, int length, const char *l, bool reverse_display = 0, bool from_memory = 0);
	//变量输出    xy坐标(0-83,0-5), number数值，b要打印出多少位, 是否为浮点数，是否反显
	void Var(int x, int y, double number, int b, boolean  float_number = 0, bool reverse_display = 0);
	//文本输出    xy坐标(0-83,0-5), l字符串，是否反显
	void Text(int x, int y, char* l, boolean reverse_display = 0);


private:
	/*******************数据**************************/
	static int RST;
	static int CE;
	static int DC;
	static int DIN;
	static int CLK;
	static const char decimal_point[]PROGMEM; //小数点
	static const char ASCIIDZ[67];
	static char char_conver_temp[112];//字符转换缓存
	static const char xz[8] PROGMEM;//用到的地方不多就不重写名字了
	static const char ASCII[92][6]PROGMEM;
};


extern ZuiLite ui;//第一次发现还有这种骚操作
#endif

