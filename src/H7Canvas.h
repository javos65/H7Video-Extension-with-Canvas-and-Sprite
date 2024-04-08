#ifndef USBC_CANVAS
#define USBC_CANVAS

#include <stdint.h>
#include "fonts_A4.h"


typedef struct {
void *imagearray;  // array pointer
uint16_t width;    // width image
uint16_t height;   // heigt image
uint32_t colormode;// colormode DMA2D
uint8_t bpp;       // bits per pixel
uint16_t xpos;     // x position
uint16_t ypos;     // y position
char name[24];     // name in text
} G_image;         // end structure

#define GENERIC_RESX 720  // VIDEO SCREEN SIZE = CANVAS SIZE
#define GENERIC_RESY 480

#define SPRITE_RESX 480   // SPRITE AREA - Game size
#define SPRITE_RESY 320

#define SPRITE_SX 120     // Start Sprite area on Canvas upper left corner
#define SPRITE_SY 80

// 565 colors
#define CLEAR     0x0005
#define BLACK     0x0000
#define BLUE      0x001F
#define RED       0xF800
#define GREEN     0x07E0
#define LIME	    0xe7e0
#define CYAN      0x07FF
#define DARK_CYAN 0x0DCB
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define WHITE     0xFFFF
#define ORANGE    0xfd20

extern uint32_t* ARGB8888Canvas;
extern uint16_t* RGB565Canvas;

extern char TBUF[80];
#define Printf_Canvas(x,y,c,s,__info,...) sprintf(TBUF,__info,##__VA_ARGS__);CanvasAll_Text(TBUF, x, y,c,s,true); // Canvas Text
#define Printf_Sprite(x,y,c,s,__info,...) sprintf(TBUF,__info,##__VA_ARGS__);CanvasAll_Text(TBUF, x, y,c,s,false); // Sprite Text
#define Sprite_width()  SPRITE_RESX
#define Sprite_height() SPRITE_RESY
#define Sprite_x()      SPRITE_SX
#define Sprite_y()      SPRITE_SY
#define Canvas_width()  GENERIC_RESX
#define Canvas_height() GENERIC_RESY


void CanvasAll_Init();
void CanvasAll_DrawFrames(bool update);
void CanvasAll_CurrentFrame();
void CanvasAll_FillBuffer(void *pDst, uint32_t xSize, uint32_t ySize, uint32_t ColorIndex,uint32_t ColorMode);
void CanvasAll_Text(const char * txt, uint16_t x, uint16_t y,uint16_t color,uint8_t size,bool type);
void CanvasAll_Drawtext(bool canvas, const char *text, font4bpp myfont, uint16_t x, uint16_t y,uint16_t color565);

void Canvas_ClearFrame(uint16_t rgb565color);
void Canvas_DrawImage(G_image spriteimage);
void Canvas_DrawImage565(void *image,uint16_t x, uint16_t y, uint16_t xw, uint16_t  yw); // non Alpha
void Canvas_DrawImageAlpha(void *pSrc, uint16_t x, uint16_t y,uint32_t xSize, uint32_t ySize,uint32_t colormode);
void Canvas_DrawFont(void *pSrc, uint16_t x, uint16_t y,uint32_t xSize, uint32_t ySize, uint32_t fontmode, uint16_t color565);
void Canvas_FillRect(uint16_t x, uint16_t y,uint16_t xw, uint16_t yw,uint16_t color);

void Sprite_DrawFrame();
void Sprite_ClearFrame(uint32_t ARGB888color);
void Sprite_DrawImage( G_image spriteimage);
void Sprite_DrawImage565( void* sprite, uint16_t x, uint16_t y,uint32_t xSize, uint32_t ySize); // non alpha
void Sprite_DrawImageAlpha( void* sprite, uint16_t x, uint16_t y,uint32_t xSize, uint32_t ySize,uint32_t colormode);
void Sprite_DrawFont(void *pSrc, uint16_t x, uint16_t y,uint32_t xSize, uint32_t ySize, uint32_t fontmode, uint16_t color565);
void Sprite_FillRect(uint16_t x, uint16_t y,uint16_t xw, uint16_t yw,uint16_t color);
void Sprite_Erase(uint16_t x, uint16_t y,uint16_t xw, uint16_t yw);

 


#endif //USBC_CANVAS