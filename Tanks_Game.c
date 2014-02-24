/*
 * Tanks_Game.c
 *
 *  Created on: 2014-01-30
 *      Author: Kris_Mazurek, Tommy Cheang, Ellina Sergeyeva, Joanna Leung
 */

#include "tanks.h"
#include "sys/alt_timestamp.h"


// Global variables
alt_up_pixel_buffer_dma_dev* pixel_buffer;
alt_up_char_buffer_dev *char_buffer;
int score =0;
int turn=0;
int dir=0;
int GameStarted = FALSE; // Initialized to FALSE. Set to TRUE by pressing ENTER.
int shot=0; //number of times fire is pressed
int WIND = 0;




int main(void) {
	struct ground g ={175,0};//ground with 0 slope and 175 unit
	/*
	 *
	 * tank_1->nozz_x=tank_1->x+15;
	 * tank_2->nozz_x=tank_2->x-3;
	 * tank_1->nozz_y=tank_1->y-1;
	 * tank_2->nozz_y=tank_1->y-1;
	 */

	struct tank t_1 ={10,166,17,160,13,9,0,1,1,100};//tank 1
	struct tank t_2 ={280,166,285,160,13,9,0,2,1,100};//tank 2
	struct bullet b_1 = {t_1.x+7,t_1.y,0,0,0};
	struct bullet b_2 = {t_2.x+5,t_2.y,0,0,0};
	struct terrain ter = {0, 175,0,0,320}; // terrain 0 by default
	struct high_score prevScore; // scores of players 1 and 2


	// **************************** Initialize VGA ****************************

	//define pixel_buffer
	alt_up_pixel_buffer_dma_dev* pixel_buffer;

	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/pixel_buffer_dma");

	//Define buffer addresses
	unsigned int pixel_buffer_addr1 = PIXEL_BUFFER_BASE;
	unsigned int pixel_buffer_addr2 = PIXEL_BUFFER_BASE + (320 * 240 * 2);

	//Set the first buffer address
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,pixel_buffer_addr1);

	// Swap background and foreground buffers
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	// Wait for the swap to complete
	while(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));

	//Set the 2nd buffer address
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,pixel_buffer_addr2);

	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);

	alt_up_char_buffer_dev *char_buffer;
	char_buffer = alt_up_char_buffer_open_dev("/dev/char_drawer");
	alt_up_char_buffer_init(char_buffer);

	//alt_up_char_buffer_string(char_buffer, "0" ,6 , 0);
	alt_up_char_buffer_clear(char_buffer); // Clear char buffer


	// **************************** Keyboard ***********************************

	alt_up_ps2_dev *keyboard;
	keyboard = alt_up_ps2_open_dev("/dev/keyboard"); // open the device

	if( keyboard == NULL ) {
		//printf("Error opening keyboard device\n");
	}
	else {
		//printf("Opened the keyboard device\n");
	}

	// initialilze the device
	alt_up_ps2_init(keyboard);

	// clear the FIFO
	alt_up_ps2_clear_fifo(keyboard);

	int status;
	alt_u8 key = 0;
	char asci_char;
	KB_CODE_TYPE code_type;


	// ************************ SD card *****************************

	alt_up_sd_card_dev *sd_card = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
	testsdcard(sd_card);

	// Create an empty file for player 1
	//int file_handle_test = alt_up_sd_card_fopen(FILENAME_P1, true);
	//alt_up_sd_card_fclose(file_handle_test);

	// Create an empty file for player 2
	//int file_handle_test2 = alt_up_sd_card_fopen(FILENAME_P2, true);
	//alt_up_sd_card_fclose(file_handle_test2);


	/********************************SOUND INIT*****************/
	short int handle;
	short int doh_handle;
	//short int doh_handle;
   	//printf("SDCARD CONNECTION CHECK\n");
   	alt_up_sd_card_dev *device_reference=alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
   	alt_up_audio_dev *audio;
   	sdcardcheck(device_reference);

    	//printf("AV CONFIG SETUP\n");
    	av_config_setup();

    	//printf("AUDIO OPEN\n");
    	audio=alt_up_audio_open_dev("/dev/audio");
    	unsigned int buffer[COIN_SIZE];
    	char *filename="coin.wav";

    	unsigned int buffer1[DOH_SIZE];
    	char *dohfile="boom1.wav";

    	readDoh(buffer1, dohfile, doh_handle);
    	//play_doh(audio, buffer1, doh_handle);

    	readCoin(buffer, filename, handle);
    	//play_audio(audio, buffer, handle);

    	alt_up_sd_card_fclose(filename);
    	alt_up_sd_card_fclose(dohfile);

    	//void sound_doh();
	/********************************SOUND INIT END************/


	start_screen(pixel_buffer, char_buffer); // Draw the start screen
	load_high_score( sd_card, &prevScore ); // Load the scores to the high score struct

	//readDoh(buffer1, dohfile, doh_handle, GameStarted);

	while(1)
	{
		/*if( key == 0x5A) { // Pressed ENTER
			break;
		}
			play_doh(audio, buffer1, doh_handle);*/
		//play_doh(audio, buffer, handle);

		status = decode_scancode(keyboard, &code_type, &key, &asci_char);
		if( GameStarted == FALSE
		{
			//play_doh(audio, buffer1, doh_handle);

			if( status == 0){
				switch (code_type) {
				case KB_BINARY_MAKE_CODE :

					if( key == 0x5A) { // Pressed ENTER

					    	play_audio(audio, buffer, handle);
						GameStarted = TRUE; // Start the game
						randomTerrain(&ter); // choose a random terrain
						//printf("Player 1 prev score is %c\n", prevScore.highscore_p1);
						//printf("Player 2 prev score is %c\n", prevScore.highscore_p2);
						alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0); // Clear the screen
						alt_up_char_buffer_clear(char_buffer); // Clear char buffer
						alt_up_char_buffer_string(char_buffer, "Starting the game...", 30, 35);
						usleep(1400000);
						alt_up_char_buffer_clear(char_buffer);
					}
					break;
				case KB_ASCII_MAKE_CODE :
					if(asci_char == 'T' ) { // display tutorial
						tutorial_screen(pixel_buffer, char_buffer);
					}
					if( asci_char == 'P'){ // display high score
						init_high_score_screen(pixel_buffer, char_buffer, &prevScore); // display high scores
					}
					break;
				default:
					break;
				}
			}

		}

		if(GameStarted == TRUE) // User pressed ENTER -- Ready to start the game
		{ 

			while(1)
			{
				if(rand()%2==1)
				{
					alt_up_char_buffer_clear(char_buffer); // Clear char buffer
					WIND=(rand()%5);
				}
				else
				{
					WIND=-(rand()%5);
				}

				while(turn==0)//tank 1 functions
				{
					status = decode_scancode(keyboard, &code_type, &key, &asci_char);
					alt_up_char_buffer_string(char_buffer, "Player 1's turn!", 30, 20);
					store_high_score_sd_card( sd_card, FILENAME_SCORE1, &t_1); // store the current score on SD card

					if(shot<t_1.weapon)
					{
						if( status == 0){
							switch (code_type) {
							case KB_BINARY_MAKE_CODE :
								if(key == 0x29 )//space key fire
								{
									play_audio(audio, buffer, handle);
									fire(&b_1,&t_1,1);
									b_1.fired = 1;
									shot++;
								}
							case KB_LONG_BINARY_MAKE_CODE:
								if( key == 0x74 ) // right arrow key
								{
									setTerrain(&ter,&t_1); // set terain's values for tank 1
									moveTankForward( &t_1, &b_1,&ter);
								}
								else if( key == 0x6B ) // left arrow key
								{
									setTerrain(&ter,&t_1); // set terain's values for tank 1
									moveTankBackward( &t_1, &b_1,&ter);
								}
								else if( key == 0x75) // up arrow key
								{
									dir=1;
									aim(&t_1,&b_1,dir);
								}
								else if( key == 0x72) // down arroy key
								{
									dir=2;
									aim(&t_1,&b_1,dir);
								}
								break;
							case KB_ASCII_MAKE_CODE :
								if(asci_char == 'R' ) { // R key
									randomTerrain(&ter); // debugging: choose a random terrain
									setTerrain(&ter,&t_1);
								}
								else if(asci_char == '1' ) { // 1 key
									t_1.weapon=1;
								}
								else if(asci_char == '2' ) { // 2 key
									t_1.weapon=2;
								}
								else if(asci_char == 'W' ) { // W key
									if(t_1.power<100)
										t_1.power=t_1.power+1;
								}
								else if(asci_char == 'S' ) { // S key
									if(t_1.power>0)
										t_1.power=t_1.power-1;
									if(t_1.power == 99)
										alt_up_char_buffer_clear(char_buffer); // Clear char buffer
									if(t_1.power==9)
										alt_up_char_buffer_clear(char_buffer); // Clear char buffer
								}
								if( asci_char == 'P'){ // P key
									high_score_screen(pixel_buffer, char_buffer, sd_card, keyboard, &prevScore); // display high scores
									//print_file(sd_card, FILENAME_SCORE1); // print contents of the given file
								}
								break;
							}
						}
					}
					/* Papa Kris's Physics function */
					update_physics(&b_1);

					if(collision_1(&g, &t_1, &t_2,&b_1,&b_2,&ter,pixel_buffer,char_buffer)==1)//if hit, delay for a little then reset the position of the tanks
					{
						play_doh(audio, buffer1, doh_handle);
						turn=1;
						draw_map(&g, &t_1, &t_2,&b_1,&b_2,pixel_buffer,char_buffer,&ter,WIND);

						//delay();
						refresh(&g, &t_1, &t_2,&b_1,&b_2,char_buffer);

						randomTerrain(&ter); // choose a random terrain
						setTerrain(&ter,&t_1); // set this terrain's coordinates
						store_high_score_sd_card( sd_card, FILENAME_SCORE1, &t_1); // store the current score on SD card
					}

					draw_map(&g, &t_1, &t_2,&b_1,&b_2,pixel_buffer,char_buffer,&ter,WIND);
					alt_dcache_flush_all();
				}
				//delay();

				while(turn==1)//tank 2 functions
				{
					status = decode_scancode(keyboard, &code_type, &key, &asci_char);
					alt_up_char_buffer_string(char_buffer, "Player 2's turn!", 30, 20);
					store_high_score_sd_card( sd_card, FILENAME_SCORE2, &t_2 ); // store the current score on SD card

					if(shot<t_2.weapon)
					{
						if( status == 0){
							switch (code_type) {
							case KB_BINARY_MAKE_CODE:
								if(key == 0x29) // space key -- fire
								{
									play_audio(audio, buffer, handle);
									fire(&b_2,&t_2, 2);
									b_2.fired = 1;
									shot++;
								}
							case KB_LONG_BINARY_MAKE_CODE :
								if( key == 0x74) // right arrow key
								{
									setTerrain(&ter,&t_2);  // set terain's values for tank 2
									moveTankForward(&t_2, &b_2,&ter);
								}

								else if( key == 0x6B) // left arrow key
								{
									setTerrain(&ter,&t_2); // set terain's values for tank 2
									moveTankBackward( &t_2, &b_2,&ter);
								}
								else if(key == 0x75) // up arrow key
								{
									dir=1;
									aim(&t_2,&b_2,dir);
								}
								else if(key == 0x72) // down arrow key
								{
									dir=2;
									aim(&t_2,&b_2,dir);
								}
							case KB_ASCII_MAKE_CODE :
								if(asci_char == 'R' ) { // R key
									randomTerrain(&ter); // Debugging: choose a random terrain
									setTerrain(&ter,&t_1);
								}
								else if(asci_char == '1' ) { // 1 key
									t_2.weapon=1;
								}
								else if(asci_char == '2' ) { // 2 key
									t_2.weapon=2;
								}
								else if(asci_char == 'W' ) { // W key
									if(t_2.power<100)
										t_2.power++;
								}
								else if(asci_char == 'S' ) { // S key
									if(t_2.power>0)
										t_2.power--;
									if(t_2.power == 99)
										alt_up_char_buffer_clear(char_buffer); // Clear char buffer
									if(t_2.power==9)
										alt_up_char_buffer_clear(char_buffer); // Clear char buffer

								}
								if( asci_char == 'P'){ // P key
									high_score_screen(pixel_buffer, char_buffer, sd_card, keyboard, &prevScore); // display high scores
									//print_file(sd_card, FILENAME_SCORE2); // print contents of the given file
								}
								break;
							}
						}
					}

					/* Papa Kris's physics function*/
					update_physics(&b_2);

					if(collision_2(&g, &t_1, &t_2,&b_1,&b_2,&ter,pixel_buffer,char_buffer)==1)//if hit, delay for a little then reset the position of the tanks
					{
						play_doh(audio, buffer1, doh_handle); //put here boom
						turn=0;
						draw_map(&g, &t_1, &t_2,&b_1,&b_2,pixel_buffer,char_buffer,&ter,WIND);

						//delay();
						refresh(&g, &t_1, &t_2,&b_1,&b_2,char_buffer);

						randomTerrain(&ter); // choose a random terrain
						setTerrain(&ter,&t_2); // set this terrain's coordinates
						store_high_score_sd_card( sd_card, FILENAME_SCORE2, &t_2 ); // store the current score on SD card

					}

					draw_map(&g, &t_1, &t_2,&b_1,&b_2,pixel_buffer,char_buffer,&ter,WIND);
					alt_dcache_flush_all();
				}

				delay();
			}
		}
	}
	//printf("thanks for playing\n");
	return 0;
}



