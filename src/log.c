/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:56:52 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/22 15:00:39 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "input.h"
#include "log.h"

static FILE *log = NULL;
static char *log_file = DEFAULT_LOG;

void
log_play(char player, int quadrant, int subquadrant) {
	if (!log)
		return;
	if (subquadrant == -1)
		fprintf(log, "%c:%d\n", player, quadrant);
	else
		fprintf(log, "%c:%d-%d\n", player, quadrant, subquadrant);
	fflush(log);
}

void
set_log(char *file) {
	log_file = file;
}

void
open_log(void) {
	if (log_file)
		log = fopen(log_file, "wb");
}

void
close_log(void) {
	if (log)
		fclose(log);
}

void
setLogReplayFile(char *file) {
	if (!file)
		setReplayFile(DEFAULT_LOG);
	else
		setReplayFile(file);
}
