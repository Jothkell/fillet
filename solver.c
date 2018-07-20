/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 10:16:57 by jkellehe          #+#    #+#             */
/*   Updated: 2018/07/20 14:41:04 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		all_placed(piece *p)
{
	while (p->id >= 'A' && p->id <= 'Z')
	{
		if (!(p->placed))
			return (0);
		p++;
	}
	return (1);
}

int		is_piece(piece is) //return 1 if it is a piece 0 if not
{
	if (is.id >= 'A' && is.id <= 'Z')
		return (1);
	else
		return (0);
}

void	toggle(boards *board, piece *p, int i)//toggle the piece in board and toggle is->placed. 
{
	board->row[p[i].y] ^= p[i].value[0];
    board->row[p[i].y + 1] ^= p[i].value[1];
	board->row[p[i].y + 2] ^= p[i].value[2];
    board->row[p[i].y + 2] ^= p[i].value[3];
	if (p[i].placed == 0)
		p[i].placed = 1;
	else
		p[i].placed = 0;
}

int checky(piece is, boards *board, uint8_t shift)//right shift by shift, if piece fits, return 1, else, shift back and return 0
{
	is.value[0] >>= shift;
	is.value[1] >>= shift;
	is.value[2] >>= shift;
	is.value[3] >>= shift;
	if (!(board->row[is.y] & is.value[0]) && !(board->row[is.y + 1] & is.value[1])
		&& !(board->row[is.y + 2] & is.value[2]) && !(board->row[is.y + 3] & is.value[3]))
		return (1);
    is.value[0] <<= shift;
    is.value[1] <<= shift;
    is.value[2] <<= shift;
    is.value[3] <<= shift;
	return (0);
}

int checker(piece is, boards *board)//set p.x an p.y to the first open place, if none reset and return 0
{
	is.y = is.ylast;
	is.x = is.xlast;

	while ((is.y + is.height) <= board->size)
	{
		is.x = is.xlast;
		while ((is.x + is.width) <= board->size)
		{
			if (checky(is, board, is.x))
			{
				is.ylast = is.y;
				is.xlast = is.x;
				return (1);//if you return 1, value is left shifted, and p.x and p.y are left
			}
			is.x++;
		}
		is.y++;
	}
	is.y = 0;
	is.x = 0;
	return (0);
}

int		recursion(piece *p, boards *board)
{
    if (all_placed(p))
        return (1);

}

int		solver (piece *p, boards *board)
{
    if (all_placed(p))
        return (1);
	while (board->size < 52)
	{
		board->i = 0;
		while(is_piece(p[board->i]))
		{
			while(!(p[board->i].placed) && checker(p[board->i], board))//make this a while, with a way of discounting positions already tried.   add a var to p to do this
			{
				p[board->i].i = board->i;
				toggle(board, p, board->i);
				if (solver(p, board))
					return (1);
				board->i = p[board->i].i;
				toggle(board, p, board->i);
			}
			board->i++;
		}
		board->size++;
	}
	return (0);
}
