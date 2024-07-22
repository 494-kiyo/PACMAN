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

void game_init (Player * player, Ghost * ghost, Game_status status) {
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
	ghost->row = 3;
	ghost->col = 2;
	ghost->clock_before = 0;

	// Game status
	status = menu;
}

void game_display (Player * player, Ghost * ghost) {
	lcd_clear_display();
	lcd_cursor_pos(player->row, player->col);
	lcd_send_data(0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 20; j++) {
			if (player->food_locations[i][j] == 1) {
				lcd_cursor_pos(i, j);
				lcd_send_data(0xa5);
			}
		}
	}
	lcd_cursor_pos(ghost->row, ghost->col);
	lcd_send_data(1);
}

int move_player (Player * player, Direction direction) {
	// First, calculate the new position of the player
	switch (direction) {
		case up:
			player->row -= 1;
			if (player->row < 1) player->row = 1;
		case down:
			player->row += 1;
			if (player->row > 4) player->row = 4;
		case left:
			player->col -= 1;
			if (player->col < 1) player->col = 1;
		case right:
			player->col += 1;
			if (player->col > 20) player->col = 20;
	}

	// Second, check if there is food in that new position
	if (player->food_locations[player->row][player->col] == 1) {
		player->food += 1;
		player->food_locations[player->row][player->col] = 0;
	}
	return 1;
}

void move_enemy (Player * player, Ghost * ghost, uint8_t pulse) {
	if (ghost->clock_before == 0 && pulse == 1) {
		if (player->row != ghost->row) {
				if (player->row < ghost->row) {
					ghost->row -= 1;
				}
				else {
					ghost->row += 1;
				}
			}
			else {
				if (player->col != ghost->col) {
					if (player->col < ghost->col) {
						ghost->col -= 1;
					}
					else {
						ghost->col += 1;
					}
				}
			}
	}
}

void check_status (Player * player, Ghost * ghost, Game_status * status) {
	if (player->row == ghost->row && player->col == ghost->col) {
		*status = over;
	}
	else if (player->food == player->total_food) {
		*status = win;
	}
}


