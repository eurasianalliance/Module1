
/*
 * draw_tank.c
 *
 *  Created on: 2014-01-06
 *      Author: Kris_Mazurek, Tommy Cheang, Joanna Leung, Ellina Sergeyeva
 */


#include "tanks.h"

/*
 *
 *
 * The following function draws a beautiful tank. FEAR ME, PUNY MORTALS!
 *
 */
void draw_tank1(alt_up_pixel_buffer_dma_dev* pixbuf, int x_pos, int y_pos)
{
	alt_up_pixel_buffer_dma_dev* pixel_buffer = pixbuf;
	int x = x_pos;
	int y = y_pos;

	//alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, 	y, 		x+8, 	y,	0xF800, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+5, 	y+1, 		x+9, 	y+1,	0xF800, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+3, 	y+2,		x+9, 	y+2,	0xF800, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2,	y+3, 		x+10, 	y+3,	0xF800, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, 	y+4,		x+11, 	y+4,	0x000000, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+5,		x+12, 	y+5,	0x000000, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+6,		x+12, 	y+6,	0x000000, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, 	y+7,		x+11,	y+7,	0x000000, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2,	y+8,		x+10,	y+8,	0x000000, 1);
	//alt_up_pixel_buffer_dma_draw(pixel_buffer, x, y, 0xDDDD);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x+2, t->y,		t->x, t->y,	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y, 		t->x, t->y, 	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y,   		t->x, t->y,	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y,		t->x, t->y, 	0xFF00, 1);

	//Swap buffers and clear
	   //   alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	   //   while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
}


/*
 * Overview: Draws a tank given its current coordinates.
 *
 */
void draw_tank2(alt_up_pixel_buffer_dma_dev* pixbuf, int x_pos, int y_pos)
{
	alt_up_pixel_buffer_dma_dev* pixel_buffer = pixbuf;
	int x = x_pos;
	int y = y_pos;

	//alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+4, 	y, 		x+6, 	y,	0xFF00 , 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+3, 	y+1, 		x+7, 	y+1,	0xFF00 , 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+3, 	y+2,		x+9, 	y+2,	0xFF00 , 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, 	y+3, 		x+10, 	y+3,	0xFF00 , 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, 	y+4,		x+11, 	y+4,	0x000000, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+5,		x+12, 	y+5,	0x000000, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+6,		x+12, 	y+6,	0x000000, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, 	y+7,		x+11,	y+7,	0x000000, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, 	y+8,		x+10,	y+8,	0x000000, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x+2, t->y,		t->x, t->y, 	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x+2, t->y,		t->x, t->y,	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y, 		t->x, t->y, 	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y,   		t->x, t->y,	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y,		t->x, t->y, 	0xFF00, 1);

	//Swap buffers and clear
	//      alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	 //     while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
}

/*
 * Overview: Draws a tank on the start screen.
 *
 */
void draw_tank1_start(alt_up_pixel_buffer_dma_dev* pixbuf, int x_pos, int y_pos)
{
	alt_up_pixel_buffer_dma_dev* pixel_buffer = pixbuf;
	int x = x_pos;
	int y = y_pos;

	//alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+21, 	y, 		x+29, 	y,	0xF800 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+19, 	y+1, 		x+30, 	y+1,	0xF800 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+18, 	y+2, 		x+30, 	y+2,	0xF800 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+16, 	y+3, 		x+31, 	y+3,	0xF800 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+14, 	y+4,		x+32, 	y+4,	0xF800 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+12, 	y+5, 		x+32, 	y+5,	0xF800 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+10, 	y+6, 		x+33, 	y+6,	0xF800 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+8, 	y+7, 		x+34, 	y+7,	0xF800 , 0);
	/*
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+10, 	y, 		x+18, 	y,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+9, 	y+1, 		x+20, 	y+1,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+9, 	y+2, 		x+21, 	y+2,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+8, 	y+3, 		x+23, 	y+3,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+7, 	y+4,		x+25, 	y+4,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+7, 	y+5, 		x+27, 	y+5,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, 	y+6, 		x+29, 	y+6,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+5, 	y+7, 		x+31, 	y+7,	0xFF00 , 0);
	*/
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+4, 	y+8,		x+35, 	y+8,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, 	y+9,		x+37, 	y+9,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+10,		x+40, 	y+10,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+11,		x+40, 	y+11,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+12,		x+40, 	y+12,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+13,		x+40, 	y+13,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, 	y+14,		x+38, 	y+14,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+4, 	y+15,		x+36,	y+15,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, 	y+16,		x+34,	y+16,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+8, 	y+17,		x+32,	y+17,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+10, 	y+18,		x+30,	y+18,	0x000000, 0);
	//Swap buffers and clear
	   //   alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	   //   while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+29, 	y+1,		x+49,	y-8,	0xF800, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+29, 	y+2,		x+49,	y-7,	0xF800, 0);
}


/*
 * Overview: Draws another tank on the start screen.
 *
 */
void draw_tank2_start(alt_up_pixel_buffer_dma_dev* pixbuf, int x_pos, int y_pos)
{
	alt_up_pixel_buffer_dma_dev* pixel_buffer = pixbuf;
	int x = x_pos;
	int y = y_pos;

	//alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+10, 	y, 		x+18, 	y,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+9, 	y+1, 		x+20, 	y+1,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+9, 	y+2, 		x+21, 	y+2,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+8, 	y+3, 		x+23, 	y+3,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+7, 	y+4,		x+25, 	y+4,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+7, 	y+5, 		x+27, 	y+5,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, 	y+6, 		x+29, 	y+6,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+5, 	y+7, 		x+31, 	y+7,	0xFF00 , 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+4, 	y+8,		x+35, 	y+8,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, 	y+9,		x+37, 	y+9,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+10,		x+40, 	y+10,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+11,		x+40, 	y+11,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+12,		x+40, 	y+12,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, 	y+13,		x+40, 	y+13,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, 	y+14,		x+38, 	y+14,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+4, 	y+15,		x+36,	y+15,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, 	y+16,		x+34,	y+16,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+8, 	y+17,		x+32,	y+17,	0x000000, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+10, 	y+18,		x+30,	y+18,	0x000000, 0);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x+2, t->y,		t->x, t->y, 	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x+2, t->y,		t->x, t->y,	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y, 		t->x, t->y, 	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y,   		t->x, t->y,	0xFF00, 1);
//	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t->x, t->y,		t->x, t->y, 	0xFF00, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+10, 	y+1,		x-10,	y-8,	0xFF00, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+10, 	y+2,		x-10,	y-7,	0xFF00, 0);

	//Swap buffers and clear
	//      alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	 //     while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
}

