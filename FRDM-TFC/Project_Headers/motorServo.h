/*
 * motorServo.h
 *
 *  Created on: May 25, 2016
 *      Author: Darkp
 */

#ifndef MOTORSERVO_H_
#define MOTORSERVO_H_

float Motorspeed;
float Servoausl;

void setServo(float ausl);
void setMotorSpeed(float speed);
void setMotor(int speed);
void calcMotorSpeed(int pos);
int drivingBack;
void driveBacktoLine();

#endif /* MOTORSERVO_H_ */
