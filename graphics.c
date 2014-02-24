/*
 * graphics.c
 *
 *  Created on: 2014-01-30
 *      Author: Kris_Mazurek, Tommy Cheang, Ellina Sergeyeva, Joanna Leung
 */

#include "tanks.h"


/*
 * Overview: 	Draws the main game screen.
 *		Displays the two tanks, their cannons and bullets,
 *		the current terrain, as well as in-game information
 *		such as current score, wind, weapon type, power.
 */
void draw_map(struct ground* g,struct tank* t_1, struct tank* t_2, struct bullet* b_1, struct bullet* b_2,alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y,struct terrain* trn, int WIND)
{
	struct ground* ground=(struct ground *) g;
	struct tank* tank_1=(struct tank *) t_1;
	struct tank* tank_2=(struct tank *) t_2;
	struct bullet* bul_1=(struct bullet *) b_1;
	struct bullet* bul_2=(struct bullet *) b_2;
	struct terrain* ter=(struct terrain *) trn;
	alt_up_pixel_buffer_dma_dev* pixel_buffer = x;
	alt_up_char_buffer_dev * char_buffer = y;
	char score_t_1[CHAR_BUF_LENGTH]; // score value buffers
	char score_t_2[CHAR_BUF_LENGTH];
	char weapon_t_1 [CHAR_BUF_LENGTH]; // weapon value buffers
	char weapon_t_2 [CHAR_BUF_LENGTH];
	char power_t_1_3 [CHAR_BUF_LENGTH];//buffer for 3 digit
	char power_t_2_3 [CHAR_BUF_LENGTH];//buffer for 3 digit
	char wind [CHAR_BUF_LENGTH];//buffer for 3 digit

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 320, 240, 0xAFF, 1); // sky

	/* Draw the current terrain */
	if( ter->type == 0) // regular ground
	{ 	
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, ter->x, ter->y, 320, 240, 0x336600, 1); //ground

	}
	else if( ter->type == 1 // water
	{ 	
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, ter->x, ter->y, ter->x+100, 240, 0x336600, 1); //ground
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, ter->x+101, ter->y+10, 200, 240, 0x7FF, 1); //water
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, ter->x+201, ter->y, 320, 240, 0x336600, 1); //ground
	}
	else if( ter->type == 2 // A tree
	{ 	
		// Draw a tree
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, (*ground).y_int, 320, 240, 0x336600, 1); //ground
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 135, 123, 175, 170, 0x7E0, 1); //crown
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 151, 160, 158, 175, 0x79E0, 1); //trunk
		// Draw shade
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 136,  177,  176,  177,  0x7E0, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 139+5,  179,  175,  179,  0x7E0, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 142+5,  181,  171+6,  181,  0x7E0, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 146+8,  184,  166+13,  184,  0x7E0, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150+10,  187,  161+17,  187,  0x7E0, 1);
	}


	/* Draw Tank 1*/
	draw_tank1(pixel_buffer,(*tank_1).x, (*tank_1).y);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, tank_1->nozz_x, tank_1->nozz_y, tank_1->x+7, tank_1->y, 0xF800, 1);//draw nozzle 1

	/* Draw Tank 2*/
	draw_tank2(pixel_buffer,(*tank_2).x, (*tank_2).y);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, tank_2->nozz_x, tank_2->nozz_y, tank_2->x+5, tank_1->y, 0xFF00 , 1);//draw nozzle 2

	alt_up_pixel_buffer_dma_draw(pixel_buffer,  0xF800,(*bul_1).x, (*bul_1).y);//draw bullet 1
	alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xFF00 ,(*bul_2).x, (*bul_2).y);//draw bullet 2

	/* Display scores */
	alt_up_char_buffer_string(char_buffer, "Score:", 1, 1);
	sprintf( score_t_1, "%d", tank_1->score); // convert to string
	sprintf( score_t_2, "%d", tank_2->score);
	alt_up_char_buffer_string(char_buffer, score_t_1, 9, 1); //print tank 1 score
	alt_up_char_buffer_string(char_buffer, score_t_2, 11, 1); //print tank 2 score

	/* Display weapon types */
	alt_up_char_buffer_string(char_buffer, "Tank 1 Weapon: ", 1, 15);
	alt_up_char_buffer_string(char_buffer, "Tank 2 Weapon: ", 61, 15);
	sprintf( weapon_t_1, "%d", tank_1->weapon); // convert to string
	sprintf( weapon_t_2, "%d", tank_2->weapon);
	alt_up_char_buffer_string(char_buffer, weapon_t_1, 16, 15); //print tank 1 weapon
	alt_up_char_buffer_string(char_buffer, weapon_t_2, 76, 15); //print tank 2 weapon

	/* Display power level */
	alt_up_char_buffer_string(char_buffer, "Tank 1 Power: ", 1, 17);
	alt_up_char_buffer_string(char_buffer, "Tank 2 Power: ", 61, 17);
	sprintf( power_t_1_3, "%d", tank_1->power); // convert to string
	sprintf( power_t_2_3, "%d", tank_2->power);
	alt_up_char_buffer_string(char_buffer, power_t_1_3, 16, 17); //print tank 1 power
	alt_up_char_buffer_string(char_buffer, power_t_2_3, 76, 17); //print tank 2 power

	/* Display the current wind level */
	sprintf(wind, "%d", WIND);
	alt_up_char_buffer_string(char_buffer, "Wind: ", 70, 1);
	alt_up_char_buffer_string(char_buffer, wind, 76, 1); //print WIND

	/* Swap pixel buffers */
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));

}


