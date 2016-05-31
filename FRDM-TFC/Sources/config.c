/*
 * config.c
 *
 *  Created on: May 23, 2016
 *      Author: Darkp
 */
#include "TFC\TFC.h"

/* enth�lt Variablen, die global (=im ganzen Programm) genutzt werden.
 * Mithile dieser werden grundeinstellungen am gesamten Programm vorgenommen, damit man bei kleineren
 * �nderungen nicht alles einzeln in verschiedenen classen �ndern muss*/


	const int motor = 1;					//nutzt motorport 2, da port 1 merkw�rdigerweise auf kein Signal reagiert (Motorport 1 w�re 0)
	const int servo = 0;					//variable f�r den SErvo (nur einer angeschlossen -> 0
	const int LEDconfig = 0;				//Values: 0 -> display speed; 1 -> display direction (nutzt die 4 LEDs um verschiedenes anzuzeigen)
	const int target = 5000;				//target value for fine line scam data, momentan nicht benutzt
	const float auslmultiplier = 1;			//gesamte servoauslenkung anpassen
	const float speedMultiplier =  1; 		//all geschwindkeitswerte �ndern
	const float minSpeed = 0.13;			//minimale geschwindkeit
	const int linetimeout = 700;			//Zeit bis automatisch abbricht ohne linie
	const int ruckwartsZeit = 800;			//zeit wie lange versucht wird r�ckw�rts die Linie zu finden
