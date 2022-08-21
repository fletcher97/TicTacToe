/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:39:34 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/21 16:40:04 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "board.h"
#include "input.h"

int
firstInput(char player, int i, int quad, board_t *game) {
	(void) player;
	if (i == INPUT_PLAY) {
		for (int j = 0; j < 9; j++)
			if (game->board[quad][j] == EMPTY) {
				usleep(delay_g * 1000);
				return j;
			}
	} else if (i == INPUT_OPP) {
		for (int j = 0; j < 9; j++)
			if (game->global[j] == EMPTY)
				return j;
	} else if (i == INPUT_START)
		return 0;
	return -1;
}
