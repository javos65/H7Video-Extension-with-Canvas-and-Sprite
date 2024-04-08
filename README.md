## Portenta H7 Video extenstion with Canvas and Sprites
![logo](/images/orb2.png?raw=true)
## Extension of the H7_Video_Library of Arduino
____

## About

H7 Video for Portenta has a smart Video output, including USB-C / HDMI
The exsisting libabry is setup as a dual buffer in RGB565 format , swithcing context to the video controller, and has no easy features for dynamicly use screens with moving or replacing images.
This library adds a background Canvas, with on top a transparant Sprite Area in ARGB8888 format.

This code was made by using Portenta H7 (and HAT expansion board) supporting HDMI over USB-C
All using a special 2D DMA function (DMA2D) to transfer. The video buffers require a 1.5MB SDRAM use of the Portenta H7.
Images can be build using the C-Array conversion program for H7.

(https://github.com/javos65/H7-CArray-Converter-for-USBDisk)


![logo](/images/orb2.png.png?raw=true)

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

