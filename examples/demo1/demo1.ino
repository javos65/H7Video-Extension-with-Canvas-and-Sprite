/*
  Update 2024 : JV for Portenta H7
    - Test Sketch for Canvas-based H7 Video over USB-C

    Remark: Arduino-H7-video library support video over usb-c, but screws up the USB bus, both HS and FS bus are corrupted.
    Untill Mbed solves this, usb-keyboard use is not possible with usb-c video running.
*/

#include "Arduino.h"
#include "stdio.h"

#include "H7Canvas.h"    // for Canvas and Sprite functions
#include "DEBUGF.h"         // for Serial debugging
#include "Screen.h"         // for sprite data



void setup() {
  DEBUGFinit(38400);
  pinMode(LEDR, OUTPUT); digitalWrite(LEDR, HIGH);// red off
  randomSeed(analogRead(A3));randomSeed(analogRead(A4));randomSeed(analogRead(A3)); //for random ??
  
  CanvasAll_Init();  // init video , canvas buffer and  sprite buffer, check H7Canvas.h
  delay(1000);

  long tt=millis();
  for(int i=0 ;i< Canvas_height(); ++i) {
      for(int t=0; t<Canvas_width();++t) {
        *( (uint16_t*) RGB565Canvas + t + (i*Canvas_width()) )=  0xff553355+(i%256+t%32); // fill screen with pattern
       }
  }
  tt=millis()-tt;
  DEBUGF("*Test 1 : RGB565 Canvas pattern by CPU in %dms, speed KB/s: %d\n\r",tt,(Canvas_width()*Canvas_height()*2)/tt); 
  CanvasAll_DrawFrames(true);delay(2000);

  for(int i = 0 ; i <25; ++i){
  Invaders3_1.xpos = random(0, Canvas_width()-Invaders3_1.width);
  Invaders3_1.ypos = random(0, Canvas_height()/3);
  Canvas_DrawImage(Invaders3_1);    // Draw transparant picture : Sprite, formatted as G_image structure to Canvas
  }
    for(int i = 0 ; i <25; ++i){
  Invaders2_1.xpos = random(0, Canvas_width()-Invaders2_1.width);
  Invaders2_1.ypos = random(Canvas_height()/3, 2*Canvas_height()/3);
  Canvas_DrawImage(Invaders2_1);    // Draw transparant picture : Sprite, formatted as G_image structure to Canvas
  }
    for(int i = 0 ; i <25; ++i){
  Invaders1_1.xpos = random(0, Canvas_width()-Invaders1_1.width);
  Invaders1_1.ypos = random(2*Canvas_height()/3, Canvas_height());
  Canvas_DrawImage(Invaders1_1);    // Draw transparant picture : Sprite, formatted as G_image structure to Canvas
  }

  tt=millis();
  CanvasAll_DrawFrames(true);
  tt=millis()-tt;  DEBUGF("*Test 4 : Canvas+Sprite Image send to DSI %dms\n\r",tt);
 
   tt=millis();
  Canvas_DrawImage565((uint16_t*) Splash ,Sprite_x(),Sprite_y(),SPLASHX,SPLASHY); // draw opaque image
  tt=millis()-tt;  DEBUGF("*Test 2 : Canvas Imagedraw by DMA  %dms\n\r",tt);
  CanvasAll_DrawFrames(true);delay(1000);

  tt=millis();

  Printf_Canvas(10,10,YELLOW,2,"RGB656 Canvas %ix%i - %iKB",Canvas_width(),Canvas_height(),Canvas_width()*Canvas_height()*2); // print large text on Canvas buffer 
  Printf_Canvas(Sprite_x()+10,Sprite_y()+10,WHITE,1,"ARGB8888 Sprite Area %ix%i",Sprite_width(),Sprite_height()); // print text on Canvas buffer
  Canvas_FillRect(700,100,10,300,RED,0x80);
  Canvas_FillRect(20,30,10,400,MAGENTA,0xA0);
  Canvas_FillRect(40,30,10,400,MAGENTA,0x80);
  Canvas_FillRect(60,30,10,400,MAGENTA,0x60);
  Canvas_FillRect(20,455,650,20,WHITE,0xA0);
  Printf_Canvas(40,460,RED,1,"Canvas Video ram starts at = %x",(uint32_t) RGB565Canvas); // print large text on Canvas buffer 
  tt=millis()-tt;  DEBUGF("*Test 3 : Canvas Text and Rect in %dms\n\r",tt);
  CanvasAll_DrawFrames(true);delay(1000);

  delay(1000);digitalWrite(LEDR, LOW);
}

void loop() {
  // Speed test wit hfull grapics and 3 color types of sprite.
uint32_t tx,tt = millis();
uint16_t s,xp ,xp1;
uint16_t yp1,yp2,yp3,yp4 = Sprite_height()/2;
yp1=yp4;yp2=yp4;yp3=yp4;

while(1) {
      tx=micros();
      for(int t=0;t<240;++t){
      xp+=12 ; if (xp>Sprite_width()) xp-=Sprite_width();//random(Canvas_height()/2,Canvas_height()-INVADER_Y+1);}  
      xp1+=8 ; if (xp1>Sprite_width()) xp1-=Sprite_width();//random(Canvas_height()/2,Canvas_height()-INVADER_Y+1);}  
      Invaders1_1.xpos = xp;Invaders2_1.xpos=xp1+40;Invaders3_1.xpos=xp+80;Invaders4_1.xpos=xp1+100;
      yp1+= random(0,3); if (yp1 > Sprite_height())  yp1 -=Sprite_height();
      yp2+= random(1,8); if (yp2 > Sprite_height()) yp2 -=Sprite_height();
      yp3+= random(2,7); if (yp3 > Sprite_height())  yp3 -=Sprite_height();
      yp4+= random(3,5); if (yp4 > Sprite_height())  yp4 -=Sprite_height();
      Invaders1_1.ypos = yp1;Invaders2_1.ypos=yp2;Invaders3_1.ypos=yp3;Invaders4_1.ypos=yp4;

      Sprite_ClearFrame(0x00000000); // fill buffer transparant nothing
        Sprite_DrawImage(Invaders1_1); s=1;       // Draw SpriteImage on Sprite Canvas 8888
        Sprite_DrawImage(Invaders2_1); s=2;      // Draw SpriteImage on Sprite Canvas 1555
        Sprite_DrawImage(Invaders3_1); s=3 ;     // Draw SpriteImage on Sprite Canvas 4444
        Sprite_DrawImage(Invaders4_1); s=4 ;    // Draw SpriteImage on Sprite Canvas 4444
      Printf_Sprite(10,Sprite_height()-25,ORANGE,3,"%i:%i",millis()-tt,millis());            // print text on Sprite Canvas
      tt=millis();
      CanvasAll_DrawFrames(true);                                                // Draw Canvas and Sprite Canvas to DSI
      }
      DEBUGF(" Average Speed #%d %ius\n\r",s, (micros()-tx)/240);
    
  } // forever
} //loop



