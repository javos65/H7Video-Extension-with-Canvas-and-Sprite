/*****************************************************************************
* | File      	: Space Invaders Demo  / SpaceInvaders.ino
* | Function    :	Demo for Portenta C33  with HAT expansion board , SPI LCD with ILI9486 and BLE remote control interface
* | Info        : JV 2024
* | Github      : https://github.com/javos65/Portenta-C33-Space-Invaders
*----------------
* |	This version:   V2.0
* | Date        :   2024-03-16
* | IOriginal   :   Objecrtoriented setup : https://github.com/YXHYX/arduino-space-invaders
*
* Screen definitions
*
******************************************************************************/
#ifndef SCREEN_H
#define SCREEN_H
#include <Arduino.h>
#include "H7Canvas.h"

//
// SCREEN and GRAPHICS definitions for Game
//
//
//


extern G_image whiteroom;
extern G_image orb1;
extern G_image orb2;
extern G_image shadow1;
extern G_image shadow2;
extern G_image shadow3;
extern G_image shadow4;


extern G_image room565;
extern G_image room1555;
extern G_image room4444;

#endif  SCREEN_H