/*
 * Overview: Draws the start menu of the game.
 *
 */
void start_screen(alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y)
{

	alt_up_pixel_buffer_dma_dev* pixel_buffer = x;
	alt_up_char_buffer_dev * char_buffer = y;

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0); // clear the screen

	//Tank Start Page
	//Sky
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 320, 240, 0xAFF, 0);

	//ground
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 148, 320, 240, 0x336600, 0);

	/* Draw the two tanks */
	draw_tank1_start(pixel_buffer, 30, 129);
	draw_tank2_start(pixel_buffer, 250, 129);

	//TANK BLOCK TEXT
	//T
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 40, 20, 90, 30, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 60, 30, 70, 70, 0xFBE0, 0);
	//A
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 100, 20, 130, 30, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 100, 30, 110, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 120, 30, 130, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 110, 40, 120, 50, 0xFBE0, 0);
	//N
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 140, 20, 150, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 180, 20, 190, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 20, 180, 60, 0xFBE0, 0); //top
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 21, 180, 61, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 22, 180, 62, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 23, 180, 63, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 24, 180, 64, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 25, 180, 65, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 26, 180, 66, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 27, 180, 67, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 28, 180, 68, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 29, 180, 69, 0xFBE0, 0); //middle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 30, 180, 70, 0xFBE0, 0); //bottom
	//thickening the N
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 20, 180, 59, 0xFBE0, 0); //top
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 20, 180, 58, 0xFBE0, 0); //top
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 20, 180, 57, 0xFBE0, 0); //top

	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 31, 180, 70, 0xFBE0, 0); //top
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 32, 180, 70, 0xFBE0, 0); //top
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 150, 33, 180, 70, 0xFBE0, 0); //top

	//K
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 200, 20, 210, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 20, 210, 40, 0xFBE0, 0);//top top
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 21, 210, 41, 0xFBE0, 0); //middles layers
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 22, 210, 42, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 23, 210, 43, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 24, 210, 44, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 25, 210, 45, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 26, 210, 46, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 27, 210, 47, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 28, 210, 48, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 240, 29, 210, 49, 0xFBE0, 0);

	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 40, 240, 70, 0xFBE0, 0);//bottom top
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 50, 230, 70, 0xFBE0, 0);//bottom bottom
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 41, 239, 70, 0xFBE0, 0);//middle layers
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 42, 238, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 43, 237, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 44, 236, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 45, 235, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 46, 234, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 47, 233, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 48, 232, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 210, 49, 231, 70, 0xFBE0, 0);

	//S
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 250, 20, 280, 30, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 250, 30, 260, 50, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 260, 40, 280, 50, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 270, 50, 280, 70, 0xFBE0, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 250, 60, 270, 70, 0xFBE0, 0);
	// text for start
	alt_up_char_buffer_string(char_buffer, "Press Enter to Start", 30, 45);
	alt_up_char_buffer_string(char_buffer, "Press T to see the tutorial", 29, 52);
	//start sign box
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 115, 173, 207, 190, 0x79E0, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 172, 208, 191, 0xBDF7, 0);
	//second sign box
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 105, 200, 225, 219, 0x79E0, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 104, 199, 226, 220, 0xBDF7, 0);

	return ;
}


/*
 * Overview: Draws the tutorial screen.
 *
 */
