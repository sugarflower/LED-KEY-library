#include "ledandkey.h"
#include <Arduino.h>

void LedAndKey::init(uint8_t stb,uint8_t clk,uint8_t dat) 
{
	_CLK = clk;
	_DAT = dat;
	_STB = stb;
	pinMode(_CLK,OUTPUT);
	pinMode(_STB,OUTPUT);
	sendCommand(0x8f);
	reset();
}

void LedAndKey::shiftOut(char value){
	pinMode(_DAT,OUTPUT);
	for(char i=0; i<8; i++ ){
		digitalWrite(_CLK,LOW);
		if((value & 1)){
			digitalWrite(_DAT,HIGH);
		} else {
			digitalWrite(_DAT,LOW);
		}
		value=value>>1;
		digitalWrite(_CLK,HIGH);
	}
}

char LedAndKey::shiftIn(){
	pinMode(_DAT,INPUT_PULLUP);
	char indata=0;
	for(char i=0; i<8; i++ ){
		digitalWrite(_CLK,LOW);
		delay(5);
		if( digitalRead(_DAT)!=0){
			indata = indata | (1 << i );
		}
		digitalWrite(_CLK,HIGH);
		delay(5);
	}
	return indata;
}

char LedAndKey::readKeys(){
	char keys=0;
	digitalWrite(_STB,LOW);
	shiftOut(0x42);
	for(char i=0; i<4; i++){
		keys = keys | (shiftIn()<<i);
	}
	digitalWrite(_STB,HIGH);
	return keys;
}

void LedAndKey::sendCommand(char value){
	digitalWrite(_STB,LOW);
	shiftOut(value);
	digitalWrite(_STB,HIGH);
}

void LedAndKey::reset(){
	digitalWrite(_STB,LOW);
	shiftOut(0xc0);
	for(char i=0; i<16; i++){
		shiftOut(0x00);
	}
	digitalWrite(_STB,HIGH);
}

// num = 0-7
void LedAndKey::dispSeg(char num, char data){
	sendCommand(0xc0);
	digitalWrite(_STB,LOW);
	shiftOut( 0xc0 | (num*2) );
	shiftOut( data );
	digitalWrite(_STB,HIGH);
}

// level = 0-f
void LedAndKey::setBrightness(char level){
	sendCommand(0x80 | level);
}

void LedAndKey::dispLED(char data){
	for(char i=0; i<8 ; i++){
		digitalWrite(_STB,LOW);
		shiftOut( 0xc0 | (i*2+1) );
		if( data & (1<<i) ){
		//	shiftOut( 0xc0 | (i*2+1) );
			shiftOut( 0x01 );
		} else {
			shiftOut( 0x00 );
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
