/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 04:45:06 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 16:08:16 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INPUT_H)
#define INPUT_H

#include "board.h"

#define INPUT_PLAY 1
#define INPUT_OPP 2
#define INPUT_START 3

typedef int (*getInputFunc)(char player, int i, int quad, board_t *game);

int playerInput(char player, int i, int quad, board_t *game);
int firstInput(char player, int i, int quad, board_t *game);
int nextInput(char player, int i, int quad, board_t *game);
int replayInput(char player, int i, int quad, board_t *game);
int randomInput(char player, int i, int quad, board_t *game);

int getInput(char player, int i, int quad, board_t *game);

void setInoutFunction1 (getInputFunc f);
void setInoutFunction2 (getInputFunc f);
void setReplayFile (char *file);
void setDelay(int d);

#endif // INPUT_H
