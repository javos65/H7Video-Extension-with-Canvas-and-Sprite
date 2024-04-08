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


//h7image setup
#define INVADER_Y 26
#define INVADER_X 36
#define BOMB_Y 10
#define BOMB_X 5
#define SPLASHX 480
#define SPLASHY 320

extern G_image Bomb;
extern G_image Invaders1_1;
extern G_image Invaders2_1;
extern G_image Invaders3_1;
extern G_image Invaders4_1;

extern const uint16_t Bomb_array[BOMB_Y][BOMB_X];
extern const uint16_t Invaders1_1_array[INVADER_Y][INVADER_X];
extern const uint16_t Invaders2_1_array[INVADER_Y][INVADER_X];
extern const uint16_t Invaders3_1_array[INVADER_Y][INVADER_X];
extern const uint16_t Invaders4_1_array[INVADER_Y][INVADER_X];
extern const uint16_t Splash[SPLASHY][SPLASHX]; 

#endif  SCREEN_H