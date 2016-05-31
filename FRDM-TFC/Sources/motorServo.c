/*
 * motorServo.c
 *
 *  Created on: May 25, 2016
 *      Author: Darkp
 */

#include "TFC\TFC.h"		//enth�lt alle wichtigen anderen Methoden

float Motorspeed;		//enth�lt die aktuelle geschwindigkeit (von -1 bis 1)
float Servoausl;		//gibt die aktuelle Servoauslenkung an (von -1 bis 1)
int drivingBack = 0;	//angabe ob es gerade zur�ckf�hrt

void setServo(float ausl) {			//justiert den Servo
	
	float value;					//lokale variable
	value = (ausl * auslmultiplier) * 0.6 - 0.35;		//reduziert die auslenkung, da der Servo bei 1 / -1 stark an das Geh�use dr�ckt.
									//bewegt den servo zus�tzlic um 35% auf eine Seite, da er bei null nicht exakt in nullstellung ist
	Servoausl = value;				//setzt die globale variable
	TFC_SetServo(servo, value);		//setzt den Servo auf den Zielwert
	
}

void setMotorSpeed(float speed) {				//Methode um die Motorengeschwindigkeit zu setzen
	
	speed = speed * speedMultiplier;			//erh�ht/senkt die geschwindigkeit, je nachdem was f�r eine zahl in der config class eingetragen ist
	
	if (speed >= -minSpeed && speed <= minSpeed) {	//wenn die geschwindkeit ca. bei 0 null
		TFC_HBRIDGE_DISABLE;				//sch�lt den Motor aus, setzt die  geschwindkeit auf 0
		TFC_SetMotorPWM(motor,0);
		AllLEDsOFF();						//sch�lt LEDs aus
	} else {
		TFC_HBRIDGE_ENABLE;					//Sch�lt die Motoren an
		TFC_SetMotorPWM(motor, speed);		//setzt die Motorengeschindigkeit
		LEDs_speedIndic(speed);				//Motor-geschwindkeitsanzeige mithilfe der LEDs
	}
	Motorspeed = speed;						//setzt die globale variable
	
}

void calcMotorSpeed(int pos) {					//methode zur automatischen Berechnung einer Sinnvollen geschwindkeit
	
	if (drivingBack == 0) {						//falls gerade zur�ckgefahren wird
	
		if (pos <= 32) {						//je nachdem wo die schwarze Linie ist (variable: pos) wird die
			setMotorSpeed(0.17);				//geschwindkeit des Motors ge�ndert. Die Mitte ist bei 64
		} else if (pos <= 45) {
			setMotorSpeed(0.24);
		} else if (pos <= 55) {
			setMotorSpeed(0.33);
		} else if (pos <= 75) {
			setMotorSpeed(0.38);
		} else if (pos <= 85) {
			setMotorSpeed(0.33);
		} else if (pos <= 95) {
			setMotorSpeed(0.24);
		} else if (pos <= 128) {
			setMotorSpeed(0.17);
		}
	
	}

	TERMINAL_PRINTF(" CamData: %d", camData[8]);			//Schreibt beispieldaten in das Terminal um zu sehen ob alles funktioniert
	TERMINAL_PRINTF(" I : %d", camData[64]);				//%d wird genutzt um das integer in einen Text/String umzuwandeln
	TERMINAL_PRINTF(" I : %d\r\n", camData[120]);			//"\r\n" beginnt danach eine neue Zeile
	
}

void driveBacktoLine() {									//f�hrt eine bestimmte zeit zur�ck in der Hoffnung die linie wieder zu finden
	
	TFC_Ticker[4] = 0;										//4. timer um bestimmte zeit lang zur�ckzufahren
	
	drivingBack = 1;
	setMotorSpeed(-0.3);
	
}



