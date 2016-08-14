//Display Serial inside of functions and make sure to make a universal winning score 

#include <reg932.h>
#include <uart.h>
#include <main.h>

sbit cycleMode=P2^1;
sbit selectMode=P2^2;
sbit buzzer=P1^7;

sbit led0=P2^4;
sbit led1=P0^5;
sbit led2=P2^7;
sbit led3=P0^6;
sbit led4=P1^6;
sbit led5=P0^4;
sbit led6=P2^5;
sbit led7=P0^7;
sbit led8=P2^6;

sbit button0=P2^0;
sbit button1=P0^1;
sbit button2=P2^3;
sbit button3=P0^2;
sbit button4=P1^4;
sbit button5=P0^0;
sbit button6=P2^1;
sbit button7=P0^3;
sbit button8=P2^2;

short score=0;

char won = 0;

code short notes[9] = {500, 750, 1000, 1250, 1500, 1750, 2000, 2250, 2500};

short randomAddition = 20;

char numberOfLedsToLight = 0;

char changeMode = 0;

void main(void)
{
    char mode = 0;

	EA = 1;
	EX1 = 1;

    P0M1 = 0x00;
    P1M1 = 0x00;
    P2M1 = 0x00;
    
    //Initiliaze TMOD
    TMOD = 0x21;
    uart_init();
    EA = 1;
    
    while(1)
    {
        userSelectMode();
    }
}

void userSelectMode()
{    
    char mode=0;
    char isModeSelected = 0;
    while(!isModeSelected)
    {
        if(cycleMode == 0)
        {
            while(cycleMode == 0);
            mode++;
            mode = mode % 5;
            delay(0.10);
        }
        
        if(selectMode == 0)
        {
            while(selectMode == 0);
            isModeSelected = 1;
            delay(0.10);
        }
    }

	displayGame(mode);
	displayScore(0);

    switch(mode)
    {

        //Basic Mode
        case 0:
			basic();
            break;

        //Alex Mode
        case 1:
	   		alex();
            break;
 
        //Eli Mode
        case 2:
			eli();
            break;

        //Richard Mode
        case 3:
            richard();
            break;

        //Zach Mode
        case 4:
            zach();
            break;
    }
	displayYouWin(won);
}

void sound(short freq, short time)
{
    
    short n;
    short repeats;
    short a;
    short i;
    short rep;
    short tconTemp = TCON;
    n= (-7.37E6)/(freq*4);
    a = n;
    i=0;
    repeats = 1;
    rep = repeats;

    while (n>65536)
    {
        repeats++;
        rep = repeats;
        n = a/repeats;
    }

     while (i < time)
    {
        while (rep >= 1)
        {
            TH0=n>>8;
            TL0=n;
            TR0=1;
            while(!TF0);
            buzzer=~buzzer;
            TF0=0;
            rep--;
        }
        rep = repeats;
        i++;
    }
}

//blink determines whether LED should blink or stay on
void lightLed(char ledNumber, char blink, float ledLength)
{    
    switch(ledNumber)
    {
        case 0:    
            led0=0;
            if(blink == 1)
            {
                delay(ledLength);
                led0=1;
            }
            break;

        case 1:
            led1=0;
            if(blink == 1)
            {
                delay(ledLength);
                led1=1;
            }
            break;

        case 2:
            led2=0;
            if(blink == 1)
            {
                delay(ledLength);
                led2=1;
            }
            break;

        case 3:
            led3=0;
            if(blink == 1)
            {
                delay(ledLength);
                led3=1;
            }
            break;

        case 4:
            led4=0;
            if(blink == 1)
            {
                delay(ledLength);
                led4=1;
            }        
            break;
        
        case 5:
            led5=0;
            if(blink == 1)
            {
                delay(ledLength);
                led5=1;
            }
            break;        
    

        case 6:
            led6=0;
            if(blink == 1)
            {
                delay(ledLength);
                led6=1;
            }        
            break;

        case 7:
            led7=0;
            if(blink == 1)
            {
                delay(ledLength);
                led7=1;
            }        
            break;    

        case 8:
            led8=0;
            if(blink == 1)
            {
                delay(ledLength);
                led8=1;
            }
            break;
    }
}


