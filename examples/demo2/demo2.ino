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
        *( (uint16_t*) RGB565Canvas + t + (i*Canvas_width()) )=(uint16_t) ((i%32)*(64+t%32)/4); // fill screen with pattern
       }
  }
  tt=millis()-tt;
  DEBUGF("*Test 1 : RGB565 Canvas pattern by CPU in %dms, speed KB/s: %d\n\r",tt,(Canvas_width()*Canvas_height()*2)/tt); 
  CanvasAll_DrawFrames(true);delay(2000);

  for(int i = 0 ; i <45; ++i){
shadow4.xpos = random(0, Canvas_width()-shadow4.width);
shadow4.ypos = random(Canvas_height()/2,Canvas_height());
Canvas_DrawImage(shadow4);    // Draw transparant picture : Sprite, formatted as G_image structure to Canvas
  }


  tt=millis();
    room565.xpos = 0; room565.ypos =60; Canvas_DrawImage(room565); // draw opaque image
    room1555.xpos = 0; room1555.ypos =175; Canvas_DrawImage(room1555); // draw opaque image
    room4444.xpos = 0; room4444.ypos =290; Canvas_DrawImage(room4444); // draw opaque image   
    whiteroom.xpos = Sprite_x(); whiteroom.ypos = Sprite_y(); Canvas_DrawImage(whiteroom); // draw opaque image
  tt=millis()-tt;  DEBUGF("*Test 2 : Canvas Imagedraw by DMA  %dms\n\r",tt);
  CanvasAll_DrawFrames(true);delay(1000);


  tt=millis();
  int r=690;
  Printf_Canvas(3,49,BLACK,1,"RGB565 image"); // print text on Canvas buffer
  Printf_Canvas(3,164,BLACK,1,"XRGB155 image"); // print text on Canvas buffer
  Printf_Canvas(3,279,BLACK,1,"X4444 image"); // print text on Canvas buffer

  Printf_Canvas(2,48,ORANGE,1,"RGB565 image"); // print text on Canvas buffer
  Printf_Canvas(2,163,YELLOW,1,"XRGB155 image"); // print text on Canvas buffer
  Printf_Canvas(2,278,CYAN,1,"X4444 image"); // print text on Canvas buffer

  Printf_Canvas(10,10,CYAN,2,"RGB656 Canvas %ix%i - %iKB",Canvas_width(),Canvas_height(),r); // print large text on Canvas buffer 
  Printf_Canvas(Sprite_x()+10,Sprite_y()+10,ORANGE,1,"ARGB8888 Sprite Area %ix%i",Sprite_width(),Sprite_height()); // print text on Canvas buffer
  Canvas_FillRect(700,80,10,300,RED);
  Canvas_FillRect(105,30,5,420,MAGENTA);
  Canvas_FillRect(20,455,650,20,WHITE);
  Printf_Canvas(40,460,RED,1,"Dram starts at = %x",(uint32_t) RGB565Canvas); // print large text on Canvas buffer 
  tt=millis()-tt;  DEBUGF("*Test 3 : Canvas Text and Rect in %dms\n\r",tt);
  CanvasAll_DrawFrames(true);delay(1000);


  tt=millis();
  CanvasAll_DrawFrames(true);
  tt=millis()-tt;  DEBUGF("*Test 4 : Canvas+Sprite Image send to DSI %dms\n\r",tt);
 
  delay(1000);digitalWrite(LEDR, LOW);
}

void loop() {
  // Speed test wit hfull grapics and 3 color types of sprite.
uint32_t tx,tt = millis();
int xp = Canvas_width()/2;
int xp2 = 40;
int yp=100,yp2=200;
int cc,sx,sy,sx2,sy2,boundry,correction;

correction = -(shadow1.width-orb1.width)/2;
boundry=Sprite_height()-orb1.height-15; // boundy of 15 to lowestr part
sx=15;sy=9;
sx2=-10;sy2=-16;
shadow1.ypos= boundry+orb1.height-18;
shadow2.ypos= boundry+orb1.height-20;
shadow3.ypos= boundry+orb1.height-24;
shadow4.ypos= boundry+orb1.height-30;
cc=0;
while(1) {
      tx=micros();
      for(int t=0;t<240;++t){
      xp+=sx + random(-3,3) ; 
        if ( xp>=(Sprite_width()-orb1.width) ) {xp=Sprite_width()-orb1.width-1;sx=-sx;}// bounce 
        else if (  xp<=0 )  {xp=1;sx=-sx;} // bounce 
        orb1.xpos = xp;
      yp+= sy + random(-1,1) ; ;
        if ( yp>=(boundry)  ) {yp=boundry-1;sy=-sy;} // bounce 
        else if (  yp<=0 ) {yp=1;sy=-sy;}// bounce 
        orb1.ypos = yp;
        
      xp2+=sx2 + random(-1,1) ; 
        if ( xp2>=(Sprite_width()-orb1.width) ) {xp2=Sprite_width()-orb1.width-1;sx2=-sx2;}// bounce 
        else if (  xp2<=0 )  {xp2=1;sx2=-sx2;} // bounce 
        orb2.xpos = xp2;
      yp2+= sy2 + random(-3,3) ; ;
        if ( yp2>=(boundry)  ) {yp2=boundry-1;sy2=-sy2;} // bounce 
        else if (  yp2<=0 ) {yp2=1;sy2=-sy2;}// bounce 
        orb2.ypos = yp2;

      //collision detect
      if(  ( (xp-xp2)*(xp-xp2)+(yp-yp2)*(yp-yp2) ) < (orb1.width*orb2.width) ) { 
        int sxT = sx; 
        int syT = sy ;
        sx = sx2; sy= sy2;
        sx2 = sxT; sy2= syT;
        cc++;
      } 

      Sprite_ClearFrame(0x00000000); // fill buffer transparant nothing
      
      if(yp >= (boundry-160) && yp< (boundry-40) )  { shadow4.xpos = xp+correction;Sprite_DrawImage(shadow4);   }      
      if(yp >= (boundry-40) && yp< (boundry-20) )  { shadow3.xpos = xp+correction;Sprite_DrawImage(shadow3);   }
      if(yp >= (boundry-20) && yp< (boundry-5) )  { shadow2.xpos = xp+correction;Sprite_DrawImage(shadow2);   }
      if(yp >= (boundry-5) ) { shadow1.xpos = xp+correction;Sprite_DrawImage(shadow1);   }
      Sprite_DrawImage(orb1);       // Draw SpriteImage on Sprite Canvas 8888

      if(yp2 >= (boundry-160) && yp< (boundry-40) )  { shadow4.xpos = xp2+correction;Sprite_DrawImage(shadow4);   }      
      if(yp2 >= (boundry-40) && yp< (boundry-20) )  { shadow3.xpos = xp2+correction;Sprite_DrawImage(shadow3);   }
      if(yp2 >= (boundry-20) && yp< (boundry-5) )  { shadow2.xpos = xp2+correction;Sprite_DrawImage(shadow2);   }
      if(yp2 >= (boundry-5) ) { shadow1.xpos = xp+correction;Sprite_DrawImage(shadow1);   }
      Sprite_DrawImage(orb2);       // Draw SpriteImage on Sprite Canvas 8888      

      Printf_Sprite(10,Sprite_height()-25,RED,3,"%i:%i:%i",millis()-tt,cc,millis());            // print text on Sprite Canvas
      tt=millis();
      CanvasAll_DrawFrames(true);                                                // Draw Canvas and Sprite Canvas to DSI
      }
      DEBUGF(" Average Speed %ius\n\r", (micros()-tx)/240);
    
  } // forever
} //loop



