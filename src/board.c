/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 01:34:12 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 03:42:53 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "board.h"

board_t*
create() {
	board_t *game;

	game = calloc(1, sizeof(board_t));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			game->board[i][j] = EMPTY;
		}
		game->global[i] = EMPTY;
	}
	game->winner = EMPTY;
	game->next_quad = -1;
	return (game);
}

void
destroy(board_t *game) {
	free(game);
}

void
checkGlobal(board_t *board, int quad, char player) {
	if (board->global[quad] != player)
		return ;
	// Vert check
	if (board->global[quad % 3] == board->global[quad % 3 + 3] && board->global[quad % 3 + 3] == board->global[quad % 3 + 6])
		board->winner = player;
	// Horz check
	else if (board->global[quad - quad % 3] == board->global[quad - quad % 3 + 1] && board->global[quad - quad % 3 + 1] == board->global[quad - quad % 3 + 2])
		board->winner = player;
	// Diag checks
	else if ((quad == 0 || quad == 4 || quad == 8) && board->global[0] == board->global[4] && board->global[4] == board->global[8])
		board->winner = player;
	else if ((quad == 2 || quad == 4 || quad == 6) && board->global[2] == board->global[4] && board->global[4] == board->global[6])
		board->winner = player;
	// Draw check
	else if (board->global[0] != EMPTY && board->global[1] != EMPTY && board->global[2] != EMPTY
		&& board->global[3] != EMPTY && board->global[4] != EMPTY && board->global[5] != EMPTY
		&& board->global[6] != EMPTY && board->global[7] != EMPTY && board->global[8] != EMPTY)
		board->winner = D;
}


void
updateGlobal(board_t *board, int quadrant, int subQuadrant, int player) {
	if (board->board[quadrant][subQuadrant] != player)
		return ;
	// Vert check
	if (board->board[quadrant][subQuadrant % 3] == board->board[quadrant][subQuadrant % 3 + 3] && board->board[quadrant][subQuadrant % 3 + 3] == board->board[quadrant][subQuadrant % 3 + 6]) {
		board->global[quadrant] = player;
		checkGlobal(board, quadrant, player);
	}
	// Horz check
	else if (board->board[quadrant][subQuadrant - subQuadrant % 3] == board->board[quadrant][subQuadrant - subQuadrant % 3 + 1]
		&& board->board[quadrant][subQuadrant - subQuadrant % 3] == board->board[quadrant][subQuadrant - subQuadrant % 3 + 2]) {
		board->global[quadrant] = player;
		checkGlobal(board, quadrant, player);
	}
	// Diag checks
	else if ((subQuadrant == 0 || subQuadrant == 4 || subQuadrant == 8) && board->board[quadrant][0] == board->board[quadrant][4] && board->board[quadrant][4] == board->board[quadrant][8]) {
		board->global[quadrant] = player;
		checkGlobal(board, quadrant, player);
	}
	else if ((subQuadrant == 2 || subQuadrant == 4 || subQuadrant == 6) && board->board[quadrant][2] == board->board[quadrant][4] && board->board[quadrant][4] == board->board[quadrant][6]) {
		board->global[quadrant] = player;
		checkGlobal(board, quadrant, player);
	}
	// Draw check
	else if (board->board[quadrant][0] != EMPTY && board->board[quadrant][1] != EMPTY && board->board[quadrant][2] != EMPTY
		&& board->board[quadrant][3] != EMPTY && board->board[quadrant][4] != EMPTY && board->board[quadrant][5] != EMPTY
		&& board->board[quadrant][6] != EMPTY && board->board[quadrant][7] != EMPTY && board->board[quadrant][8] != EMPTY)
		board->global[quadrant] = D;
}
