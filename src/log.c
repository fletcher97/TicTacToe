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

static FILE *log_file = NULL;
static char *log_file_name = DEFAULT_LOG;

void
log_play(char player, int quadrant, int subquadrant) {
	if (!log_file)
		return;
	if (subquadrant == -1)
		fprintf(log_file, "%c:%d\n", player, quadrant);
	else
		fprintf(log_file, "%c:%d-%d\n", player, quadrant, subquadrant);
	fflush(log_file);
}

void
set_log(char *file) {
	log_file_name = file;
}

void
open_log(void) {
	if (log_file_name)
		log_file = fopen(log_file_name, "wb");
}

void
close_log(void) {
	if (log_file)
		fclose(log_file);
}

void
setLogReplayFile(char *file) {
	if (!file)
		setReplayFile(DEFAULT_LOG);
	else
		setReplayFile(file);
}
