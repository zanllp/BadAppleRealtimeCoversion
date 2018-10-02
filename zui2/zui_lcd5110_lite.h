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


	//LCD��ʼ������
	void SetLcd(int RST0, int CE0, int DC0, int DIN0, int CLK0);
	//LCD��������
	void Clear(void);
	//�����ַ�λ�ú���  xy����
	void SetPostion(unsigned char X, unsigned char Y);
	//����д�뵽lcd dat���ݣ�command 0����1����ѡ��
	void WriteData(unsigned char dat, unsigned char command);


	//��          xy����
	void point(int x, int y);
	//��ͼ        xy����(0-83,0-5)��width���,length����,l��������,�Ƿ��ԣ��Ƿ���ڴ��ȡ����
	void Draw(int x, int y, int width, int length, const char *l, bool reverse_display = 0, bool from_memory = 0);
	//�������    xy����(0-83,0-5), number��ֵ��bҪ��ӡ������λ, �Ƿ�Ϊ���������Ƿ���
	void Var(int x, int y, double number, int b, boolean  float_number = 0, bool reverse_display = 0);
	//�ı����    xy����(0-83,0-5), l�ַ������Ƿ���
	void Text(int x, int y, char* l, boolean reverse_display = 0);


private:
	/*******************����**************************/
	static int RST;
	static int CE;
	static int DC;
	static int DIN;
	static int CLK;
	static const char decimal_point[]PROGMEM; //С����
	static const char ASCIIDZ[67];
	static char char_conver_temp[112];//�ַ�ת������
	static const char xz[8] PROGMEM;//�õ��ĵط�����Ͳ���д������
	static const char ASCII[92][6]PROGMEM;
};


extern ZuiLite ui;//��һ�η��ֻ�������ɧ����
#endif

