/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replay.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:40:40 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/21 16:43:42 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "board.h"
#include "input.h"

static FILE *replay_file = NULL;

void
setReplayFile (char *file) {
	if (replay_file)
		fclose(replay_file);
	replay_file = fopen(file, "r");
}

int
replayInput(char player, int i, int quad, board_t *game) {
	char player_replay;
	int quad_replay;
	int sub_replay;
	char line[6];
	int success;

	(void) game;
	(void) quad;
	success = fscanf(replay_file, "%s\n", line);
	if (success == EOF) {
		if (player == FIRST)
			setInputFunction1(&playerInput);
		else
			setInputFunction2(&playerInput);
		return -1;
	}
	success = sscanf(line, "%c:%d-%d\n", &player_replay, &quad_replay, &sub_replay);
	if (i == INPUT_START && success == 3 && player == player_replay) {
		rewind(replay_file);
		return quad_replay;
	}
	if (i == INPUT_PLAY && success == 3 && player == player_replay) {
		usleep(delay_g * 1000);
		return sub_replay;
	}
	if (i == INPUT_OPP && success == 2 && player == player_replay) {
		usleep(delay_g * 1000);
		return quad_replay;
	}

	return -1;
}
