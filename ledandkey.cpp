#include "ledandkey.h"
#include <Arduino.h>

void LedAndKey::init(uint8_t stb,uint8_t clk,uint8_t dat) 
{
	_CLK = clk;
	_DAT = dat;
	_STB = stb;
	pinMode(_CLK,OUTPUT);
	pinMode(_STB,OUTPUT);
	pinMode(_DAT,OUTPUT);
	sendCommand(0x8f);
	reset();
}

char LedAndKey::readKeys(){
	char keys=0;
	digitalWrite(_STB,LOW);
	shiftOut(_DAT,_CLK,LSBFIRST,0x42);
	pinMode(_DAT,INPUT);
	keys = shiftIn(_DAT,_CLK,LSBFIRST);
	keys = keys | (shiftIn(_DAT,_CLK,LSBFIRST)<<1);
	keys = keys | (shiftIn(_DAT,_CLK,LSBFIRST)<<2);
	keys = keys | (shiftIn(_DAT,_CLK,LSBFIRST)<<3);
	digitalWrite(_STB,HIGH);
	pinMode(_DAT,OUTPUT);
	return keys;
}

void LedAndKey::sendCommand(char value){
	digitalWrite(_STB,LOW);
	shiftOut(_DAT,_CLK,LSBFIRST,value);
	digitalWrite(_STB,HIGH);
}

void LedAndKey::reset(){
	digitalWrite(_STB,LOW);
	shiftOut(_DAT,_CLK,LSBFIRST,0xc0);
	for(char i=0; i<16; i++){
		shiftOut(_DAT,_CLK,LSBFIRST,0x00);
	}
	digitalWrite(_STB,HIGH);
}

// num = 0-7
void LedAndKey::dispSeg(char num, char data){
	sendCommand(0xc0);
	digitalWrite(_STB,LOW);
	shiftOut(_DAT,_CLK,LSBFIRST,0xc0 | (num*2) );
	shiftOut(_DAT,_CLK,LSBFIRST,data );
	digitalWrite(_STB,HIGH);
}

// level = 0-f
void LedAndKey::setBrightness(char level){
	sendCommand(0x80 | level);
}

void LedAndKey::dispLED(char data){
	for(char i=0; i<8 ; i++){
		digitalWrite(_STB,LOW);
		shiftOut(_DAT,_CLK,LSBFIRST,0xc0 | (i*2+1) );
		if( data & (1<<i) ){
			shiftOut(_DAT,_CLK,LSBFIRST,0x01 );
		} else {
			shiftOut(_DAT,_CLK,LSBFIRST,0x00 );
		}
		digitalWrite(_STB,HIGH);
	}
}
// value = 0-f
void LedAndKey::dispNumber(char num, char value){
	if( value < 0x10){
		dispSeg(num,font[value]);
	}
}
