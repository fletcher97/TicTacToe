/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:12:07 by fletcher          #+#    #+#             */
/*   Updated: 2022/09/23 16:49:11 by fletcher         ###   ########.fr       */
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

void
printHelp(void) {
	printf(
"-h/--help: print help message\n\
\n\
-p1 <input_methos>/-p2 <input_methos>: Change the input method for\n\
  player 1/2.\n\
  -> player: Default input method that asks the user for the cell index.\n\
  -> first: Loads input method that chooses always the first possible cell to\n\
    play on.\n\
  -> next: Loads input method that chooses always the cell who's index is one\n\
    higher than it's last invocation.\n\
  -> random: Loads input method that chooses a random cell.\n\
  -> replay: Loads input method that reads from a log file and chooses the\n\
    next valid play for the given player.\n\
\n\
-log <path>: Specify the path for the log file. Default log file is\n\
  located at /tmp/TicTacToe.log.\n\
\n\
-no-log: Disable logging.\n\
\n\
-replay-file <path>: Specify the path for the replay file. Default replay\n\
  file is set to the same as the default log file.\n\
\n\
-delay <milisecond>: Specify how long a \"bot\" takes to play. Defaults to\n\
  200 ms.\n\
\n\
-seed <number>: Specify seed to use for random input method. Defaults to a\n\
  random seed based on current time.\n\
\n\
WARNING: If the same flag is given twice or conflicting flags are specified\n\
the last one will prevail and overwrite previous flags.\n\
");
}

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
parse_args(int ac, char *av[]) {
	setLogReplayFile(NULL);
	srand(time(NULL));
	for (int i = 1; i < ac; i++) {
		if (!strcmp(av[i], "-h") || !strcmp(av[i], "--help")) {
			return false;
		} else if (!strcmp(av[i], "-p1") && i+1 < ac) {
			if (!setInput(&setInputFunction1, &(av[++i])))
				return false;
			if (strcmp(av[i], "load"))
				i++;
		} else if (!strcmp(av[i], "-p2") && i+1 < ac) {
			if (!setInput(&setInputFunction2, &(av[++i])))
				return false;
			if (strcmp(av[i], "load"))
				i++;
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
			printf("Error: wrong/unrecognizable parameter '%s'\n", av[i]);
			return false;
		}
	}
	return true;
}

int
main(int ac, char *av[]) {
	if (!parse_args(ac, av)) {
		printHelp();
		return -1;
	}
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
