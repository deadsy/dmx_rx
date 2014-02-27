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

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
 #define LCD_RESET   PN(1,0)   /* D8, PB0 */
 #define LCD_A0      PN(1,1)   /* D9, PB1 */
 #define LCD_CS      PN(1,2)   /* D10, PB2 */
 #define LCD_MOSI    PN(1,3)   /* D11, PB3 */
 #define LCD_SCK     PN(1,5)   /* D13, PB5 */
#elif defined(__AVR_ATmega32U4__)
 #define LCD_RESET   PN(1,4)   /* D8, PB4 */
 #define LCD_A0      PN(1,5)   /* D9, PB5 */
 #define LCD_CS      PN(1,6)   /* D10, PB6 */
 #define LCD_MOSI    PN(1,7)   /* D11, PB7 */
 #define LCD_SCK     PN(2,7)   /* D13, PC7 */
#else
  #error "define the target processor"
#endif

u8g_t u8g;

void u8g_setup(void)
{
    u8g_InitSPI(&u8g, &u8g_dev_st7565_nhd_c12864_sw_spi, LCD_SCK, LCD_MOSI, LCD_CS, LCD_A0, LCD_RESET);
}

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