/*
 * Overview:	Detects collision on tank 1 turn.
 *		Updates the current score if hit.
 *
 */
int collision_1(struct ground* g,struct tank* t_1, struct tank* t_2, struct bullet* b_1, struct bullet* b_2,struct terrain* trn,alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y)
{
	struct ground* ground=(struct ground *) g;
	struct tank* tank_1=(struct tank *) t_1;
	struct tank* tank_2=(struct tank *) t_2;
	struct bullet* bul_1=(struct bullet *) b_1;
	struct bullet* bul_2=(struct bullet *) b_2;
	struct terrain* ter = (struct terrain *) trn;
	alt_up_char_buffer_dev * char_buffer = y;

	if( ((bul_1->x >= tank_2->x) && (bul_1->x<=(tank_2->x+tank_2->t_width))) &&    ( bul_1->y >= tank_2->y && (bul_1->y<=(tank_2->y+tank_2->t_height))))
	{
		//alt_up_char_buffer_string(char_buffer, "Player 1 Wins", 30, 20);
		(*bul_1).x=t_1->x+7;
		(*bul_1).y=t_1->y;
		(*bul_1).del_x=0;
		bul_1->del_y=0;
		(*t_2).x=999;
		t_2->nozz_x=999;
		bul_2->x=t_2->x+5;
		bul_1->fired = 0;
		tank_1->score++; // tank 1 wins the turn
		shot=0;
		return 1;
	}
	if((*bul_1).x>341 ||(*bul_1).x<0 || bul_1->y>ground->y_int || bul_1->y <0)
	{
		(*bul_1).x=t_1->x+7;
		(*bul_1).del_x=0;
		(*bul_1).y=t_1->y;
		(*bul_1).del_y=0;
		(*bul_1).fired = 0;
		turn=1;
		shot=0;
		return 2;
	}
	if(ter->type == 2) { // tree
		if( bul_1->x > 135 && bul_1->x < 175 && bul_1->y > 123 && bul_1->y < 170 ) {// bullet hit the crown
			(*bul_1).x=t_1->x+7;
			(*bul_1).del_x=0;
			(*bul_1).y=t_1->y;
			(*bul_1).del_y=0;
			(*bul_1).fired = 0;
			turn=1;
			shot=0;
			return 3;
		}
		if( bul_1->x > 151 && bul_1->x < 158 && bul_1->y > 160 && bul_1->y < 175 ) { // bullet hit the trunk
			(*bul_1).x=t_1->x+7;
			(*bul_1).del_x=0;
			(*bul_1).y=t_1->y;
			(*bul_1).del_y=0;
			(*bul_1).fired = 0;
			turn=1;
			shot=0;
			return 3;
		}
	}

	return 0;
}