void basic()
{
    char ledSequence [14];
    char scored = 1; //Bool only 0 or 1
    score = 0;
	
    while(score < 15 && !changeMode)
    {
        char i;
        i=0;

        if(scored == 1)
        {
            addLeds(&ledSequence, 1, 2); //difficultyFactor = 1, numberOfLeds = 2
        }
        
        
        lightLedSequence(ledSequence, 1, 200, 0.5, 0); //ledLength = 1, soundLength = 200, delayBtwLedSound = 5;
        scored = playGame(ledSequence);
		
    	delay(0.5);

        if(scored)
        {
            score++;
			displayGame(0);
			displayScore(score);
        }
    }

	if(score == 15)
	{
		won = 1;
	}
}


void alex()
{
	char numberOfLedsToAdd = 0;
    //char difficultyFactor;
    char ledSequence [15];
    char scored = 1;            		//Bool only 0 or 1
    float delayBtwLedSound = 0.5; 		//Delay between the led and the sound
	score = 0;

    while(score < 5 && !changeMode)
    {
        char i = 0;
	

        numberOfLedsToAdd = random() % 3 + 1;
        
        if(scored == 1)
        {
            addLeds(&ledSequence, numberOfLedsToAdd, 9);
		
        }
        
        lightLedSequence(ledSequence, 1, 200, delayBtwLedSound, 1); 

        scored = playGame(ledSequence);    


		if(scored == 1)
        {

            score++;
			displayGame(1);
			displayScore(score);
        }
        
        delayBtwLedSound = random() % 100 + 1;                //Generate random delay time
        delayBtwLedSound /= 100;
    }

	if(score == 5)
	{
		won = 1;
	}
}



void eli()
{
    char ledSequence [14];
    char scored = 1; //Bool only 0 or 1

    while(score < 10 && !changeMode)
    {
        char i;
        i=0;

        if(scored == 1)
        {
            addLeds(&ledSequence, 1, 2); //difficultyFactor = 1, numberOfLeds = 2
        }
        
        
        //lightLedSequence(ledSequence, 1, 200, 5); //ledLength = 1, soundLength = 200, delayBtwLedSound = 5;

        for(i;i<numberOfLedsToLight; i++)
        {
            char ledIndex = 0;
            for(ledIndex;ledIndex<9;ledIndex++)
            {
                lightLed(ledIndex, 0, 500); // Doesn't blink
            }
            
            switch(ledSequence[i])
            {
                case 0:
                    led0 = 1;
                    break;
                case 1:
                    led1 = 1;
                    break;
                case 2:
                    led2 = 1;
                    break;
                case 3:
                    led3 = 1;
                    break;
                case 4:
                    led4 = 1;
                    break;
                case 5:
                    led5 = 1;
                    break;
                case 6:
                    led6 = 1;
                    break;
                case 7:
                    led7 = 1;
                    break;
                case 8:
                    led8 = 1;
                    break;

            }
            sound(notes[ledSequence[i]], 500);
            delay(0.5);
            led0=1;
            led1=1;
            led2=1;
            led3=1;
            led4=1;
            led5=1;
            led6=1;
            led7=1;
            led8=1;
        }

        scored = playGame(ledSequence);

        if(scored)
        {
            score++;
			displayGame(2);
			displayScore(score);
        }
    
    }

	if(score == 5)
	{
		won = 1;
	}
}

void richard()
{
    char ledSequence [14];
    char scored = 1; //Bool only 0 or 1

    while(score < 5 && !changeMode)
    {
        char i;
        i=0;
        
        if(scored == 1)
        {
            addLeds(&ledSequence, 2, 2); //difficultyFactor = 2, numberOfLeds = 2
        }
        
        
        lightLedSequence(ledSequence, 1, 200, 0.5, 0); //ledLength = 1, soundLength = 200, delayBtwLedSound = 0.5

        scored = playGame(ledSequence);

        if(scored)
        {
            score++;
	displayGame(4);
	displayScore(score);
            if(score == 2) //if score == half of winning score
            {
                ledInterlude();
            }
        }
    }

    if(score == 5)
    {
        won = 1;
     }
}

