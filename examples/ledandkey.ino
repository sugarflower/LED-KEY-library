#include <ledandkey.h>

// use pins
#define strobePin 2
#define clockPin 3
#define dataPin 4

LedAndKey lak;

uint8_t key;
uint8_t flg;
unsigned long pc;

void setup(){
	lak.init(strobePin, clockPin, dataPin);
	lak.setBrightness(0x8); //brightness is 0x0 to 0xf
	lak.reset();
	flg=0;
	pc=0;
}

void loop(){
	key=lak.readKeys(); //input switch
	lak.dispLED(key); //display leds


	if( pc < millis() ){
		pc = millis() + 1000;
		if(flg == 0){
			flg=1;
		} else {
			flg=0;
		}

		//display seg leds
		if( flg==0){
			for(char i=0; i<8; i++ ){
				lak.dispNumber(i,i);
			}
		} else {
			for(char i=0; i<8; i++ ){
				lak.dispNumber(i,i+8);
			}
		}
	}
}
