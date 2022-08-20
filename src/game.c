/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:12:07 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 04:33:40 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "draw.h"
#include "input.h"

static FILE *log;
static char *log_file = "/tmp/TicTacToe.log";

bool
play(board_t *board, int quadrant, int subQuadrant, char player) {
	if (board->board[quadrant][subQuadrant] != EMPTY) {
		return false;
	}
	fprintf(log, "%c:%d-%d\n", player, quadrant, subQuadrant);
	fflush(log);
	board->board[quadrant][subQuadrant] = player;
	updateGlobal(board, quadrant, subQuadrant, player);
	board->prev_move = board->last_move;
	board->last_move = (quadrant << 4) | subQuadrant;
	board->next_quad = subQuadrant;
	return true;
}

bool
setInput(void (*f)(getInputFunc f), char *type) {
	if (!strcmp(type, "player"))
		f(&playerInput);
	else if (!strcmp(type, "first"))
		f(&firstInput);
	else if (!strcmp(type, "next"))
		f(&nextInput);
	else
		return false;
	return true;
}

bool
parse_args(int ac, char *av[]) {
	for (int i = 1; i < ac; i++) {
		if (!strcmp(av[i], "-p1") && i+1 < ac) {
			if (!setInput(&setInoutFunction1, av[++i]))
				return false;
		} else if (!strcmp(av[i], "-p2") && i+1 < ac) {
			if (!setInput(&setInoutFunction2, av[++i]))
				return false;
		} else if (!strcmp(av[i], "-log") && i+1 < ac) {
			log_file = av[++i];
		} else
			return false;
	}
	return true;
}

char *
askInput(char player, int type, int quad, board_t *game) {
	char *ret;
	do
		drawBoard(game);
	while ((ret = getInput(player, type, quad, game)) == -1); // Asking input untill success
	return ret;
}

int
main(int ac, char *av[]) {
	if (!parse_args(ac, av))
		return -1;
	log = fopen(log_file, "w");
	board_t *game = create();
	int quad = -1, sub = -1;
	char player = FIRST;

	sub = askInput(player, 3, -1, game);
	while (game->winner == EMPTY) {
		game->next_quad = sub;
		quad = sub;
		do {
			sub = askInput(player, 1, quad, game);
			if (sub == -2) {
				fclose(log);
				destroy(game);
				exit(-1);
			}
		} while (!play(game, quad, sub, player)); // Play untill success
		if (game->winner != EMPTY)
			break ;
		if (game->global[sub] != EMPTY) {
			while (game->global[sub] != EMPTY){
				sub = askInput(player, 2, quad, game);
			}
			fprintf(log, "%c:%d\n", player, sub);
			fflush(log);
		}
		NEXT(player);
	}
	if (game->winner == D)
		printf("You ended in a draw.\n");
	else
		printf("Congratulations to \'%c\' on winning.\n", game->winner);
	destroy(game);
	fclose(log);
}
