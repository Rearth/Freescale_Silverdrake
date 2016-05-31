/*
 * LSamera.c
 *
 *  Created on: May 23, 2016
 *      Author: Darkp
 */

#include "TFC\TFC.h"

/* Enthält alle wichtigen Methoden diie etwas mit der Linienscancamera zu tun haben.
 * Die Linienscancamera scannt alle 10ms und speichert die helligkeitswerte in dem "LineScanImage0 array (ingesamt 128 Werte)*/

int camData[128];		//enthält die Daten die zur verarbeitung genutzt werden
int active = 0; 		//0 = false; !0 = true, gibt den Status der automatischen Steuerung an
float sAusl = 0;		//momentane auslenkungsvariable
int linemissing = 0;	//gibt an ob die Linie fehlt oder vorhanden ist (0 = false; 1 = true)
int checkLineStep = 100;

void loadCameraData() {	//Methode um die "rohen" Daten in ein zunutzenden Array zu bringen
	
	int num = 0;
	for (num = 0; num < 128; num++) {				//nimmt jeden Wert und setzt ihn in camData
		camData[num] = (int) LineScanImage0[num];
	}
	for (num = 0; num < 5; num++) {					//erhöht die Randwerte, da diese oftmals seltsame Werte enthalten
		camData[num] = camData[14] + 100;
	}
	for (num = 123; num < 128; num++) {
		camData[num] = camData[115] + 100;
	}
	
}

void calcquarterLED(int Data[128]) {			//Methode zur berechnung in welche Vierter sich die Linie befinden, 
												//um dies mit den 4 LEDs anzuzeigen
	int num;
	int val[5];									//locale variablen, die für die berechnungen benötigt werden (val = value)
	val[0] = 99999;
	int calcnum[5];								//calcnum = calculierte nummer
	for (num = 1; num < 5; num++) {val[num] = 0;}		//setzt alle werte des Arrays calcnum auf 0
	
	for (num = 0; num < 32; num++) {			//hier werden die durchschnittswerte für je 32 werte berechnet, insgesamt 4 mal		
		val[1] = val[1] + Data[num];
	}
	calcnum[1] = val[1] / 32 ;
	
	for (num = 32; num < 64; num++) {
		val[2] = val[2] + Data[num];
	}
	calcnum[2] = val[2] / 32;
	
	for (num = 64; num < 96; num++) {
		val[3] = val[3] + Data[num];
	}
	calcnum[3] = val[3] / 32;
	
	for (num = 96; num < 128; num++) {
		val[4] = val[4] + Data[num];
	}
	calcnum[4] = val[4] / 32;
	
	int lowestIndex = getLowestIndex(calcnum, 0, 5);		//findet heraus in welchem der vier Werte (viertel des Sichtfeldes)
															//der Wert am niedrigsten ist
	showDirection(lowestIndex);								//zeigt das ergebnis mithilfe der LEDs an
	
	
}

int getLowestIndex (int array[], int wantValue, int length) {		//methode zum herausfinden der Position der tiefsten Zahl im Array7
	
	int lnum = array[1];									//lowest number
	int lnumIndex = 1;										//position/index im array der niedrigsten nummer
	int Index = 1;											//Index auf den momentan geschaut wird
	
	
	for (Index = 0; Index < length; Index++) {				//nimmt jeden index im array, falls der Wert von diesem
		if (array[Index] < lnum && array[Index != 0]) {		//unter lnum ist wird lnum bzw. nlumIndex auf den Wert
			lnum = array[Index];							//von diesem gesetzt
			lnumIndex = Index;
		}
	}
	if (wantValue == 1) {									//falls der Wert der niedrigsten zahl zahl gewollt ist
		return lnum;
	} else {												//falls die arraypositin der niedrigsten Zahl gewollt ist
		return lnumIndex;
	}
}
			

int getBlackPos() {											//Methode zur berechnung der Stelle an der es am dunkelsten ist, mitte bei 0
		
	int rawPos = getLowestIndex(camData, 0, 128);			//findet die position des tiefsten Werts im Array camData
	calcMotorSpeed(rawPos);									//berechnet die Motorengeschwindkeit anhand dieses Werts
	int val = getLowestIndex(camData, 1, 128);				//berechnet den tiefsten Wert im array, nur zu infozwecken im Terminal
	int value = (rawPos - 64);								//setzt die Mitte bei null
	TERMINAL_PRINTF("Value: %d", val);
	TERMINAL_PRINTF(" I Index: %d", rawPos);				//gibt die Werte im terminal an
	
	return value;											//gibt den Zielwert zurück
	
}

