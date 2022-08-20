/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:47:04 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 04:59:47 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "draw.h"

void
printCircle(int i, char *color) {
	if (i == 0 || i == 6)
		printf("%s       "RESET, color);
	else if (i == 1)
		printf("%s  ___  "RESET, color);
	else if (i == 2)
		printf("%s /   \\ "RESET, color);
	else if (i == 3 || i == 4)
		printf("%s |   | "RESET, color);
	else if (i == 5)
		printf("%s \\___/ "RESET, color);
}

void
printCross(int i, char *color) {
	if (i == 0 || i == 6)
		printf("%s       "RESET, color);
	else if (i == 1)
		printf("%s \\   / "RESET, color);
	else if (i == 2)
		printf("%s  \\ /  "RESET, color);
	else if (i == 3)
		printf("%s   X   "RESET, color);
	else if (i == 4)
		printf("%s  / \\  "RESET, color);
	else if (i == 5)
		printf("%s /   \\ "RESET, color);
}

void
printDraw(int i, char *color) {
	if (i == 2 || i == 3)
		printf("%s  ___  "RESET, color);
	else
		printf("%s       "RESET, color);
}

void
printBoard(int i, board_t *b, int quad) {
	char *last = ((quad == ((b->last_move&0xF0) >> 4) && b->winner == EMPTY ) ? GREEN : b->winner != EMPTY ? YELLOW : "");
	char *prev = ((quad == ((b->prev_move&0xF0) >> 4) && b->winner == EMPTY ) ? RED : b->winner != EMPTY ? YELLOW : "");
	char *curr = ((quad == b->next_quad || b->winner != EMPTY) ? YELLOW : "");
	char *end = ((b->winner != EMPTY) ? YELLOW : "");

	if (i == 0 || i == 6)
		printf("       ");
	else if (i == 1 || i == 3 || i == 5)
		printf(" %s%c"RESET"%s|"RESET"%s%c"RESET"%s|"RESET"%s%c"RESET" ",
			((((i-1)/2)*3) == (b->last_move&0xF)) ? last : ((((i-1)/2)*3) == (b->prev_move&0xF)) ? prev : end, b->board[quad][((i-1)/2)*3],
			curr,
			((((i-1)/2)*3+1) == (b->last_move&0xF)) ? last : ((((i-1)/2)*3+1) == (b->prev_move&0xF)) ? prev : end, b->board[quad][((i-1)/2)*3+1],
			curr,
			((((i-1)/2)*3+2) == (b->last_move&0xF)) ? last : ((((i-1)/2)*3+2) == (b->prev_move&0xF)) ? prev : end, b->board[quad][((i-1)/2)*3+2]);
	else if (i == 2 || i == 4)
		printf("%s -+-+- "RESET, curr);
}


void
drawBoard(board_t *board) {
	system("clear");
	char *global_selection = ((board->next_quad == -1 || (board->next_quad >= 0 && board->next_quad <= 8 && board->global[(int)board->next_quad] != EMPTY) || board->winner != EMPTY) ? YELLOW : "");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			for (int k = 0; k < 3; k++) {
				char * color = (((i*3+k) == ((board->last_move&0xF0) >> 4) && board->winner == EMPTY) ? GREEN : (((i*3+k) == ((board->prev_move&0xF0) >> 4) && board->winner == EMPTY) ? RED : board->winner != EMPTY ? YELLOW : ""));
				if (board->global[i * 3 + k] == EMPTY)
					printBoard(j, board, i * 3 + k);
				else if (board->global[i * 3 + k] == O)
					printCircle(j, color);
				else if (board->global[i * 3 + k] == X)
					printCross(j, color);
				else
					printDraw(j, color);
				if (k < 2)
					printf("%s||"RESET, global_selection);
			}
			printf("\n");
		}
		if (i < 2) {
			printf("%s-------++-------++-------"RESET"\n", global_selection);
			printf("%s-------++-------++-------"RESET"\n", global_selection);
		}
	}
}
