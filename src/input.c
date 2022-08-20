/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:47:01 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 06:00:05 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "board.h"
#include "input.h"

static getInputFunc getInputFunc1 = &playerInput;
static getInputFunc getInputFunc2 = &playerInput;

void
setInoutFunction1 (getInputFunc f) {
	getInputFunc1 = f;
}

void
setInoutFunction2 (getInputFunc f) {
	getInputFunc2 = f;
}

int
firstInput(char player, int i, int quad, board_t *game) {
	(void) player;
	if (i == INPUT_PLAY) {
		for (int j = 0; j < 9; j++)
			if (game->board[quad][j] == EMPTY) {
				usleep(200 * 1000);
				return j;
			}
	} else if (i == INPUT_OPP) {
		for (int j = 0; j < 9; j++)
			if (game->global[j] == EMPTY)
				return j;
	} else if (i == INPUT_START)
		return 0;
	return -1;
}

int
nextInput(char player, int i, int quad, board_t *game) {
	(void) player;
	(void) i;
	(void) quad;
	(void) game;

	static int next = -1;
	next = (next + 1) % 9;

	if (i == INPUT_PLAY) {
		while (game->board[quad][next] != EMPTY) {
			next = (next + 1) % 9;
		}
	} else if (i == INPUT_OPP) {
		while (game->global[next] != EMPTY) {
			next = (next + 1) % 9;
		}
		return next;
	} else if (i == INPUT_START) {
		return next;
	}

	usleep(200 * 1000);
	return next;
}


int
playerInput(char player, int i, int quad, board_t *game) {
	int d;

	(void) game;
	if (i == INPUT_PLAY)
		printf("Player \'%c\', you are on %d. Enter an index for your play (1-9):", player, quad + 1);
	else if (i == INPUT_OPP)
		printf("Player \'%c\', enter an index for your opponnent (1-9):", player);
	else if (i == INPUT_START)
		printf("Player \'%c\', enter a quadrant to start the game in (1-9):", player);
	int ret = scanf("%d", &d);
	if (ret == EOF) {
		printf("Game closed.\n");
		return -2;
	}
	while(getchar() != '\n');
	if (ret == 0 || d < 1 || d > 9)
		return (-1);
	return (d - 1);
}

int
getInput(char player, int i, int quad, board_t *game) {
	if (player == FIRST)
		return (*getInputFunc1)(player, i, quad, game);
	return (*getInputFunc2)(player, i, quad, game);
}
