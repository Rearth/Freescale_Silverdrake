/*
 * LEDs.c
 *
 *  Created on: May 23, 2016
 *      Author: Darkp
 */
#include "TFC\TFC.h"

/* In dieser Class sind alle Methoden enthalten die
 * zur ansteuerung der LEds genutzt werden
 */

void AllLEDsON() {				//sch�lt alle 4 LEDs an
	
	TFC_BAT_LED0_ON;
	TFC_BAT_LED1_ON;
	TFC_BAT_LED2_ON;
	TFC_BAT_LED3_ON;
	
}

void AllLEDsOFF() {								//sch�lt alle LEDS aus falls in der config class der modus auf die
												//geschwindkeitsanzeige gestellt ist
	if (LEDconfig == 0 && active == 1) {
		TFC_BAT_LED0_OFF;
		TFC_BAT_LED1_OFF;
		TFC_BAT_LED2_OFF;
		TFC_BAT_LED3_OFF;
	}
}
void forceAllOff() {							//sch�lt alle LEDs aus
		
	TFC_BAT_LED0_OFF;
	TFC_BAT_LED1_OFF;
	TFC_BAT_LED2_OFF;
	TFC_BAT_LED3_OFF;
}


int curNum = 0;

void animLEDs() {								//l�sst die LEDs animiert blinken, wird aber momentan nicht benutzt
	
	curNum++;									//erh�ht "curNum" (=current Number") um 1, falls diese bei 4 ist wird sie auf 0 gesetzt
	if (curNum < 4) {
		curNum = 0;
	}
	
	switch (curNum) {							//abh�ngig von curNum werden unterschiedliche LEDs angeschalten
	default:									//da f�r curNum immer ein Wert eingetragen ist wird kein default case ben�tigt
	case 0:
		TFC_BAT_LED0_OFF;
		TFC_BAT_LED1_OFF;
		TFC_BAT_LED2_OFF;
		TFC_BAT_LED3_OFF;
		break;									//break beendet die switch schleife und verhindert dass die anderer f�lle ausgef�hrt werden
	case 1:
		TFC_BAT_LED0_ON;
		TFC_BAT_LED1_OFF;
		TFC_BAT_LED2_OFF;
		TFC_BAT_LED3_OFF;
		break;
	case 2:
		TFC_BAT_LED0_ON;
		TFC_BAT_LED1_ON;
		TFC_BAT_LED2_OFF;
		TFC_BAT_LED3_OFF;
		break;
	case 3:
		TFC_BAT_LED0_ON;
		TFC_BAT_LED1_ON;
		TFC_BAT_LED2_ON;
		TFC_BAT_LED3_OFF;
		break;
	case 4:
		TFC_BAT_LED0_ON;
		TFC_BAT_LED1_ON;
		TFC_BAT_LED2_ON;
		TFC_BAT_LED3_ON;
		break;
	}
	
}

void LEDs_speedIndic (float speed) {			//geschwindkeitsanzeige mithilfe der LEDs
	
	if (LEDconfig == 0 && active == 1) {		//wird nur ausgef�hrt wenn die variable in der config class
		 	 	 	 	 	 	 	 	 	 	//entsprechend bestimmt ist
		if (speed < 0) {						//verhindert dass mit negativen Werten gerechnet ist (beim r�ckwartsfahren)
			speed = speed * (-1);
		}
		
		if (speed > 0.15) {						//hier werden verschiedene LEDs je nach geschwindkeit
			TFC_BAT_LED0_ON;					//angeschalten
			TFC_BAT_LED1_OFF;
			TFC_BAT_LED2_OFF;
			TFC_BAT_LED3_OFF;
		} else {
			TFC_BAT_LED0_OFF;
			TFC_BAT_LED1_OFF;
			TFC_BAT_LED2_OFF;
			TFC_BAT_LED3_OFF;		
		}
		if (speed > 0.28) {
			TFC_BAT_LED0_ON;
			TFC_BAT_LED1_ON;
			TFC_BAT_LED2_OFF;
			TFC_BAT_LED3_OFF;
		}
		if (speed > 0.38) {
			TFC_BAT_LED0_ON;
			TFC_BAT_LED1_ON;
			TFC_BAT_LED2_ON;
			TFC_BAT_LED3_OFF;
		}
		if (speed > 0.5) {
			TFC_BAT_LED0_ON;
			TFC_BAT_LED1_ON;
			TFC_BAT_LED2_ON;
			TFC_BAT_LED3_ON;
		}
	}
	
}

void showDirection (int num) {					//Methode zur richtungsanzeige mithilfe der LEDS
	
	if (LEDconfig == 1 && active == 1) {		//wird nur ausgef�hrt wenn die LEDconfiguration entsprechent eingestellt ist
		
		switch(num) {							//je nach richtungswert wird eine andere LED aktiviert
			case 4:
				TFC_BAT_LED0_ON;
				TFC_BAT_LED1_OFF;
				TFC_BAT_LED2_OFF;
				TFC_BAT_LED3_OFF;
				break;
			case 3:
				TFC_BAT_LED0_OFF;
				TFC_BAT_LED1_ON;
				TFC_BAT_LED2_OFF;
				TFC_BAT_LED3_OFF;
				break;
			case 2:
				TFC_BAT_LED0_OFF;
				TFC_BAT_LED1_OFF;
				TFC_BAT_LED2_ON;
				TFC_BAT_LED3_OFF;
				break;
			case 1:
				TFC_BAT_LED0_OFF;
				TFC_BAT_LED1_OFF;
				TFC_BAT_LED2_OFF;
				TFC_BAT_LED3_ON;
				break;
				
		}
	}
	
}


