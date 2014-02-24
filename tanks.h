/*
 * tanks.h
 *
 *  Created on: 2014-01-30
 *      Author: Kris_Mazurek, Tommy Cheang, Ellina Sergeyeva, Joanna Leung
 */

#ifndef TANKS_H_
#define TANKS_H_

#include <stdio.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include <alt_types.h>
#include "altera_up_avalon_ps2.h"
#include "altera_up_ps2_keyboard.h"
#include "altera_up_ps2_mouse.h"
#include <altera_up_sd_card_avalon_interface.h>
#include "sys/alt_timestamp.h"
#include "sys/alt_alarm.h"
#include <sys/alt_cache.h>
#include <stdlib.h>
#include "altera_up_avalon_audio_and_video_config.h"
#include "altera_up_avalon_audio.h"
#include "sys/alt_irq.h"


#define width 340
#define height 240
#define switches (char *) 0x0004460
#define leds (char *) 0x0004470
#define keys (char *) 0x0004490
#define COIN_SIZE 7720 //the size of the coin for buffer is 7720
#define COIN_LENGTH 200
#define DOH_SIZE 28727
#define DOH_LENGTH 745

#define ORIGIN 0
#define X_RANGE 320
#define Y_RANGE 240
#define X_SHIFT 2 // x shift for tank's movement
#define widthVGA 340 // VGA width
#define heightVGA 240 // VGA height
#define TANKWIDTH 20
#define TANKHEIGHT 15
#define INITIAL_X1 10 // initial x coordinate of tank 1
#define INITIAL_Y1 175 // initial y coordinate of tank 1
#define INITIAL_X2 200 // initial x coordinate of tank 2
#define INITIAL_Y2 175 // initial y coordinate of tank 2
#define TRUE 1
#define FALSE 0
#define TERRAIN_LENGTH 100
#define CHAR_BUF_LENGTH 10 // length of an intermediated char buffer
#define SD_CHAR_BUF_LENGTH 4 // length of an intermediated char buffer
#define SD_CHAR_BUF_LENGTH_LONG 4 // length of an intermediated char buffer
#define SD_CHAR_BUF_LENGTH_SHORT 3 // length of an intermediated char buffer
#define FILENAME_P1 "testp1.txt" // test file for Player 1 score
#define FILENAME_P2 "testp2.txt" // test file for Player 2 score
#define FILENAME_SCORE1 "tests1.txt" // file for Player 1 score
#define FILENAME_SCORE2 "tests2.txt" // file for Player 2 score

/*
 * Defines Gravity Coefficient and Energy Loss on Bounce
 * (optional, can be adapted to represent air friction)
 *
 */
#define GRAVITY 0.2
#define E_LOSS 1

// Structs

	struct bullet{
		double x;
		double y;
		double del_x;
		double del_y;
		int fired;
	};

	struct ground{
		int y_int;
		int slope;
	};

	struct tank{
		int x; // top left hand site X coordinate
		int y; // top left hand site Y coordinate
		int nozz_x;
		int nozz_y;
		int t_width; // tank's width
		int t_height; // tank's height
		int score;
		int tank_type; // 1 for tank1, 2 for tank2
		int weapon; //weapon
		int power; //power of the shot
	};

	struct terrain{
		int x;
		int y;
		int type; // type of terrain
		int x_left; // x boundary
		int x_right; // x boundary
	};

	struct high_score{
		char highscore_p1;
		char highscore_p2;
	};


// Functions

void draw_bombs(alt_up_pixel_buffer_dma_dev* x);
void draw_bullet(alt_up_pixel_buffer_dma_dev* x, struct bullet* b_1);
void update_physics(struct bullet* bullet);
void sd_card (void);
void delay(void);
void draw_map(struct ground* g,struct tank* t_1, struct tank* t_2, struct bullet* b_1, struct bullet* b_2,alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y,struct terrain* trn,int WIND);
void update(struct bullet* b_1);
int collision_1(struct ground* g,struct tank* t_1, struct tank* t_2, struct bullet* b_1, struct bullet* b_2,struct terrain* trn,alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y);
int collision_2(struct ground* g,struct tank* t_1, struct tank* t_2, struct bullet* b_1, struct bullet* b_2,struct terrain* trn,alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y);//tank2 collision theory
void fire(struct bullet* b_1,struct tank* t_1, int tank);
void refresh(struct ground* g,struct tank* t_1, struct tank* t_2, struct bullet* b_1, struct bullet* b_2, alt_up_char_buffer_dev * y);
void draw_tank(struct tank * Tanke);
void moveTankForward(struct tank * t_1,struct bullet* b_1,struct terrain* trn);
void moveTankBackward (struct tank * t_1,struct bullet* b_1,struct terrain* trn);
void aim(struct tank* t_1,struct bullet* b_1, int dir);
void start_screen(alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y);
void tutorial_screen(alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y);
void setTerrain(struct terrain* trn,struct tank * t);
void randomTerrain(struct terrain* trn);
void testsdcard(alt_up_sd_card_dev *device_reference);
void load_high_score( alt_up_sd_card_dev * sd, struct high_score * highscore );
void print_file( alt_up_sd_card_dev * sd, char * filename );
void store_high_score_sd_card( alt_up_sd_card_dev * sd, char * filename, struct tank * t );
void high_score_screen(alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y, alt_up_sd_card_dev * sd, alt_up_ps2_dev *keyb, struct high_score * highscore);
void init_high_score_screen(alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y, struct high_score * highscore);
void draw_tank1_start(alt_up_pixel_buffer_dma_dev* pixbuf, int x_pos, int y_pos);
void draw_tank2_start(alt_up_pixel_buffer_dma_dev* pixbuf, int x_pos, int y_pos);
void draw_tank1(alt_up_pixel_buffer_dma_dev* pixbuf, int x_pos, int y_pos);
void draw_tank2(alt_up_pixel_buffer_dma_dev* pixbuf, int x_pos, int y_pos);
void av_config_setup(void);
void sdcardcheck(alt_up_sd_card_dev *device_reference);
int readCoin(unsigned int *buffer, char* filename,short int handle);
int readDoh(unsigned int *buffer, char* filename, short int doh_handle);
void play_audio(alt_up_audio_dev *audio, unsigned int *buffer, short int handle);
void play_doh(alt_up_audio_dev *audio, unsigned int *buffer, short int handle);
void sound(void);
void sound_doh(void);


#endif /* TANKS_H_ */