/*
 * Overview:	Detects collision on tank 2 turn.
 *		Updates the current score if hit.
 *
 */
int collision_2(struct ground* g,struct tank* t_1, struct tank* t_2, struct bullet* b_1, struct bullet* b_2,struct terrain* trn,alt_up_pixel_buffer_dma_dev* x, alt_up_char_buffer_dev * y)
{
	struct ground* ground=(struct ground *) g;
	struct tank* tank_1=(struct tank *) t_1;
	struct tank* tank_2=(struct tank *) t_2;
	struct bullet* bul_1=(struct bullet *) b_1;
	struct bullet* bul_2=(struct bullet *) b_2;
	alt_up_char_buffer_dev * char_buffer = y;
	struct terrain* ter = (struct terrain *) trn;

	if( ((bul_2->x >= tank_1->x) && (bul_2->x<=(tank_1->x+tank_1->t_width))) &&    ( bul_2->y >= tank_1->y && (bul_2->y<=(tank_1->y+tank_1->t_height))))
	{
		//alt_up_char_buffer_string(char_buffer, "Player 1 Wins", 30, 20);
		(*bul_2).x=t_2->x+5;
		(*bul_2).y=t_2->y;
		(*bul_2).del_x=0;
		bul_2->del_y=0;
		(*t_1).x=999;
		t_1->nozz_x=999;
		bul_1->x=t_1->x+7;
		bul_2->fired = 0;
		tank_2->score++; // tank 2 wins the turn
		shot=0;
		return 1;
	}
	if((*bul_2).x>341 ||(*bul_2).x<0 || bul_2->y>ground->y_int || bul_2->y <0)
	{
		(*bul_2).x=t_2->x+5;
		(*bul_2).del_x=0;
		(*bul_2).y=t_1->y;
		(*bul_2).del_y=0;
		(*bul_2).fired = 0;
		turn=0;
		shot=0;
		return 2;
	}
	if(ter->type == 2){ // tree
		if( bul_2->x > 135 && bul_2->x < 175 && bul_2->y > 123 && bul_2->y < 170 ){ // bullet hit crown of the tree
			(*bul_2).x=t_2->x+5;
			(*bul_2).del_x=0;
			(*bul_2).y=t_1->y;
			(*bul_2).del_y=0;
			(*bul_2).fired = 0;
			turn=0;
			shot=0;
			return 3;
		}
		if( bul_2->x > 151 && bul_2->x < 158 && bul_2->y > 160 && bul_2->y < 175 ){ // bullet hit trunk of the tree
			(*bul_2).x=t_2->x+5;
			(*bul_2).del_x=0;
			(*bul_2).y=t_1->y;
			(*bul_2).del_y=0;
			(*bul_2).fired = 0;
			turn=0;
			shot=0;
			return 3;
		}
	}
	return 0;
}


