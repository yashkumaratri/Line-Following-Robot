// Project name : Line follower for Atmega8 mini
// Compile Date : 2/2/2011 Time : (16:21)
// Designed By  : Geekslab Technologies
//                http://www.geekslab.in
/*
PWM LED-------------->PB1
RIGHT MOTOR(+)------->PB1
RIGHT MOTOR(-)------->PB2
LEFT MOTOR(-)-------->PB3
LEFT MOTOR(+)-------->PB4
BUZZER--------------->PB0
LDR------------------>PC5
BOOTLOADER Condition Check-----PC2(if 0 bootler section else program execution
							  section of Flash memory)
RESET----------------->PC6
Crystal Ossilator----PB6 and PB7
left sensor---------->PC0
right sensor--------->PC3
Temprature sensor------>PC1
sound sensor------------>PC2
*********DTMF sensor connection********

DTMF D0---->PC0
DTMF D1---->PC1
DTMF D2---->PC2
DTMF D3---->PC3
VB=Battery Supply
VCC=regulated 5V+
Gnd=ground(0V)
VR1=Contrast of LCD
*/


#include<avr/io.h>
#include<util/delay.h>

void wait(float sec, int freq)   //wait function to create time delay  
{
for(int i=0;i<(int)(46*sec);i++)
_delay_loop_2(0);
}
void main()
{
	DDRC=0b0000000;  //set PORTC as input port
	DDRB=0b11111111;  //PB1, PB2, PB3, PB4 as output port
    int ls=0, rs=0;   // define & initialize ls, rs integer as 0 to 
						// acquire the left sensor status in ls and right sensor
						// status in rs 
	while(1)            // create infinite loop
	{
	ls=(PINC&0b0000001);  //acquire only left sensor status connected at PC0
	rs=(PINC&0b0000100);   // acquire only right sensor status connected at PC3
		
		if((ls==0b0000000)&(rs==0b0000000)) //check sensor status for both sensor OFF 
		{
			PORTB=0b00000000;  //stop
			ls=0;   //set sensor status off
			rs=0;   //set sensor status off
		}

		if((ls==0b0000001)&(rs==0b0000000)) //check sensor status for left sensor=ON and
		                                     // right sensor=OFF
		{
			
			PORTB=0b00001100;    //turn right
			ls=0;   //set sensor status off
			rs=0;   //set sensor status off
		}
		
		if((ls==0b0000000)&(rs==0b0000100)) //check sensor status for left sensor=OFF and
		                                     // right sensor=ON
		{
			 
			PORTB=0b00000010;   //turn left
			ls=0;   //set sensor status off
			rs=0;     //set sensor status off
		}
        if((ls==0b0000001)&(rs==0b0000100)) //check sensor status for both sensor ON 
		{
			PORTB=0b00010100;  //move forward
			ls=0;   //set sensor status off
			rs=0;     //set sensor status off
		}
	}
}
