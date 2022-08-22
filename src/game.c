/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:12:07 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/22 15:00:01 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "board.h"
#include "draw.h"
#include "input.h"
#include "log.h"

bool
play(board_t *board, int quadrant, int subQuadrant, char player) {
	if (board->board[quadrant][subQuadrant] != EMPTY) {
		return false;
	}
	log_play(player, quadrant, subQuadrant);
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
	else if (!strcmp(type, "replay"))
		f(&replayInput);
	else if (!strcmp(type, "random"))
		f(&randomInput);
	else
		return false;
	return true;
}

bool
parse_args(int ac, char *av[]) {
	setLogReplayFile(NULL);
	srand(time(NULL));
	for (int i = 1; i < ac; i++) {
		if (!strcmp(av[i], "-p1") && i+1 < ac) {
			if (!setInput(&setInputFunction1, av[++i]))
				return false;
		} else if (!strcmp(av[i], "-p2") && i+1 < ac) {
			if (!setInput(&setInputFunction2, av[++i]))
				return false;
		} else if (!strcmp(av[i], "-log") && i+1 < ac) {
			set_log(av[++i]);
		} else if (!strcmp(av[i], "-no-log")) {
			set_log(NULL);
		} else if (!strcmp(av[i], "-replay-file") && i+1 < ac) {
			setLogReplayFile(av[++i]);
		} else if (!strcmp(av[i], "-delay") && i+1 < ac) {
			int d = (int)strtol(av[++i], NULL, 10);
			if (d >= 0)
				setDelay(d);
		} else if (!strcmp(av[i], "-seed") && i+1 < ac) {
			int d = (int)strtol(av[++i], NULL, 10);
			srand(d);
		} else {
			printf("Error: unrecognizable parameter '%s'\n", av[i]);
			return false;
		}
	}
	return true;
}

int
askInput(char player, int type, int quad, board_t *game) {
	int ret;
	do
		drawBoard(game);
	while ((ret = getInput(player, type, quad, game)) == -1); // Asking input untill success
	return ret;
}

int
main(int ac, char *av[]) {
	if (!parse_args(ac, av))
		return -1;
	open_log();
	board_t *game = create();
	int quad = -1, sub = -1;
	char player = FIRST;

	sub = askInput(player, INPUT_START, -1, game);
	while (game->winner == EMPTY) {
		game->next_quad = sub;
		quad = sub;
		do {
			sub = askInput(player, INPUT_PLAY, quad, game);
			if (sub == -2) {
				close_log();
				destroy(game);
				exit(-1);
			}
		} while (!play(game, quad, sub, player)); // Play untill success
		if (game->winner != EMPTY) {
			drawBoard(game);
			break ;
		}
		if (game->global[sub] != EMPTY) {
			while (game->global[sub] != EMPTY){
				sub = askInput(player, INPUT_OPP, quad, game);
			}
			log_play(player, sub, -1);
		}
		NEXT(player);
	}
	if (game->winner == D)
		printf("You ended in a draw.\n");
	else
		printf("Congratulations to \'%c\' on winning.\n", game->winner);
	destroy(game);
	close_log();
}
