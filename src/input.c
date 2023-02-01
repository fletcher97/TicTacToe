/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:47:01 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/21 16:42:39 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "input.h"

static getInputFunc getInputFunc1 = &playerInput;
static getInputFunc getInputFunc2 = &playerInput;

int delay_g = 200;

void
setDelay(int d) {
	delay_g = d;
}

void
setInputFunction1 (getInputFunc f) {
	getInputFunc1 = f;
}

void
setInputFunction2 (getInputFunc f) {
	getInputFunc2 = f;
}

bool
setInput(void (*f)(getInputFunc f), char *type) {
	if (!strcmp(type, "player"))
		f(&playerInput);
	else if (!strcmp(type, "first"))
		f(&firstInput);
	else if (!strcmp(type, "next"))
		f(&nextInput);
	else if (!strcmp(type, "replay"))
		f(&replayInput);
	else if (!strcmp(type, "random"))
		f(&randomInput);
	else
		return false;
	return true;
}

int
getInput(char player, int i, int quad, board_t *game) {
	if (player == FIRST)
		return (*getInputFunc1)(player, i, quad, game);
	return (*getInputFunc2)(player, i, quad, game);
}

int
askInput(char player, int type, int quad, board_t *game) {
	int ret;
	do
		drawBoard(game);
	while ((ret = getInput(player, type, quad, game)) == -1); // Asking input untill success
	return ret;
}