void tutorial_screen(alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y){

	alt_up_pixel_buffer_dma_dev* pixel_buffer = x;
	alt_up_char_buffer_dev * char_buffer = y;

	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_char_buffer_clear(char_buffer);

	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 320, 240, 0xFBE0, 0); // background colour
	alt_up_char_buffer_string(char_buffer, "Tutorial", 36, 10);
	alt_up_char_buffer_string(char_buffer, "Use left and right arrows to move the tank", 22, 15);
	alt_up_char_buffer_string(char_buffer, "Press 1 and 2 to switch between Normal Shot and Bounce Shot", 13, 20);
	alt_up_char_buffer_string(char_buffer, "Use up and down arrows to aim and W and S to adjust power", 12, 25);
	alt_up_char_buffer_string(char_buffer, "Press SPACE to fire", 30, 30);
	alt_up_char_buffer_string(char_buffer, "Press P to pause the Game", 30, 35);
	alt_up_char_buffer_string(char_buffer, "Press ENTER to continue to the game...", 24, 38);
	alt_up_char_buffer_string(char_buffer, "Have fun!", 34, 42);
	// Draw a box behind the instructions
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 30, 30, 300, 200, 0xAFF, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 29, 29, 301, 201, 0xBDF7, 0);

	usleep(1000000); // add some delai to read the information
	return;
}


/*
 * Overview: Draws the high score screen as seen during the game.
 *
 */
void high_score_screen(alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y, alt_up_sd_card_dev * sd, alt_up_ps2_dev *keyb, struct high_score * highscore){

	alt_up_pixel_buffer_dma_dev* pixel_buffer = x;
	alt_up_char_buffer_dev * char_buffer = y;
	alt_up_ps2_dev *keyboard = keyb;
	struct high_score* scores = (struct high_score *) highscore;
	char score_p1[CHAR_BUF_LENGTH]; // score buffers
	char score_p2[CHAR_BUF_LENGTH];
	alt_u8 key = 0;
	char asci_char;
	KB_CODE_TYPE code_type;

	//printf("Player 1 score is %c\n", scores->highscore_p1);
	//printf("Player 2 score is %c\n", scores->highscore_p2);
	sprintf( score_p1, "%c", scores->highscore_p1); // convert to string
	sprintf( score_p2, "%c", scores->highscore_p2);

	// Clear
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_char_buffer_clear(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 320, 240, 0x0000, 0); // background colour

	alt_up_char_buffer_string(char_buffer, "High Score", 35, 12);
	alt_up_char_buffer_string(char_buffer, "Player 1:", 34, 18);
	alt_up_char_buffer_string(char_buffer, "Player 2:", 34, 22);
	alt_up_char_buffer_string(char_buffer, "Press ENTER to continue to the game...", 21, 40);

	alt_up_char_buffer_string(char_buffer, score_p1, 45, 18); //display player 1 score
	alt_up_char_buffer_string(char_buffer, score_p2, 45, 22); //display player 2 score

	// Wait for the user to press ENTER to continue the game
	while (1) {

		if( decode_scancode(keyboard, &code_type, &key, &asci_char) == 0){
			switch (code_type) {
			case KB_BINARY_MAKE_CODE :
				if( key == 0x5A) { // Pressed ENTER
					alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0); // Clear the screen
					alt_up_char_buffer_clear(char_buffer); // Clear char buffer
					alt_up_char_buffer_string(char_buffer, "Ready...", 35, 35);
					usleep(1000000); // wait for a bit to get ready
					alt_up_char_buffer_clear(char_buffer);
					return;
				}
			}
		}
	}

}


/*
 * Overview: Draws the high score screen as seen in the start screen.
 *
 */
void init_high_score_screen(alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y, struct high_score * highscore){

	alt_up_pixel_buffer_dma_dev* pixel_buffer = x;
	alt_up_char_buffer_dev * char_buffer = y;
	struct high_score* scores = (struct high_score *) highscore;
	char score_p1[CHAR_BUF_LENGTH]; // score buffers
	char score_p2[CHAR_BUF_LENGTH];

	//printf("Player 1 score is %c\n", scores->highscore_p1);
	//printf("Player 2 score is %c\n", scores->highscore_p2);
	sprintf( score_p1, "%c", scores->highscore_p1); // convert to string
	sprintf( score_p2, "%c", scores->highscore_p2);

	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_char_buffer_clear(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 320, 240, 0x0000, 0); // background colour

	alt_up_char_buffer_string(char_buffer, "High Score", 35, 12);
	alt_up_char_buffer_string(char_buffer, "Player 1:", 34, 18);
	alt_up_char_buffer_string(char_buffer, "Player 2:", 34, 22);
	alt_up_char_buffer_string(char_buffer, "Press ENTER to continue to the game...", 21, 40);

	alt_up_char_buffer_string(char_buffer, score_p1, 45, 18); //display player 1 score
	alt_up_char_buffer_string(char_buffer, score_p2, 45, 22); //display player 2 score

	return;
}