void ledInterlude()
{
    short freq=2000;
    
    while (freq>500)
    {
        sound(freq, 75);
        led0=~led0;
        led2=~led2;
        led4=~led4;
        led6=~led6;
        led8=~led8;
        freq-=50;
    }
    while (freq<2000)
    {
        led1=~led1;
        led3=~led3;
        led5=~led5;
        led7=~led7;
        sound(freq, 75);
        freq+=50;
    }
}


void zach()
{
    char won = 0;
    char ledSequence [14];
    char scored = 1;  //Bool only 0 or 1
    float ledLength = 2;  //Initialize for led speed
    short soundLength = 400;  //Initialize for sound speed
    float delayBtwLedSound = 1 ; //Dleay between the led and the sound

    while(score < 5 && !changeMode)
    {
           char i;
           i=0;
          
           if(scored == 1)
           {
               addLeds(&ledSequence, 2, 3); //difficultyFactor = 2, numberOfLeds = 3
           }
          
           lightLedSequence(ledSequence, ledLength, soundLength, delayBtwLedSound, 0);
    
           scored = playGame(ledSequence);
       
           delay(0.5);
          
           if(scored == 1)
           {
               score++;
               ledLength = (ledLength*0.75);
               soundLength = (soundLength/2);
               delayBtwLedSound = (delayBtwLedSound *0.75);
           }
    
           displayScore(score);
       
           //Toggle Lights at the bottom to distract
           led6 = ~led6;
           led7 = ~led7;
           led8 = ~led8;
          
           if(score == 6)
           {
               won = 1;
               led3 = 0;
               led4 = 0;
               led5 = 0;
               led6 = 0;
               led7 = 0;
               led8 = 0;
               delay(5);
           }
    }
}


void delay(float secondsOfDelay) //Side effect: TR0 is turned off. TR0 will be reloaded with value at the end of the function
{
    short numberOfLoops;
    short tconTemp;
    TR0=0;
    numberOfLoops=1000*secondsOfDelay;
    
    for(numberOfLoops;numberOfLoops>0;numberOfLoops--)
    {
        TH0=-3686>>8;
        TL0=-3686;
        TR0=1;
        while(!TF0);
        TF0=0;
        TR0=0;
        tconTemp = TCON;
    }
}

void displayScore(short score)
{
	char charArrayScore[2];
	//char leastSignificantDigit = score;
	short temp = score % 10;
	
	charArrayScore[0] = temp + 48;

	temp = score - temp;
    charArrayScore[1] = temp + 48;
	
	

    uart_transmit('S');
    uart_transmit('c');
    uart_transmit('o');
    uart_transmit('r');
    uart_transmit('e');
    uart_transmit(':');
	uart_transmit(charArrayScore[1]);
	uart_transmit(charArrayScore[0]);
	/*if(score > 9)
	{
		uart_transmit('1');
		leastSignificantDigit = score - (score % 10);
	}


	switch(leastSignificantDigit)
	{
		case 0:
			uart_transmit('0');
			break;
		case 1:
			uart_transmit('1');
			break;
		case 2:
			uart_transmit('2');
			break;
		case 3:
			uart_transmit('3');
			break;
		case 4:
			uart_transmit('4');
			break;
		case 5:
			uart_transmit('5');
			break;
		case 6:
			uart_transmit('6');
			break;
		case 7:
			uart_transmit('7');
			break;
		case 8:
			uart_transmit('8');
			break;
	   	case 9:
			uart_transmit('9');
			break;
	}*/

    clearLine();
}

void displayGame(short mode)
{
    uart_transmit('G');
    uart_transmit('a');
    uart_transmit('m');
    uart_transmit('e');
    uart_transmit(':');

    if(mode == 0)
    {
        uart_transmit('1');
    }

    else if(mode ==1)
    {
        uart_transmit('2');
    }

    else if(mode == 2)
    {
        uart_transmit('3');
    }

    else if(mode == 3)
    {
        uart_transmit('4');
    }

    else if(mode == 4)
    {
        uart_transmit('5');
    }

	uart_transmit(32);
}

