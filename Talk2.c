//blink the led
#define F_CPU 8000000UL
#include <avr/io.h>		//header file
#include <util/delay.h>
#include <avr/eeprom.h>


// Typedefs
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
//typedef unsigned int anAllophone;

// Defines
#define forever	117
#define aPowerOn	PORTD |= (1<<PD1) //high voltage
#define aPowerOff 	PORTD &= ~(1<<PD1)//low voltage
#define SpeakerOn	PORTD |= (1<<PD0) //high voltage
#define SpeakerOff	PORTD &= ~(1<<PD1)//low voltage
#define LEDOFF	PORTD |= (1<<PD2) //high voltage
#define LEDON	PORTD &= ~(1<<PD2)//low voltage
//Define ALLOPHONES
#define aPA1 SayIt(0)
#define aPA2 SayIt(1)
#define aPA3 SayIt(2)
#define aPA4 SayIt(3)
#define aPA5 SayIt(4)
#define aOY SayIt(5)
#define aAY SayIt(6)
#define aEH SayIt(7)
//#define XX SayIt(8)
//#define XX SayIt(9)
#define aKK3 SayIt(8)
#define aPP SayIt(9)
#define aJH SayIt(10)
#define aNN1 SayIt(11)
#define aIH SayIt(12)
#define aTT2 SayIt(13)
#define aRR1 SayIt(14)
#define aAX SayIt(15)
//#define XX SayIt(18)
//#define XX SayIt(19)
#define aMM SayIt(16)
#define aTT1 SayIt(17)
#define aDH1 SayIt(18)
#define aIY SayIt(19)
#define aEY SayIt(20)
#define aDD1 SayIt(21)
#define aUW1 SayIt(22)
#define aAO SayIt(23)
//#define XX SayIt(28)
//#define XX SayIt(29)
#define aAA SayIt(24)
#define aYY2 SayIt(25)
#define aAE SayIt(26)
#define aHH1 SayIt(27)
#define aBB1 SayIt(28)
#define aTH SayIt(29)
#define aUH SayIt(30)
#define aUW2 SayIt(31)
//#define XX SayIt(38)
//#define XX SayIt(39)
#define aAW SayIt(32)
#define aDD2 SayIt(33)
#define aGG3 SayIt(34)
#define aVV SayIt(35)
#define aGG1 SayIt(36)
#define aSH SayIt(37)
#define aZH SayIt(38)
#define aRR2 SayIt(39)
//#define XX SayIt(48)
//#define XX SayIt(49)
#define aFF SayIt(40)
#define aKK2 SayIt(41)
#define aKK1 SayIt(42)
#define aZZ SayIt(43)
#define aNG SayIt(44)
#define aLL SayIt(45)
#define aWW SayIt(46)
#define aXR SayIt(47)
//#define XX SayIt(58)
//#define XX SayIt(59)
#define aWH SayIt(48)
#define aYY1 SayIt(49)
#define aCH SayIt(50)
#define aER1 SayIt(50)
#define aER2 SayIt(52)
#define aOW SayIt(53)
#define aDH2 SayIt(54)
#define aSS SayIt(55)
//#define XX SayIt(68)
//#define XX SayIt(69)
#define aNN2 SayIt(56)
#define aHH2 SayIt(57)
#define aOR SayIt(58)
#define aAR SayIt(59)
#define aYR SayIt(60)
#define aGG2 SayIt(61)
#define aEL SayIt(62)
#define aBB2 SayIt(63)

//Prototypes
void InitPorts (void);
void Delay (u32 count);
uint8_t ReadByteFromEeprom(void);
void WriteByteToEeprom(uint8_t x);
void TestIt(void);
void SayIt(u16 allophone);
//phrases
void IamTalking(void);
void FreakazoidRobots(void);
void HelloLila(void);
void RandoAllophone(void);
void Yes(void);
void No(void);
void AsISeeItYes(void);
void AskAgainLater(void);
void BetterNotTellYouNow(void);

//variables
uint8_t EEMEM EEVar;
uint8_t ByteOfData;
volatile u16 anAllophone = 5;

void delayms( uint16_t millis ) {
	while ( millis ) {
		_delay_ms( 1 );
		millis--;
	}
}
int main(void)			//program start
{
	//u8 btnState;
	
	u16 aBoolean;
	ByteOfData = ReadByteFromEeprom ();

	anAllophone = (u16)ByteOfData;
	aBoolean = 0;

	InitPorts();
	aPowerOn;
	LEDON;
	delayms(250);

	//Total Number of Phrases
	const u16 AllDuhPhrases = 8;

	while(forever)
	{

			aPowerOn;
			delayms(250);aPA1;
			SpeakerOn;
			switch (anAllophone)
			{
				case 0 : aPA1;
				break;

				case 1 : BetterNotTellYouNow();
				break;

				case 2 : AskAgainLater();
				break;

				case 3 : HelloLila();
				break;

				case 4 : FreakazoidRobots();
				break;

				case 5 : Yes();
				break;

				case 6 : No();
				break;

				case 7 : AsISeeItYes();
				break;
			}
			delayms(250);
			SpeakerOff;
			anAllophone++;
			if (AllDuhPhrases <= anAllophone) 
			{
				anAllophone = 1;//set to 5 to only do "Yes()" and "No()"
			}
			ByteOfData = (uint8_t)anAllophone;
			WriteByteToEeprom (ByteOfData);
			delayms(999);
			aPowerOff;
		}
	//}
	return (0);
}


