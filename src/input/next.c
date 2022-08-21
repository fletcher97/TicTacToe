/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:41:59 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/21 16:42:14 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "board.h"
#include "input.h"

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

	usleep(delay_g * 1000);
	return next;
}
