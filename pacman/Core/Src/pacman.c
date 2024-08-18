/*
 * pacman.c
 *
 *  Created on: Jul 18, 2024
 *      Author: esthe
 */

#include "pacman.h"
#include "i2c-lcd.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define width 20
#define height 4
#define TIM_FREQ 84000000

void pcm_game_init (Player * player, Enemy * enemy, Game_status * status) {
	// Player initialization
	player->row = 0;
	player->col = 0;
	player->food = 0;
	player->total_food = 0;

	// Populate the food location array
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 20; j++) {
			if (rand() % 4 == 1) {
				player->food_locations[i][j] = 1;
				player->total_food += 1;
			}
			else {
				player->food_locations[i][j] = 0;
			}
		}
	}

	// Enemy Initialization
	enemy->row = 3;
	enemy->col = 5;
	enemy->clock_before = 0;

	// Game status
	status = menu;
}

void pcm_display_game (Player * player, Enemy * enemy) {
	lcd_clear_display();
	for (int col = 9; col <= 19; col++) {
		lcd_cursor_pos(3, col);
		lcd_send_data(' ');
	}

	// Print the food
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 20; j++) {
			if (player->food_locations[i][j] == 1) {
				lcd_cursor_pos(i, j);
				lcd_send_data(0xa5); // this is not a custom character
			}
		}
	}

	// Print the enemy
	lcd_cursor_pos(enemy->row, enemy->col);
	lcd_send_data(1);

	// Print the player
	lcd_cursor_pos(player->row, player->col);
	lcd_send_data(0);
}

void pcm_display_enemy (Enemy * enemy) {
	// Print the enemy
	lcd_cursor_pos(enemy->row, enemy->col);
	lcd_send_data(1);
}

int pcm_move_player (Player * player, Direction direction) {
    // First, calculate the new position of the player
	switch (direction) {
		case up:
			player->row -= 1;
			if (player->row < 0) player->row = 0;
			break;
		case down:
			player->row += 1;
			if (player->row > 3) player->row = 3;
			break;
		case left:
			player->col -= 1;
			if (player->col < 0) player->col = 0;
			break;
		case right:
			player->col += 1;
			if (player->col > 19) player->col = 19;
			break;
		case none:
			break;
	}

	// Second, check if there is food in that new position
	if (player->food_locations[player->row][player->col] == 1) {
		player->food += 1;
		player->food_locations[player->row][player->col] = 0;
		return 1;
	}
	return 0;
}

void pcm_move_enemy (Player * player, Enemy * enemy, uint8_t pulse) {
	// The pulse makes sure that the enemy only moves once when the pulse changes
	// The logic here is to follow the player
	if (enemy->clock_before == 0 && pulse == 1) {
		if (player->row != enemy->row) {
				if (player->row < enemy->row) {
					enemy->row -= 1;
				}
				else {
					enemy->row += 1;
				}
			}
			else {
				if (player->col != enemy->col) {
					if (player->col < enemy->col) {
						enemy->col -= 1;
					}
					else {
						enemy->col += 1;
					}
				}
			}
		//pcm_display_enemy(enemy);
	}
}

void pcm_check_status (Player * player, Enemy * enemy, Game_status * status) {
	if (player->row == enemy->row && player->col == enemy->col) {
		*status = over;
	}
	else if (player->food == player->total_food) {
		*status = win;
	}
}

