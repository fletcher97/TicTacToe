/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:58:03 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/22 14:58:55 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LOG_H)
#define LOG_H

#define DEFAULT_LOG "/tmp/TicTacToe.log"

void log_play(char player, int quadrant, int subquadrant);
void set_log(char *file);
void open_log(void);
void close_log(void);
void setLogReplayFile(char *file);

#endif // LOG_H
