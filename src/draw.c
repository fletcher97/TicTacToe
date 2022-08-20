/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:47:04 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/19 21:51:54 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "board.h"

void
printCircle(int i) {
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
}

void
printCross(int i) {
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

void
printDraw(int i) {
	if (i == 2 || i == 3)
		printf("  ___  ");
	else
		printf("       ");
}

void
printBoard(int i, board_t *b, int quad) {
	if (i == 0 || i == 6)
		printf("       ");
	else if (i == 1 || i == 3 || i == 5)
		printf(" %c|%c|%c ", b->board[quad][((i - 1) / 2) * 3], b->board[quad][((i-1)/2)*3+1], b->board[quad][((i-1)/2)*3+2]);
	else if (i == 2 || i == 4)
		printf(" -+-+- ");
}


void
drawBoard(board_t *board) {
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
