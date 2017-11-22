/*
 * TM1638 LED & KEY functions
 * Sugar Flower 2016
 */
#include <Arduino.h>

#ifndef __LEDANDKEY_H_INCLUDED__
#define __LEDANDKEY_H_INCLUDED__

class LedAndKey {
	public:
		void init(uint8_t stb, uint8_t clk, uint8_t dat);	
		void shiftOut(char value);
		char shiftIn();
		char readKeys();
		void sendCommand(char value);
		void reset();
		void dispSeg(char num, char data); // num=0-7
		void setBrightness(char level); // level=0-f
		void dispLED(char data);
		void dispNumber(char num, char value); // value=0-f

	private:
		//DigitalOut _CLK;
		//DigitalInOut _DAT;
		//DigitalOut _STB;

		uint8_t _CLK;
		uint8_t _DAT;
		uint8_t _STB;
		const char font[16]={
			0x3f, 0x06, 0x5b, 0x4f, 
			0x66, 0x6d, 0x7d, 0x07, 
			0x7f, 0x6f, 0x77, 0x7c, 
			0x58, 0x5e, 0x79, 0x71
		};

};

#endif
