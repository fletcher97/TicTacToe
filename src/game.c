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

int
main() {
	board_t *game = create();
	int quad = -1, sub = -1;
	char player = FIRST;
	setInoutFunction1(&playerInput);
	setInoutFunction2(&playerInput);

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