/*
 * Overview: Fires a bullet of the given tank.
 *
 */
void fire(struct bullet* b_1, struct tank* t_1, int tank)
{
	struct bullet* bul_1=(struct bullet *) b_1;
	struct tank* tank_1=(struct tank *) t_1;
	int i;
	if(tank==1)
	{
		bul_1->del_x=(double)(tank_1->nozz_x-(tank_1->x+(tank_1->t_width/2)+1))*((double)tank_1->power/50);
		bul_1->del_y=(double)(tank_1->nozz_y-tank_1->y)*((double)tank_1->power/50);
	}
	else if(tank==2)
	{
		bul_1->del_x=(tank_1->nozz_x-(tank_1->x+(tank_1->t_width/2)-1))*((double)tank_1->power/50);
		bul_1->del_y=(tank_1->nozz_y-tank_1->y)*((double)tank_1->power/50);
	}
	else
		//printf("exit fire function\n");
		return;
}


/*
 * Overview: Refresh tanks and bullets settings after collision.
 *
 */
void refresh(struct ground* g,struct tank* t_1, struct tank* t_2, struct bullet* b_1, struct bullet* b_2, alt_up_char_buffer_dev * y)
{
	struct ground* ground=(struct ground *) g;
	struct tank* tank_1=(struct tank *) t_1;
	struct tank* tank_2=(struct tank *) t_2;
	struct bullet* bul_1=(struct bullet *) b_1;
	struct bullet* bul_2=(struct bullet *) b_2;
	alt_up_char_buffer_dev * char_buffer = y;

	tank_1->x =10;
	tank_1->y=166;
	tank_2->x=280;
	tank_2->y=166;
	tank_1->nozz_x=tank_1->x+7;
	tank_2->nozz_x=tank_2->x+5;
	tank_1->nozz_y=tank_1->y-6;
	tank_2->nozz_y=tank_1->y-6;
	bul_1->x=tank_1->x+7;
	bul_1->y=tank_1->y;
	bul_2->x=tank_2->x+5;
	bul_2->y=tank_2->y;
	if(rand()%2==1)
	{
		alt_up_char_buffer_clear(char_buffer); // Clear char buffer
		WIND=(rand()%5);
	}
	else
	{
		WIND=-(rand()%5);
	}

	bul_1->fired=0;
	bul_2->fired=0;


}


