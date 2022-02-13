/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:12:07 by fletcher          #+#    #+#             */
/*   Updated: 2022/02/13 19:59:12 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "board.h"

board_t *create() {
	board_t *game;

	game = calloc(1, sizeof(board_t));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			game->board[i][j] = EMPTY;
		}
		game->global[i] = EMPTY;
	}
	game->winner = EMPTY;
	return (game);
}

void destroy(board_t *game) {
	free(game);
}

void checkGlobal(board_t *board, int quad, char player) {
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


void updateGlobal(board_t *board, int quadrant, int subQuadrant, int player) {
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

bool play(board_t *board, int quadrant, int subQuadrant, char player) {
	if (board->board[quadrant][subQuadrant] != EMPTY)
		return false;
	board->board[quadrant][subQuadrant] = player;
	updateGlobal(board, quadrant, subQuadrant, player);
	return true;
}

void printCircle(int i) {
	if (i == 0 || i == 6)
		printf("       ");
	else if (i == 1)
		printf("  ___  ");
	else if (i == 2)
		printf(" /   \\ ");
	else if (i == 3 || i == 4)
		printf(" |   | ");
	else if (i == 5)
		printf(" \\___/ ");
	else if (i == 6)
		printf("       ");
}

void printCross(int i) {
	if (i == 0 || i == 6)
		printf("       ");
	else if (i == 1)
		printf(" \\   / ");
	else if (i == 2)
		printf("  \\ /  ");
	else if (i == 3)
		printf("   X   ");
	else if (i == 4)
		printf("  / \\  ");
	else if (i == 5)
		printf(" /   \\ ");
}

void printDraw(int i) {
	if (i == 2 || i == 3)
		printf("  ___  ");
	else
		printf("       ");
}

void printBoard(int i, board_t *b, int quad) {
	if (i == 0 || i == 6)
		printf("       ");
	else if (i == 1 || i == 3 || i == 5)
		printf(" %c|%c|%c ", b->board[quad][((i - 1) / 2) * 3], b->board[quad][((i-1)/2)*3+1], b->board[quad][((i-1)/2)*3+2]);
	else if (i == 2 || i == 4)
		printf(" -+-+- ");
}


void drawBoard(board_t *board) {
	system("clear");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			for (int k = 0; k < 3; k++) {
				if (board->global[i * 3 + k] == EMPTY)
					printBoard(j, board, i * 3 + k);
				else if (board->global[i * 3 + k] == O)
					printCircle(j);
				else if (board->global[i * 3 + k] == X)
					printCross(j);
				else
					printDraw(j);
				if (k < 2)
					printf("||");
			}
			printf("\n");
		}
		if (i < 2) {
			printf("-------++-------++-------\n");
			printf("-------++-------++-------\n");
		}
	}
}

int getInput(char player, int i, int quad, board_t *game) {
	int d;

	drawBoard(game);
	if (i == 1)
		printf("Player \'%c\', you are on %d. Enter an index for your play (1-9):", player, quad + 1);
	else if (i == 2)
		printf("Player \'%c\', enter an index for your opponnent (1-9):", player);
	else if (i == 3)
		printf("Player \'%c\', enter a quadrant to start the game in (1-9):", player);
	int ret = scanf("%d", &d);
	if (ret == EOF) {
		printf("Game closed.\n");
		exit(1);
	}
	while(getchar() != '\n');
	if (ret == 0 || d < 1 || d > 9)
		return (-1);
	return (d - 1);
}

int main() {
	board_t *game = create();
	int quad = -1, sub = -1;
	char player = O;

	while ((sub = getInput(player, 3, -1, game)) == -1) ; // Asking input untill success
	while (game->winner == EMPTY) {
		quad = sub;
		while ((sub = getInput(player, 1, quad, game)) == -1) ; // Asking input untill success
		while (!play(game, quad, sub, player)) // Play untill success
			while ((sub = getInput(player, 1, quad, game)) == -1) ; // Asking input untill success
		if (game->winner != EMPTY)
			break ;
		while (game->global[sub] != EMPTY)
			while ((sub = getInput(player, 2, quad, game)) == -1) ; // Asking input untill success
		NEXT(player);
	}
	drawBoard(game);
	if (game->winner == D)
		printf("You ended in a draw.\n");
	else
		printf("Congratulations to \'%c\' on winning.\n", game->winner);
	destroy(game);
}