void calibcam() {											//soll eigentlich noch die Kamera calibrieren, geht aber auch ohne
															//jetzt wird hierdurch nur das Hauptprogramm gestartet, falls
	if (active == 0) {									//es noch nicht gestartet ist

		int num = 0;									//locale Variablen
		int valbefore = camData[1];
		int val;
		int gesVal = 0;
					
		for (num = 5; num < 124; num++) {				//nimmt alle Werte des Camerascans von 5 bis 124, die randwerte werden weggelassen da 
														//diese oft nicht genau sind
			valbefore = camData[num - 1];				//wert der position direkt daneben
						
			if (valbefore > camData[num]) {				//berechnet den unterschied zwischen den beiden Werten
				val = valbefore - camData[num];
			} else {
			val = camData[num] - valbefore;
			}
			if (val >= gesVal) {
				gesVal = val;
			}
		}
		checkLineStep = gesVal * 0.8;					//um wv der Wert des nächsten Punkts in camData[128] mindestens abweichen muss,
												//damit das programm nicht abbricht (damit es eine "Linie" erkennt)
		
		
		
		TERMINAL_PRINTF("\r\n");
		TERMINAL_PRINTF("Calibriert!");
		forceAllOff();										//schält alle LEDs aus
		active = 1;
	}
		
}

void calcdirection() {										//methode zur Berechnung der Servoauslenkung
	
	float ausl = 0;
	if (linemissing == 0) {
		int targetloc = getBlackPos();										//findet heraus wo die Linie ist
		
		if (targetloc >= 54 && targetloc <= 74) {
			Sausl = 0;
		} else {
			ausl = (float) targetloc / 64.0 * (float) auslmultiplier;		//berechnet die auslenkung um der Linie zu folgen
			Sausl = ausl;														//setzt die globale Variable, mit welcher der Servo angesteuert wird
		}
		
		TERMINAL_PRINTF("     I %d", camData[1]);							//schreibt die Werte ins Terminal
		TERMINAL_PRINTF(" I %d", camData[30]);
		TERMINAL_PRINTF(" I %d", camData[60]);
		TERMINAL_PRINTF(" I %d", camData[90]);
		TERMINAL_PRINTF(" I %d", camData[115]);
		TERMINAL_PRINTF(" Auslenkung: %d\r\n", (int) (ausl * 10000));
		
	} else {
		Sausl = Sausl * 2;
		setMotorSpeed(Motorspeed * 0.8);
	}
	
}

void checkforLine() {										//Methode um zu prüfen ob die Linie noch im sichtfeld ist
	
			int num = 0;									//locale Variablen
			int valbefore = camData[1];
			int val;
			int gesVal = 0;
			
			for (num = 5; num < 124; num++) {				//nimmt alle Werte des Camerascans von 5 bis 124, die randwerte werden weggelassen da 
															//diese oft nicht genau sind
				valbefore = camData[num - 1];				//wert der position direkt daneben
				
				if (valbefore > camData[num]) {				//berechnet den unterschied zwischen den beiden Werten
					val = valbefore - camData[num];
				} else {
					val = camData[num] - valbefore;
				}
				if (val >= gesVal) {
					gesVal = val;
				}
			}
		
			if (gesVal <= checkLineStep) {					//falls der unterschied der beiden Werte zu klein ist wird keine
				TERMINAL_PRINTF(" LINE MISSING!");
				if (linemissing == 0) {						//linie gefunden, der automatische Modus wird deaktiviert
					linemissing = 1;
					if (TFC_Ticker[3] >=  linetimeout) {
						TFC_Ticker[3] = 0;
					}
				}
			} else  {										//linie vorhanden, variablen entsprechend setzen
				active = 1;
				linemissing = 0;
				TFC_Ticker[3] = 0;
			}

			TERMINAL_PRINTF("  Linestep: %d", gesVal);
			TERMINAL_PRINTF(" / %d\r\n", checkLineStep);
	
}









