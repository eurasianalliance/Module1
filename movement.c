/*
 * movement.c
 *
 *  Created on: 2014-01-30
 *      Author: Tommy Cheang, Ellina Sergeyeva, Joanna Leung, Kris Mazurek
 */

#include "tanks.h"


/*
 * Overview:	Moves the tank forward if space permits.
 * 		Updates the x coordinate in the tank's struct.
 * 		Adjusted distance is set in X_SHIFT.
 */
void moveTankForward(struct tank * t_1, struct bullet* b_1,struct terrain* trn) {

	struct tank* tank=(struct tank *) t_1;
	struct bullet* bul_1=(struct bullet *) b_1;
	struct terrain* ter=(struct terrain *) trn;

	if( ((*tank).x + (*tank).t_width + X_SHIFT) < ter->x_right ) { // good to go
		(*tank).x = (*tank).x + X_SHIFT; // update x coordinate
		(*bul_1).x=(*bul_1).x+X_SHIFT;
		tank->nozz_x=tank->nozz_x + X_SHIFT;

	}
}

/*
 * Overview:	Moves a tank backward if space permits.
 * 		Updates the x values in the tank's struct.
 * 		Adjusted distance is set in X_SHIFT.
 */
void moveTankBackward (struct tank * t_1,struct bullet* b_1,struct terrain* trn) {

	struct tank* tank=(struct tank *) t_1;
	struct bullet* bul_1=(struct bullet *) b_1;
	struct terrain* ter=(struct terrain *) trn;

	if( (*tank).x - X_SHIFT >  ter->x_left ) { // good to go
		(*tank).x = (*tank).x - X_SHIFT; // update x coordinate
		(*bul_1).x=(*bul_1).x-X_SHIFT;
		tank->nozz_x=tank->nozz_x - X_SHIFT;
	}

}

/*
 * Overview: Moves a canon of the given tank given the dicrection of movement.
 *
 */
void aim(struct tank* t_1,struct bullet* b_1, int dir)
{
	struct tank* tank_1=(struct tank *) t_1;
	struct bullet* bul_1=(struct bullet *) b_1;


	if(dir==1)
	{
		if(tank_1->nozz_x <= (tank_1->x+(tank_1->t_width/2)))
		{
			if(tank_1->nozz_y<tank_1->y){
				tank_1->nozz_x--;
				tank_1->nozz_y++;
			}
		}
		else if(tank_1->nozz_x >= (tank_1->x+(tank_1->t_width/2)))
		{
			if(tank_1->nozz_y<tank_1->y){
				tank_1->nozz_x--;
				tank_1->nozz_y--;
			}
		}
		if((tank_1->nozz_x>(tank_1->x+(tank_1->t_width/2)))&& (tank_1->nozz_y>=tank_1->y))
		{
			tank_1->nozz_x--;
			tank_1->nozz_y--;
		}

	}
	else if (dir ==2)
	{
		if(tank_1->nozz_x < (tank_1->x+(tank_1->t_width/2)))
		{
			if(tank_1->nozz_y<tank_1->y){
				tank_1->nozz_x++;
				tank_1->nozz_y--;
			}
		}
		else if(tank_1->nozz_x >= (tank_1->x+(tank_1->t_width/2)))
		{
			if(tank_1->nozz_y<tank_1->y){
				tank_1->nozz_x++;
				tank_1->nozz_y++;
			}
		}
		if((tank_1->nozz_x<(tank_1->x+(tank_1->t_width/2)))&& (tank_1->nozz_y>=tank_1->y))
		{
			tank_1->nozz_x++;
			tank_1->nozz_y--;
		}

	}
}
