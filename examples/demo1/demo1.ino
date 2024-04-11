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


// Demo for 800x600 Video

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

tt=millis();
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
  tt=millis()-tt;
  DEBUGF("*Test 2 : RGB565 Canvas Alpha images drawing by DMA in %dms, speed images/s: %d\n\r",tt,75*1000/tt); 

  tt=millis();
  CanvasAll_DrawFrames(true);
  tt=millis()-tt;  DEBUGF("*Test 3 : Canvas+Sprite Image send to DSI %dms\n\r",tt);
 
   tt=millis();
   Splash.xpos = Sprite_x();  Splash.ypos = Sprite_y();
  Canvas_DrawImageR(Splash,Sprite_width(),Sprite_height()); // draw opaque image resized under Sprite Area
  tt=millis()-tt;  DEBUGF("*Test 4 : Canvas Imagedraw REsized by CPU + DMA  %dms\n\r",tt);
  CanvasAll_DrawFrames(true);delay(1000);

  tt=millis();
  Printf_Canvas(10,10,YELLOW,2,"RGB656 Canvas %ix%i - %iKB",Canvas_width(),Canvas_height(),Canvas_width()*Canvas_height()*2/1024); // print large text on Canvas buffer 
  Printf_Canvas(Sprite_x()+10,Sprite_y()+10,WHITE,1,"ARGB8888 Sprite Area %ix%i",Sprite_width(),Sprite_height()); // print text on Canvas buffer
  Canvas_FillRect(700,50,20,500,RED,0x80);
  Canvas_FillRect(20,130,10,450,MAGENTA,0xA0);
  Canvas_FillRect(40,130,10,450,MAGENTA,0x80);
  Canvas_FillRect(60,130,10,450,MAGENTA,0x60);
  Canvas_FillRect(80,130,10,450,MAGENTA,0x40);
  Canvas_FillRect(100,130,10,450,MAGENTA,0x20);
  Canvas_FillRect(20,555,750,20,WHITE,0xA0);
  Printf_Canvas(40,560,RED,1,"Canvas Video ram starts at = %x",(uint32_t) RGB565Canvas); // print large text on Canvas buffer 
  tt=millis()-tt;  DEBUGF("*Test 5 : Canvas Alpha Text and Rect in %dms\n\r",tt);
  CanvasAll_DrawFrames(true);delay(1000);

  delay(1000);digitalWrite(LEDR, LOW);
}

void loop() {
  // Speed test wit hfull grapics and 3 color types of sprite.
uint32_t t,tx,tt = millis();
uint16_t s,xp ,xp1;
uint16_t yp1,yp2,yp3,yp4 = Sprite_height()/2;
yp1=yp4;yp2=yp4;yp3=yp4;

while(1) {
      xp+=12 ; if (xp>(Sprite_width()-Invaders1_1.width)) xp-=Sprite_width();//random(Canvas_height()/2,Canvas_height()-INVADER_Y+1);}  
      xp1+=8 ; if (xp1>(Sprite_width()-Invaders1_1.width)) xp1-=Sprite_width();//random(Canvas_height()/2,Canvas_height()-INVADER_Y+1);}  
      yp1+= random(0,3); if (yp1 > (Sprite_height()-Invaders1_1.height))  yp1 -=Sprite_height();
      yp2+= random(1,8); if (yp2 > (Sprite_height()-Invaders2_1.height))  yp2 -=Sprite_height();
      yp3+= random(2,7); if (yp3 > (Sprite_height()-Invaders3_1.height))  yp3 -=Sprite_height();
      yp4+= random(3,5); if (yp4 > (Sprite_height()-Invaders4_1.height))  yp4 -=Sprite_height();

      Sprite_ClearFrame(0x00000000); // fill buffer transparant nothing
      for( t=0;t<10;++t) { Invaders1_1.xpos=random(32,38)+t*(Invaders1_1.width+16);Invaders1_1.ypos =10;Sprite_DrawImage(Invaders1_1); }
      for( t=0;t<10;++t) { Invaders2_1.xpos=random(17,27)+t*(Invaders2_1.width+14);Invaders2_1.ypos =40;Sprite_DrawImage(Invaders2_1); }
      for( t=0;t<10;++t) { Invaders3_1.xpos=random(29,34)+t*(Invaders3_1.width+15);Invaders3_1.ypos =70;Sprite_DrawImage(Invaders3_1); }

      Invaders1_1.xpos = xp;Invaders2_1.xpos=xp1+40;Invaders3_1.xpos=xp+80;Invaders4_1.xpos=xp1+100;
      Invaders1_1.ypos = yp1;Invaders2_1.ypos=yp2;Invaders3_1.ypos=yp3;Invaders4_1.ypos=yp4;

        Sprite_DrawImage(Invaders1_1); s=1;       // Draw SpriteImage on Sprite Canvas 8888
        Sprite_DrawImage(Invaders2_1); s=2;      // Draw SpriteImage on Sprite Canvas 1555
        Sprite_DrawImage(Invaders3_1); s=3 ;     // Draw SpriteImage on Sprite Canvas 4444
        Sprite_DrawImage(Invaders4_1); s=4 ;    // Draw SpriteImage on Sprite Canvas 4444
        Printf_Sprite(10,Sprite_height()-25,ORANGE,3,"%i:%i",millis()-tt,millis());            // print text on Sprite Canvas
        Printf_Sprite(10,random(Sprite_height()/3,Sprite_height()/2),GREEN,2,"FRame Rate : %i fps",1000/(millis()-tt));     
      tt=millis();
      CanvasAll_DrawFrames(true);                                                // Draw Canvas and Sprite Canvas to DSI

    
  } // forever
} //loop



