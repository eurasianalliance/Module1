/*
 * utilities.c
 *
 *  Created on: 2014-01-30
 *      Author: Tommy Cheang, Joanna Leung, Ellina Sergeyeva, Kris_Mazurek
 */

#include "tanks.h"


// *********************** Audio related functions *************************************


//-----------------------------------------------------------------------------------------------------------------
/*
 * Overview: This configures the audio and video.
 *
 */
void av_config_setup()
{
	alt_up_av_config_dev * av_config =
			alt_up_av_config_open_dev("/dev/audio_video_config");
	if(av_config == NULL)
	{
		//printf("Configuration failed\n");
	}
	while (!alt_up_av_config_read_ready(av_config)){}
	//printf("Audio video configuration complete\n");
}
//---------------------------------------------------------------------------------------------------------------------------------------
/*
 * Overview:	This checks if the sdcard is connected or not
 *		This also checks if the SDCard is of the correct format of FAT16
 */
void sdcardcheck(alt_up_sd_card_dev *device_reference)
{
	char file_name[10];
	int connected = 0;

	if (device_reference != NULL)
	{
		while(1)
		{
			if ((connected == 0) && (alt_up_sd_card_is_Present()))
			{
				//printf("Card connected.\n");
				if (alt_up_sd_card_is_FAT16())
				{
					//printf("FAT16 file system detected.\n");
					if(alt_up_sd_card_find_first(".", (char*) file_name)==0)
					{
						//printf("%s\n",file_name);
						while(alt_up_sd_card_find_next((char*)file_name)==0)
						{
							//printf("%s\n", file_name);
							alt_up_sd_card_read(file_name);
						}
					}
					break;
				}
				else
				{
					//printf("Unknown file system.\n");
				}
				connected = 1;
			}
			else if ((connected == 1) && (alt_up_sd_card_is_Present() == false))
			{
				//printf("Card disconnected.\n"); connected = 0;
			}
		}
	}
	else
	{
		//printf("Card could not be opened\n");
	}
}

/*
 * Overview: This is the function for reading the bytes of the coin sound for when the bullet is shot out of the cannon.
 *
 */
int readCoin(unsigned int *buffer, char* filename, short int handle)
{

	short int data;
	unsigned char upper;
	unsigned char lower;
	int size;

	alt_up_audio_dev *audio=alt_up_audio_open_dev("/dev/audio");

	//printf("Now loading: %s\n", filename);

	handle = alt_up_sd_card_fopen(filename, false);
	if (handle < 0)
	{
		//printf("Failed to open the file");
		return;
	}

	int i;

	//printf("first for loop\n");
	for (i = 0; i < 46; i++)
	{
		alt_up_sd_card_read(handle);
	}

	size = 0;
	while (1)
	{
		////printf("inside the while loop\n");

		data = alt_up_sd_card_read(handle);
		////printf("data is 0x%x", data);

		if (data == -1)
		{
			break;
		}
		else
		{
			lower = data;
		}

		data = alt_up_sd_card_read(handle);
		if (data == -1)
		{
			break;
		}
		else
		{
			upper = data;
		}

		buffer[size] = ((upper << 8) | lower);
		////printf("buffer is 0x%x\n", buffer[size]);
		size++;
		if (size + 1 > COIN_SIZE)
		{//7720 for cha ching sound
			break;
		}
		//play_audio(audio, buffer, handle);
	}

	/*while(1)//do this to loop
    {
        play_audio(audio, buffer, handle);
    }*/

	////printf("Song size: %d\n", size);
	alt_up_sd_card_fclose(handle);

	return size;
}

/*
 * Overview: This is the function for reading the bytes of the boom sound for when the bullet hits a tank
 *
 */
int readDoh(unsigned int *buffer, char* filename, short int handle)
{
	short int data;
	unsigned char upper;
	unsigned char lower;
	int size;

	alt_up_audio_dev *audio=alt_up_audio_open_dev("/dev/audio");

	//printf("Now loading: %s\n", filename);

	handle = alt_up_sd_card_fopen(filename, false);
	if (handle < 0) {
		printf("Failed to open the file");
		return;
	}

	int i;

	//printf("first for loop\n");
	for (i = 0; i < 46; i++) {
		alt_up_sd_card_read(handle);
	}
	size = 0;
	while (1) {

		//printf("inside the while loop\n");

		data = alt_up_sd_card_read(handle);
		//printf("data is 0x%x", data);

		if (data == -1) {
			break;
		} else {
			lower = data;
		}

		data = alt_up_sd_card_read(handle);
		if (data == -1) {
			break;
		} else {
			upper = data;
		}

		buffer[size] = ((upper << 8) | lower);
		//printf("buffer is 0x%x\n", buffer[size]);
		size++;
		if (size + 1 > DOH_SIZE) {//7720 for cha ching sound
			break;
		}
		//play_doh(audio, buffer, handle);
	}

	//break;
	//printf("Song size: %d\n", size);
	alt_up_sd_card_fclose(handle);

	return size;
}

