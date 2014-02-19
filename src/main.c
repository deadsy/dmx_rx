//-----------------------------------------------------------------------------
/*

DMX Rx

Receive DMX channel information and use it to control lights.

*/
//-----------------------------------------------------------------------------

#include "u8g.h"
#include <avr/interrupt.h>
#include <avr/io.h>

//-----------------------------------------------------------------------------

u8g_t u8g;

void u8g_setup(void)
{
    //U8GLIB_NHD_C12864 u8g(13, 11, 10, 9, 8);    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, RST = 8
    u8g_InitHWSPI(&u8g, &u8g_dev_st7565_nhd_c12864_hw_spi, PN(1, 5), PN(1, 3), U8G_PIN_NONE);
}

uint8_t u8g_InitSPI(u8g_t *u8g, u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset);

void sys_init(void)
{
    // select minimal prescaler (max system speed)
    CLKPR = 0x80;
    CLKPR = 0x00;
}

void draw(void)
{
    u8g_SetFont(&u8g, u8g_font_6x10);
    u8g_DrawStr(&u8g, 0, 15, "Hello World!");
}

int main(void)
{
    sys_init();
    u8g_setup();

    while(1) {
        u8g_FirstPage(&u8g);
        do {
            draw();
        } while (u8g_NextPage(&u8g));
        u8g_Delay(100);
    }

    // loop forever...
    while(1);
    return 0;
}

//-----------------------------------------------------------------------------
