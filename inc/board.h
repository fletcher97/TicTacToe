/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:13:31 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 03:34:43 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

# define O 'O'
# define X 'X'
# define D 'D'
# define EMPTY ' '
# define FIRST O

# define NEXT(x) x = (x == O ? X : O)

typedef struct board_s {
	char prev_move;
	char last_move;
	char next_quad;
	char board[9][9];
	char global[9];
	char winner;
} board_t;

board_t* create(void);
void updateGlobal(board_t *board, int quadrant, int subQuadrant, int player);
void destroy(board_t *game);


#endif // BOARD_H
