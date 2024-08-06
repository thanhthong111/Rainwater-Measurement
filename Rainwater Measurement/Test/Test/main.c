#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <avr/interrupt.h>
#define F_CPU 16000000L
#include <util/delay.h>

/*Time count 
Clock Period = 1 / 32000 = 1 / 32 (ms)
Time Count = (6 / (1/32) ) – 1 = 191
*/

//Ham random [a,b)
int RandomI (int min, int max){
	return min + rand() % (max - min);
}
//Ham random [a,b]
int RandomII (int min, int max){
	return min + rand() % (max + 1 - min);
}
//Ham gan gia tri luong mua
int assign (){
	float a;
	a = RandomII(0, 40);
	PORTA = a;
	return PORTA;
}
//Timer
void T0delay()
{
	TCNT0= 0xBF;
	TCCR0= 0b00000001; // no prescaler
	while((TIFR&0x01)==0);
	TCCR0= 0;
	TIFR= 0x01; // Clear TOV0 to ‘1’ for the next round.
	sei();
}

int main(void)
{		
	DDRA = 0xFF;
	DDRC = 0xFF;
	RandomI (0,40);
	RandomII(0,40);
	assign();
	int t;
	while (1)
	{	
		// Task i
		/*for (int i = 0; i <= 3; i++){
			if (i == 0) {
				t = RandomI(0,10);
				
			}
			else if (i == 1) {
				t = RandomI(10,20);
			}
			else if (i == 2) {
				t = RandomI (20,30);
			}
			else {
				t = RandomII(30,40);
			}
		if (t >= 0 && t <= 10 ){
			PORTC=0x01;
		}
		else if (t >= 10 && t < 20){
			PORTC=0x02;
		}
		else if(t >= 20 && t < 30 ){
			PORTC=0x04;
		}
		else if (t >=30 && t < 40 ){
			PORTC=0x08;
			
		}
			T0delay();
			PORTC=0x00;
			T0delay();		
		}
	}*/
		// Task ii
		for (int i = 0; i <= 3; i++){
			t = assign();
			if (t >= 0 && t < 10 ){
				PORTC=0x01;				
			}
			else if (t >= 10 && t < 20){
				PORTC=0x02;
				
			}
			else if(t >= 20 && t < 30 ){
				PORTC=0x04;
				
			}
			else if (t >=30 && t < 40 ){
				PORTC=0x08;								
			}
			T0delay();
			_delay_ms(1000);
			PORTC=0x00;
			_delay_ms(1000);
			T0delay();	
		}
	}
}


