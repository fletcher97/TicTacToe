/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:47:01 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 01:32:27 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "draw.h"

int
getInput(char player, int i, int quad, board_t *game) {
	int d;

	(void) game;
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
