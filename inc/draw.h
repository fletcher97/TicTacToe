/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <fletcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:47:23 by fletcher          #+#    #+#             */
/*   Updated: 2022/08/20 02:47:26 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(DRAW_H)
#define DRAW_H

#include "board.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

void drawBoard(board_t *board);

#endif // DRAW_H
