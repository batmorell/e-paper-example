/* Includes ------------------------------------------------------------------*/
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>

/* Entry point ----------------------------------------------------------------*/
void setup()
{
	printf("EPD_2IN9_V2_test Demo\r\n");
	DEV_Module_Init();

  printf("e-Paper Init and Clear...\r\n");
  EPD_2IN9_V2_Gray4_Init();  // Initialize in grayscale mode
  EPD_2IN9_V2_Clear();
  DEV_Delay_ms(500);

  UWORD Imagesize = ((EPD_2IN9_V2_WIDTH % 4 == 0)? (EPD_2IN9_V2_WIDTH / 4 ): (EPD_2IN9_V2_WIDTH / 4 + 1)) * EPD_2IN9_V2_HEIGHT;
  UBYTE *BlackImage = (UBYTE *)malloc(Imagesize);
  if(BlackImage == NULL) {
      printf("Failed to apply for black memory...\r\n");
      return;
  }

  Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 270, WHITE);
  Paint_SetScale(4);  // Set scale for grayscale
  Paint_Clear(WHITE);
  Paint_SelectImage(BlackImage);

  UBYTE num = 20;
  for (;;) {
    // Draw a rectangle in grayscale
    if(num % 2 == 0) {
      Paint_DrawRectangle(20, 20, 100, 100, GRAY3, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    } else {
      Paint_DrawRectangle(20, 20, 100, 100, GRAY1, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    }

    // Display the image
    EPD_2IN9_V2_Display_Partial(BlackImage);
    DEV_Delay_ms(2000);
    int num = num - 1;
    if(num == 0) {
        break;
    }
  }

  printf("Clear...\r\n");
  EPD_2IN9_V2_Init();
  EPD_2IN9_V2_Clear();

  printf("Goto Sleep...\r\n");
  EPD_2IN9_V2_Sleep();
  free(BlackImage);
  BlackImage = NULL;
}

/* The main loop -------------------------------------------------------------*/
void loop()
{
  //
}

