/*
 * pacman.h
 *
 *  Created on: Jul 18, 2024
 *      Author: esthe
 */

#ifndef SRC_PACMAN_H_
#define SRC_PACMAN_H_

#include "stm32f4xx_hal.h"

typedef struct {
	int row;
	int col;
	int food;
	int total_food;
	int food_locations[4][20];
} Player;

typedef struct {
	int row;
	int col;
	uint8_t clock_before;
} Ghost;

typedef enum {
	menu,
	in_progress,
	over,
	win
} Game_status;

typedef enum {
	up,
	down,
	left,
	right
} Direction;

void game_init (Player * player, Ghost * ghost, Game_status status);
void game_display (Player * player, Ghost * ghost);
int move_player (Player * player, Direction direction);
void move_enemy (Player * player, Ghost * ghost, uint8_t pulse);
void check_status (Player * player, Ghost * ghost, Game_status * status);

#endif /* SRC_PACMAN_H_ */
