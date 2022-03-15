#ifndef _WATER_H
#define _WATER_H

int levelMax = A0; //Probe declarations
int levelFull = A1;
int levelHalf = A2;
int levelStop = A3;
int Overide = A4; //Button for user overide to  stop system

int fillPump = 7; //pump for filling solution tank with pure water
int outPump = 6; //pump for transporting solution to plants
int dosingPump1 = 5; //dosing pump for nutrients
int dosingPump2 = 4;
int dosingPump3 = 3;
int dosingPump4 = 2;

int ledGreen = 13;
int ledYellow = 12;
int ledRed = 11;

#endif
