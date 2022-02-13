/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:13:31 by fletcher          #+#    #+#             */
/*   Updated: 2022/02/13 18:49:49 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

# define O 'O'
# define X 'X'
# define D 'D'
# define EMPTY ' '

# define NEXT(x) x = (x == O ? X : O)

typedef struct board_s {
	char board[9][9];
	char global[9];
	char winner;
} board_t;

#endif // BOARD_H