/*
 * Overview: Delays for 1 second using system clock timer.
 *
 */
void delay(void)
{
	float duration;
	int ticks_start;
	int ticks_end;
	int ticks_per_s;
	int ticks_duration;

	//printf("Timers\n");
	//printf(" Sys Clock Timer\n");
	ticks_per_s = alt_ticks_per_second();
	//printf(" Tick Freq: %d\n", ticks_per_s);
	//printf(" Recording starting ticks\n");
	ticks_start = alt_nticks();
	//printf(" Sleeping for 5 seconds\n");
	usleep(1000000);
	//printf(" Recording ending ticks\n");
	ticks_end = alt_nticks();
	ticks_duration = ticks_end - ticks_start;
	duration = (float) ticks_duration / (float) ticks_per_s;
	//printf(" The program slept for %d ticks (%f seconds)\n\n", ticks_duration,duration);
}


/*
 * Overview: Set the coordinates for the current terrain.
 *
 */
void setTerrain(struct terrain* trn, struct tank * t){

	struct terrain* ter = (struct terrain *) trn;
	struct tank* tank=(struct tank *) t;

	if(ter->type == 0){ // flat terrain
		ter->x_left = 0;
		ter->x_right = 320;
		ter->x = 0;
		ter->y = 175;
	}
	else if(ter->type == 1) { // water terrain
		if(tank->tank_type == 1) { // tank 1
			ter->x_left = 0;
			ter->x_right = ter->x+101;
		}
		else{ // tank 2
			ter->x_left = 200;
			ter->x_right = 320;
		}
	}
	else if(ter->type == 2){ // tree terrain
		if(tank->tank_type == 1) { // tank 1
			ter->x_left = 0;
			ter->x_right = 134;
		}
		else{ // tank 2
			ter->x_left = 176;
			ter->x_right = 320;
		}
	}
	else
		return;
}


/*
 * Overview: Generate a pseudo-random terrain.
 *
 */
void randomTerrain(struct terrain* trn){

	struct terrain* ter = (struct terrain *) trn;

	int random = rand() %3; // random number between 0 and 2
	ter->type = random;
}


/*
 * Overview: Adds gravity to the delta_y coefficient of the bullet (vertical speed), and updates coordinates.
 *
 */
void update_physics(struct bullet* bullet)
{
	struct bullet* b =(struct bullet *) bullet;
	(*b).x = (*b).x + (*b).del_x;
	(*b).y = (*b).y + (*b).del_y;
	if((*b).fired == 1)
	{
		(*b).del_y = (*b).del_y + GRAVITY;
		b->del_x=b->del_x+((float)WIND/100);
	}
}

