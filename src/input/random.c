/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:24:28 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/21 16:43:02 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "board.h"
#include "input.h"

int
randomInput(char player, int i, int quad, board_t *game) {
	int choice;
	int count = 0;

	(void) player;
	(void) i;
	(void) quad;
	(void) game;
	if (i == INPUT_START)
		return rand() % 9;
	if (i == INPUT_PLAY) {
		for (int j = 0; j < 9; j++)
			if (game->board[quad][j] == EMPTY)
				count++;
		choice = rand() % count;
		for (int j = 0; j < 9; j++) {
			if (choice && game->board[quad][j] == EMPTY)
				choice--;
			else if (!choice && game->board[quad][j] == EMPTY) {
				choice = j;
				break;
			}
		}
	} else {
		for (int j = 0; j < 9; j++)
			if (game->global[j] == EMPTY)
				count++;
		choice = rand() % count;
		for (int j = 0; j < 9; j++) {
			if (choice && game->global[j] == EMPTY)
				choice--;
			else if (!choice && game->global[j] == EMPTY) {
				choice = j;
				break;
			}
		}
	}
	usleep(delay_g * 1000);
	return choice;
}