/*
 * Overview: This plays the audio for the coin sound
 *
 */
void play_audio(alt_up_audio_dev *audio, unsigned int *buffer, short int handle)
{
	int lbytes;
	int rbytes;
	int lindex=22;
	int rindex=22;
	alt_up_audio_dev* aud=audio;
	int i=0;

	while(i<COIN_LENGTH) //200 for cha ching
	{
		if (alt_up_audio_write_fifo_space(audio, ALT_UP_AUDIO_LEFT) > 22)
		{
			lbytes = alt_up_audio_write_fifo(aud, &buffer[lindex], 96, ALT_UP_AUDIO_LEFT);
			rbytes = alt_up_audio_write_fifo(aud, &buffer[rindex], 96, ALT_UP_AUDIO_RIGHT);
			lindex += lbytes;
			rindex += rbytes;
			i++;
		}
	}
	//printf("all good things come to an end\n");
	alt_up_sd_card_fclose(handle);
}

/*
 * Overview: This plays the boom sound when the tanks are hit
 *
 */
void play_doh(alt_up_audio_dev *audio, unsigned int *buffer, short int handle)
{

	int lbytes;
	int rbytes;
	int lindex=22;
	int rindex=22;
	alt_up_audio_dev* aud=audio;
	int i=0;


	while(i<DOH_LENGTH) //200 for cha ching
	{
		if (alt_up_audio_write_fifo_space(audio, ALT_UP_AUDIO_LEFT) > 22)
		{
			lbytes = alt_up_audio_write_fifo(aud, &buffer[lindex], 96, ALT_UP_AUDIO_LEFT);
			rbytes = alt_up_audio_write_fifo(aud, &buffer[rindex], 96, ALT_UP_AUDIO_RIGHT);
			lindex += lbytes;
			rindex += rbytes;
			i++;
		}

	}
	//printf("all good things come to an end\n");
	alt_up_sd_card_fclose(handle);
}


//----------------------------------------------------------------------------------------------------------------------------

/*
 * Overview: The origins of the coin sound
 *
 */void sound()
{
	short int handle;
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

	readCoin(buffer, filename, handle);
	play_audio(audio, buffer, handle);

	alt_up_sd_card_fclose(filename);

}

/*
 * Overview: The origins of the boom sound
 *
 */
void sound_doh()
{
	short int handle;
	short int doh_handle;
	int check;
	//printf("SDCARD CONNECTION CHECK\n");
	alt_up_sd_card_dev *device_reference=alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
	alt_up_audio_dev *audio;
	sdcardcheck(device_reference);

	//printf("AV CONFIG SETUP\n");
	av_config_setup();

	//printf("AUDIO OPEN\n");
	audio=alt_up_audio_open_dev("/dev/audio");
	unsigned int buffer[DOH_SIZE];
	char *filename="boom1.wav";

	readDoh(buffer, filename, doh_handle);
	play_audio(audio, buffer, handle);

	alt_up_sd_card_fclose(filename);

}



// *********************** High Score related functions ********************************



/*
 * Overview: Stores score on SD card.
 *
 */
void store_high_score_sd_card( alt_up_sd_card_dev * sd, char * filename, struct tank * t ){

	struct tank* tank = (struct tank *) t;
	int file_handle; // write to this file
	int i = 0; // index
	char buffer[SD_CHAR_BUF_LENGTH]; // buffer

	sprintf( buffer, "%d", tank->score); // put integer to a char buffer

	if(sd != NULL) {
		if(alt_up_sd_card_is_Present()) {

			file_handle =alt_up_sd_card_fopen(filename, false);
			if(file_handle < 0)
				printf("Text file open failed\n");
			else {
				//printf("\nStoring data...\n");

				for(i =0; i < SD_CHAR_BUF_LENGTH; i++) {
					alt_up_sd_card_write(file_handle, buffer[i]);
				}

				//printf("Done storing and Closing File...\n");
				alt_up_sd_card_fclose(file_handle);
				//printf("Closed the file\n\n");
			}
		}
	}
}


/*
 * Overview: Helper function to print out the contents of the given file to console.
 *
 */
void print_file( alt_up_sd_card_dev * sd, char * filename  ){

	char buf_read [SD_CHAR_BUF_LENGTH_LONG];
	int file;
	int i;

	if(sd != NULL){
		if(alt_up_sd_card_is_Present()) {
			file = alt_up_sd_card_fopen(filename, false);

			if(file < 0)
				printf("Text File open failed\n");
			else {

				//printf("Reading from file...\n");
				for(i=0; i<SD_CHAR_BUF_LENGTH_LONG; i++) {
					buf_read[i]=alt_up_sd_card_read(file);
				}
				//printf("Done reading\n");

				alt_up_sd_card_fclose(file);
				//printf("Closed the file\n");

				printf("\nPrinting out file contents\n");

				for (i = 0; i <SD_CHAR_BUF_LENGTH_LONG; i++ ) {
					printf("%c", buf_read[i] );
				}
				printf("\n");

			}
		}
	}
}