void displayYouWin(char won)
{
	if(won == 1)
	{
	    clearLine();
	    uart_transmit('Y');
	    uart_transmit('o');
	    uart_transmit('u');
	    uart_transmit(' ');
	    uart_transmit('H');
	    uart_transmit('a');
	    uart_transmit('v');
	    uart_transmit('e');
	    uart_transmit(' ');
	    uart_transmit('W');
	    uart_transmit('o');
	    uart_transmit('n');
	    uart_transmit('!');
	    uart_transmit('!');
	    uart_transmit('!');
		clearLine();
	}
}

void addLeds(char *randomLeds, char difficultyFactor, char numberOfLeds) //Must use address of operator to allow for pass by reference
{
    char i = 0;

    for(i; i < difficultyFactor; i++)
    {
        randomLeds[numberOfLedsToLight+i] = random() % numberOfLeds;
    }
    numberOfLedsToLight += difficultyFactor;

}

//If dudPossible == 1, there is a chance an LED without an accompanying sound will be blinked
void lightLedSequence(char ledSequence [], float ledLength, short soundLength, float delayBtwLedSound, char dudPossible)
{
    char i;
    i=0;
    for(i;i<numberOfLedsToLight; i++)
    {
        ledLength = 1;
        lightLed(ledSequence[i], 1, ledLength);
        sound(notes[ledSequence[i]], soundLength);
        delay(delayBtwLedSound);

        if(dudPossible == 1)
        {
            if(random() % 2 == 1) //Randomly selects if dud will appear
            {
                lightLed(random() % 9, 1, ledLength); //Randomly selects which led will be a dud
                
                delayBtwLedSound = random() % 100 + 1; //Generate random delay time
                delayBtwLedSound /= 100;

                delay(delayBtwLedSound);
            }
        }
    }
}


char playGame(char ledSequence [])
{
	
    char i = 0;
    char failed = 0;
	//led4 = 0;						//test
	
	
    while(numberOfLedsToLight > i && !failed)
    {
		//led5 = 0;					//test
        while(button0 && button1 && button2 && button3 && button4 && button5 && button6 && button7 && button8);
		//led6 = 0;					//test
        switch(ledSequence[i])
        {
            case 0:
                if(button0 != 0)
                {
                    failed = 1;
                }
                break;
            case 1:
                if(button1 != 0)
                {
                    failed = 1;
                }
                break;
            case 2:
                if(button2 != 0)
                {
                    failed = 1;
                }
                break;
            case 3:
                if(button3 != 0)
                {
                    failed = 1;
                }
                break;
            case 4:
                if(button4 != 0)
                {
                    failed = 1;
                }
                break;
            case 5:
                if(button5 != 0)
                {
                    failed = 1;
                }
                break;
            case 6:
                if(button6 != 0)
                {
                    failed = 1;
                }
                break;
            case 7:
                if(button7 != 0)
                {
                    failed = 1;
                }
                break;
            case 8:
                if(button8 != 0)
                {
                    failed = 1;
                }
                break;
			
        }
		//led7 = 0;						//test
        while(!button0 || !button1 || !button2 || !button3 || !button4 || !button5 || !button6 || !button7 || !button8);
		//led8 = 0;						//test
        delay(0.25);
        i++;
    }
	//led5 = 0;							test
    return !failed;
}

short random()            //value of TL1 at the end of the delay is the "random" value returned
{
    short i = 0;
    randomAddition *= 1941;
    randomAddition /= 7;
    randomAddition %= 1000;
    TH1 = randomAddition >> 8;
    TL1 = randomAddition;
    TR1 = 1;
    
    while(i < randomAddition)
    {
        i++;
    }
    
    TR1 = 0;
    TF1 = 0;
    return TL1;
}


void clearLine()
{
	uart_transmit('\r');
}

void isrChangeGameMode() interrupt 2 using 1
{
	changeMode = 1;
	score = 0;
	led4=~led4; //Testing
	delay(0.25);
	led0=1;
	led1=1;
	led2=1;
	led3=1;
	led4=1;
	led5=1;
	led6=1;
	led7=1;
	led8=1;
}


