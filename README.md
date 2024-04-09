# Portenta H7 Video extenstion with Canvas and Sprites
![logo](/images/orb2.png?raw=true)
## Extension of the Arduino_H7_Video.h library
____

## About

H7 Video for Portenta has a smart Video output, including USB-C / HDMI. The exsisting libabry is setup as a dual buffer in RGB565 format , switching context to the video controller, and has no easy features for dynamicly use screens with moving , replacing or tansparant images.
This library adds a background Canvas, with on top a transparant Sprite Area in alpha-format.

This code was made by using Portenta H7 (and HAT expansion board) supporting HDMI over USB-C
All video functions using a special 2D DMA function (DMA2D) to transfer. The video buffers require part of the SDRAM use of the Portenta H7.
Images can be build using the C-Array conversion program for H7.
(https://github.com/javos65/H7-CArray-Converter-for-USBDisk)

![logo](/images/orb1.png?raw=true)

### Functions added

*CanvasAll_Init()* : initialises video with Canvas and Sprite Area. currently not dybnamic, but adaptable in the .h setup<br>
*CanvasAll_DrawFrames()* : draws all frames - Canvas + transparant Sprite to the current DSI video buffer, and sends buffer for display

*Canvas_DrawImage(G_image imagename)* : draw G_image to Canvas-buffer<br>
*Sprite_DrawImage(G_image imagename)* : draw G_image to Sprite-buffer

**G_image** is an image C-structure object that contains the image data like pixel-type, size and the pointer to the image data.
This simplifies the image-draww calls in your program, it supporta alpha images (like PNG) in ARGB8888 ARGB1555 ARGB4444.
G_image object also contains the x-y coordinates on the screen.

*Printf_Canvas()* and *Printf_Sprite()* : printf-function for graphic text in alpha / transparant style.
Graphic text comes is 3 flavours are the moment : 1 standard 12pt , 2 large 18pt, 3 fat 24pt (number only)



### Wiring

Connect H7 to HAT expansion board , load the program, and fiddle around.
*  Portenta Carrier :     Portenta Hat Carrier  SKU ASX00049 Barcode 7630049204041
*  Portenta board :       Portenta H7           SKU ABX00042 Barcode 7630049202252 

___

### Features:
+ Drive fixed background
+ Add transparant image blending to background
+ Add a Sprite area - transparant overlay
+ Add transparant image blending to Sprite Area
+ Support 16 bit RGB565 ARGB1555 ARGB4444  / 32 bit ARGB8888
+ Add transparant A4-pixel font usage as a printf-function


___

## To do:
+ Make the Canvas a Callable Class
+ Add transparant drawing features

___

### And please, don't ask about the 0xB19B00B5

