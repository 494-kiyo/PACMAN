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
} Enemy;

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
	right, none
} Direction;

void pcm_game_init (Player * player, Enemy * enemy, Game_status * status);
void pcm_display_game (Player * player, Enemy * enemy);
void pcm_display_enemy (Enemy * enemy);
int pcm_move_player (Player * player, Direction direction);
void pcm_move_enemy (Player * player, Enemy * enemy, uint8_t pulse);
void pcm_check_status (Player * player, Enemy * enemy, Game_status * status);

#endif /* SRC_PACMAN_H_ */