//read byte function

uint8_t ReadByteFromEeprom(void)
{ 
   uint8_t temp; 
   temp = eeprom_read_byte(&EEVar);
   return(temp); 
}

// read byte usage
//ByteOfData = ReadByteFromEeprom ();

//write byte function
void WriteByteToEeprom(uint8_t x)
{ 
   eeprom_write_byte (&EEVar, x); 
}
// write byte usage
//WriteByteToEeprom (ByteOfData);

void InitPorts(void)
{
	DDRD = 255;			//set port D for output
	DDRC=0;
	DDRB = 255;			//set port B for output
	PORTB = 0;			//set port B pins to 0
	DDRC = 0;			//set port C for input
	PORTD |= (1<<PD3);	//set reset bit to 1 PORTD
	//PORTD |= (1<<PD0);
}

void Delay(u32 count)
{
	while(count--);
}

void TestIt(void)
{
	PORTB = 5;		//set port B to AY
	LEDOFF;
	PORTB |= (1<<PB6);
	
	while(~PINC & _BV(PC3))//while zero, voltage high
	{
		LEDON;
	}
	LEDOFF;
}

void SayIt(u16 allophone)
{
	LEDON;
	PORTB = allophone; //set the allophone
	LEDOFF;
	PORTB |= (1<<PB6); //trigger it
	LEDON;
	while(~PINC & _BV(PC3))//wait for it to finish
	{
		//just wait
	}
		LEDOFF;
}
// **************************************************
// **************************************************
// SAY STUFF
// **************************************************
// **************************************************
void IamTalking(void)
{
			aPA5;
			aHH1;aHH1;aEY;aPA5;aPA5;aPA5;aPA5;//hey
			aAA;aAY;aPA5;aPA5;//I
			aAE;aAE;aMM;aPA3;//am
			aTT2;aAO;aAO;aPA3;aKK1;aIH;aNG;aPA5;//talking
			aTT2;aUW1;aPA3;//to
			aYY1;aYY1;aUW1;aUW1;aUW1;aPA5;//you
			aPA5;
			aPA5;
}


void FreakazoidRobots(void)
{
	aPA5;
	aFF;aFF;aRR1;aIY;aKK2;aAX;aZZ;aOW;aIY;aDH2;aPA5;//freakazoid
	aRR1;aOW;aPA2;aBB2;aAA;aPA3;aTT1;aSS;aPA5;aPA5;//robots
	aPP;aLL;aIY;aSS;aPA5;//please
	aRR1;aIY;aPP;aAX;aOW;aRR2;aTT2;aPA5; //report
	aTT1;aUW2;aPA5;//to
	aDH1;aAX;aPA5;aPA3;//the
	aDD1;aAE;aAE;aNN2;aSS;aSS;aPA5;//dance
	aFF;aEL;aOR;aOR;aPA5;//floor
}
void HelloLila(void)
{
			aPA5;
			aHH1;aEH;aLL;aAX;aOW;
			aLL;aAY;aLL;aAX;//Lila
			aPA5;
			aPA5;
}
void RandoAllophone(void)
{
	u16 i;

	for (i=1; i <= 65; ++i)
	{
		SayIt(i);aPA1;
	}

}
void Yes(void)
{
	aYY2;aEH;aEH;aSS;aSS;aPA5;//yes
}

void No(void)
{
	aNN2;aAX;aOW;aPA5;//yes
}

void AsISeeItYes(void)
{
aAE;aZH;aPA5;				//as
aAA;aAY;aPA5;aPA5;			//I
aSS;aSS;aIY;aPA5;			//see
aIH;aTT1;aPA5;				//it
aYY2;aEH;aEH;aSS;aSS;aPA5;	//yes
}

void AskAgainLater(void)
{
aAE;	aSS;	aKK2;	aPA5;	//ask
aAE;	aGG3;	aAE;	aNN1;	aPA5;	//again
aLL;	aEH;	aEY;	aPA3;	aTT2;	aER1;	//later
}

void BetterNotTellYouNow(void)
{
aBB2;	aEH;	aEH;	aPA3;	aTT2;	aER1;	//better
aNN2;	aAA;	aPA3;	aTT2;	aPA5;	//not	
aTT2;	aEH;	aEH;	aLL;	aPA5;	//tell
aYY1;aYY1;aUW1;aUW1;aUW1;aPA5;//you					
aNN2;	aAW;	aPA5;	//now		
}
