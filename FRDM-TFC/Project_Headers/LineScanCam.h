/*
 * LineScanCam.h
 *
 *  Created on: May 23, 2016
 *      Author: Darkp
 */

#ifndef LINESCANCAM_H_
#define LINESCANCAM_H_

void loadCameraData();
void calcquarterLED(int Data[128]);
int getBlackPos();
int getLowestIndex (int array[], int wantValue, int length);
void calcdirection();
void calibcam();
void checkforLine();
int camData[128];
int active; 	//0 = false; !0 = true;
float Sausl;
int linemissing;
int checkLineStep;


#endif /* LINESCANCAM_H_ */
