/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:11:49 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/21 16:12:59 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "board.h"
#include "input.h"

int
playerInput(char player, int i, int quad, board_t *game) {
	int d;

	(void) game;
	if (i == INPUT_PLAY)
		printf("Player \'%c\', you are on %d. Enter an index for your play (1-9):", player, quad + 1);
	else if (i == INPUT_OPP)
		printf("Player \'%c\', enter an index for your opponnent (1-9):", player);
	else if (i == INPUT_START)
		printf("Player \'%c\', enter a quadrant to start the game in (1-9):", player);
	int ret = scanf("%d", &d);
	if (ret == EOF) {
		printf("Game closed.\n");
		return -2;
	}
	while(getchar() != '\n');
	if (ret == 0 || d < 1 || d > 9)
		return (-1);
	return (d - 1);
}
