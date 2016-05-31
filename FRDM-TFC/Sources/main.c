/*
 * LineScanCam.h
 *
 *  Created on: May 23, 2016
 *      Author: Darkp
 */

#include "derivative.h" //enthält Unterstützung für bestimmt peripherie
#include "TFC\TFC.h"	//enthält alle anderen wichtigen classes
#include <inttypes.h>	//enthält Unterstützung für verschiedene integer-arten (uint8/uint16,...)
#include <stdio.h>		//enthält Methoden für die Textdarstellung


/* Hauptclasse, hier werden alle wichtigen Methoden aufgerufen*/

int curblink = 0;		//wird in der main class für die benachrichtung, dass das hauptprogramm noch nicht gestartet ist, benutzt
	
int main(void)
{
	TFC_Init();			//intitialisiert alle wichtigen komponenten (IO Pins, Camera, Terminal, ...)		
	
	TERMINAL_PRINTF(" \r\n");															//Willkommensnachricht im Terminal
	TERMINAL_PRINTF("---------------------------------------------------- \r\n");		//Da keine UART tools vorhanden sind kann
	TERMINAL_PRINTF("  Freescale-Cup Programm von Bill Hu/David Waidner \r\n");			//das Terminal nur über den Seriellen Port gesehen werden,
	TERMINAL_PRINTF("---------------------------------------------------- \r\n");		//dazu wird ein ausleseprogramm dazu benötigt, wir nutzen "Putty"
	TERMINAL_PRINTF(" \r\n");															//der benötigte port kann im gerätemanager nachgesehen werden, die 
																						//refresh-rate muss auf 115200 gestellt werden
	for(;;) {				//Hauptschleife, wird dauerhaft wiederholt
		TFC_Task();			//hält grundprozesse am laufen, u.a. das Terminal
		
		if(TFC_Ticker[0]>=20) {		//wird alle 20 ms ausgeführt (jedesmal wenn der ticket 20 ms erriecht wird diese Methode ausgeübt und
			TFC_Ticker[0] = 0;		//der Ticker wird wieder auf 0 gesetzt)
			
			if (active == 0) {					//falls Hauptpgrogramm noch nicht aufgerufen wurde, kann zum testen benutzt werden
				float pot1 = TFC_ReadPot(0);	//liest potentiometer 1 (gibt werte zwischen -1 und 1 zurück)
				setServo(pot1);					//setzt den Servo auf den Wert dieses Potentiometers
				
				float pot2 = TFC_ReadPot(1);	//liest potentiometer 2
				setMotorSpeed(pot2);			//setzt motor auf den Wert des 2. Potentiometers
			}
			
			
			if(TFC_Ticker[1] >= 100) {		//2. Ticker. Diese Schleife wird alle 100 ms ausgeführt
				TFC_Ticker[1] = 0;
				loadCameraData();			//lädt die aktuellen Kameradaten in das int-array "camData"
				calcquarterLED(camData);	//setzt die Led-richtungsanzeige
				
				if (active == 1) {			//falls hauptprogramm läuft wird dies ausgeführt
					calcdirection();		//berechnet in welche richtung gefahren werden muss
					setServo(Sausl);		//justiert den servo in die neue richtung
					checkforLine();			//prüft ob sich die Linie noch im Sichtfeld befindet
				}
			}
			
			
			if(TFC_PUSH_BUTTON_0_PRESSED) {	//falls Knopf 1 gedrückt wird, started in der Funktion "calbcam" das
				calibcam();					//Hauptprogramm bzw. die automatische steuerung und die variable "active" wird auf true bzw. 1 gesetzt
			}
			if(TFC_PUSH_BUTTON_1_PRESSED) {	//benutzt um Hauptprogramm wieder auszuschalten
				active = 0;
			}
			
		}
		
		if(TFC_Ticker[2]>=150) {		//benachrichtung dass das Hauptprogramm noch nicht läuft, lässt
										//die LEDs alle 150 ms blinken
			TFC_Ticker[2] = 0;
			
			if (active == 0) {
				if (curblink == 0) {
					AllLEDsON();
					curblink = 1;
				} else if (curblink == 1) {
					forceAllOff();
					curblink = 0;
				}
			}
			
		}
		
		if(TFC_Ticker[3]>= linetimeout && linemissing == 1) {		//teil der Methode zum überprüfen ob die Linie
																	//noch im Sichtfeld ist (nach 300 ms beendet es automatisch)
			active = 0;
			linemissing = 0;
			driveBacktoLine();
		}
		
		if(TFC_Ticker[4] >= ruckwartsZeit) {						//falls der Timer fürs rückwärtsfahren abgeloffen ist, wird es abgebrochen
			
			drivingBack = 0;
		
		}
				
	}
	
	return 0;
}