/*
 * Overview: Read high score of the previous game
 *
 */
void load_high_score( alt_up_sd_card_dev * sd, struct high_score * highscore )
{

	struct high_score* scores = (struct high_score *) highscore;
	char buf1[SD_CHAR_BUF_LENGTH_SHORT]; // player 1 buffer
	char buf2[SD_CHAR_BUF_LENGTH_SHORT]; // player 2 buffer
	int intBuf1[SD_CHAR_BUF_LENGTH_SHORT];
	int intBuf2[SD_CHAR_BUF_LENGTH_SHORT];
	int file_player1, file_player2; // file handles
	int i = 0; //index

	if(sd != NULL){
		if(alt_up_sd_card_is_Present()) {

			// Player 1 previous score
			file_player1 = alt_up_sd_card_fopen(FILENAME_SCORE1, false);
			if(file_player1 < 0) {
				printf("Text File open failed\n");
				return;
			}
			else{
				//printf("\nPlayer 1: Reading prev score\n");

				for(i=0; i<SD_CHAR_BUF_LENGTH_SHORT; i++) {
					buf1[i]=alt_up_sd_card_read(file_player1);
				}
				alt_up_sd_card_fclose(file_player1);
			}

			// Player 2 previous score
			file_player2 = alt_up_sd_card_fopen(FILENAME_SCORE2, false);
			if(file_player2 < 0) {
				printf("Text File open failed\n");
				return;
			}
			else{
				//printf("Player 2: Reading prev score\n");

				for(i=0; i<SD_CHAR_BUF_LENGTH_SHORT; i++) {
					buf2[i]=alt_up_sd_card_read(file_player2);
				}
				alt_up_sd_card_fclose(file_player2);
			}
		}
	}

	if(buf1[0] != NULL ){
		scores->highscore_p1 = buf1[0]; // load the value to player 1 highscore struct
	}
	else
		printf("Null reference p1\n");

	if(buf2[0] != NULL ){
		scores->highscore_p2 = buf2[0]; // load the value to player 2 highscore struct
	}
	else
		printf("Null reference p1\n");

	return;

}


/*
 * Overview:	Helper function to test SD card.
 *		Check connectivity, file system, and any present files.
 *
 */
void testsdcard(alt_up_sd_card_dev *device_reference)
{
	char file_name[10];
	int connected = 0;

	if (device_reference != NULL)
	{
		while(1)
		{
			if ((connected == 0) && (alt_up_sd_card_is_Present()))
			{
				printf("Card connected.\n");
				if (alt_up_sd_card_is_FAT16())
				{
					printf("FAT16 file system detected.\n");
					if(alt_up_sd_card_find_first(".", (char*) file_name)==0)
					{
						printf("%s\n",file_name);
						while(alt_up_sd_card_find_next((char*)file_name)==0)
						{
							printf("%s\n", file_name);
							alt_up_sd_card_read(file_name);
						}
					}
					break;
				}
				else
				{
					printf("Unknown file system.\n");
				}
				connected = 1;
			}
			else if ((connected == 1) && (alt_up_sd_card_is_Present() == false))
			{
				printf("Card disconnected.\n"); connected = 0;
			}
		}
	}
	else
	{
		printf("Card could not be opened\n");
	}
}

/*
 * Overview: exercise 3 reads sd_card and list its file.
 *
 */
void sd_card(void){
	char file_name[10];
	alt_up_sd_card_dev *device_reference = NULL;
	int connected = 0;

	device_reference = alt_up_sd_card_open_dev(ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_NAME);
	if (device_reference != NULL) {
		while(1) {
			if ((connected == 0) && (alt_up_sd_card_is_Present())) {
				//printf("Card connected.\n");
				if (alt_up_sd_card_is_FAT16()) {
					//printf("FAT16 file system detected.\n");
					if(alt_up_sd_card_find_first(".", (char*) file_name)==0){
						//printf("%s\n",file_name);
						while(alt_up_sd_card_find_next((char*)file_name)==0)
						{
							//printf("%s\n", file_name);
						}
					}
				} else {
					//printf("Unknown file system.\n");
				}
				connected = 1;
			} else if ((connected == 1) && (alt_up_sd_card_is_Present() == false)) {
				//printf("Card disconnected.\n");
				connected = 0;
			}
			break;
		}
	} else {
		//printf("Card could not be opened\n");
	}
	//printf("sd_card function finished\n");
}

