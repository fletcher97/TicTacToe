/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:12:07 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 03:07:49 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "draw.h"
#include "input.h"

bool
play(board_t *board, int quadrant, int subQuadrant, char player) {
	if (board->board[quadrant][subQuadrant] != EMPTY) {
		drawBoard(board);
		return false;
	}
	board->board[quadrant][subQuadrant] = player;
	updateGlobal(board, quadrant, subQuadrant, player);
	board->prev_move = board->last_move;
	board->last_move = (quadrant << 4) | subQuadrant;
	drawBoard(board);
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
		} else
			return false;
	}
	return true;
}

int
main(int ac, char *av[]) {
	if (!parse_args(ac, av))
		return -1;
	board_t *game = create();
	int quad = -1, sub = -1;
	char player = FIRST;

	drawBoard(game);
	while ((sub = getInput(player, 3, -1, game)) == -1) ; // Asking input untill success
	while (game->winner == EMPTY) {
		quad = sub;
		do
			while ((sub = getInput(player, 1, quad, game)) == -1) ; // Asking input untill success
		while (!play(game, quad, sub, player)); // Play untill success
		if (game->winner != EMPTY)
			break ;
		while (game->global[sub] != EMPTY)
			while ((sub = getInput(player, 2, quad, game)) == -1) ; // Asking input untill success
		NEXT(player);
	}
	if (game->winner == D)
		printf("You ended in a draw.\n");
	else
		printf("Congratulations to \'%c\' on winning.\n", game->winner);
	destroy(game);
}
