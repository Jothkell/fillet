/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 10:16:57 by jkellehe          #+#    #+#             */
/*   Updated: 2018/07/23 15:20:40 by jkellehe         ###   ########.fr       */
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
{//add toggle firstcheck
	board->row[p[i].ylast] ^= p[i].value[0];
    board->row[p[i].ylast + 1] ^= p[i].value[1];
	board->row[p[i].ylast + 2] ^= p[i].value[2];
    board->row[p[i].ylast + 2] ^= p[i].value[3];
	if (p[i].placed == 0)
		p[i].placed = 1;
	else
		p[i].placed = 0;
}

int touching(piece is, boards *board)//if a up down or left or right shift with & operator results in true, than return 1
{
	if ((board->row[is.ylast + 1] & is.value[0]) || (board->row[is.ylast + 2] & is.value[1])
        || (board->row[is.ylast + 3] & is.value[2]) || (board->row[is.ylast + 4] & is.value[3]))
		return (1);
    if ((board->row[is.ylast - 1] & is.value[0]) || (board->row[is.ylast] & is.value[1])
        || (board->row[is.ylast + 1] & is.value[2]) || (board->row[is.ylast + 2] & is.value[3]))
        return (1);
    if ((board->row[is.ylast] & (is.value[0] / 2)) || (board->row[is.ylast + 1] & (is.value[1] / 2))
        || (board->row[is.ylast + 2] & (is.value[2] / 2)) || (board->row[is.ylast + 3] & (is.value[3] / 2)))
        return (1);
    if ((board->row[is.ylast] & (is.value[0] * 2)) || (board->row[is.ylast + 1] & (is.value[1] * 2))
        || (board->row[is.ylast + 2] & (is.value[2] * 2)) || (board->row[is.ylast + 3] & (is.value[3] * 2)))
        return (1);
	return (0);
}

int checky(piece is, boards *board, uint8_t shift)//right shift by shift, if piece fits, return 1, else, shift back and return 0
{
	is.value[0] >>= shift;
	is.value[1] >>= shift;
	is.value[2] >>= shift;
	is.value[3] >>= shift;
	if (touching(is, board) && !(board->row[is.ylast] & is.value[0]) && !(board->row[is.ylast + 1] & is.value[1])
		&& !(board->row[is.ylast + 2] & is.value[2]) && !(board->row[is.ylast + 3] & is.value[3]))
		return (1);
    is.value[0] <<= shift;
    is.value[1] <<= shift;
    is.value[2] <<= shift;
    is.value[3] <<= shift;
	return (0);
}

void widtheight(piece is, piece *p, boards *board)//amoung placed record lowest x value, highest x+width, subtract and return 
{//assign this to boards, width and tlx respectively, and is.xlast
	is.i = 0;

	while (is_piece(p[is.i]))
	{
		if (p[is.i].placed)
		{
			board->tlx = (p[is.i].xlast < board->tlx) ? (p[is.i].xlast) : (board->tlx);
			board->xmax = ((p[is.i].xlast + p[is.i].width) > board->xmax) ? (p[is.i].xlast + p[is.i].width) : (board->xmax);
			board->tly = (p[is.i].ylast < board->tly) ? (p[is.i].ylast) : (board->tly);
			board->ymax = ((p[is.i].ylast + p[is.i].height) > board->ymax) ? (p[is.i].ylast + p[is.i].height) : (board->ymax);
		}
		is.i++;
	}
}//goal is to only run this 4 times for each checker, to figure out the start and stop x and y. 

int checker(piece is, boards *board, piece *p)//set p.x an p.y to the first open place, if none reset and return 0
{
	widtheight(is, p, board); //sets tlx, tly, ymax, and xmax
	if (is.firstcheck)//reset xlast and ylast
	{
		is.xlast = (board->tlx - is.width);
		is.ylast = (board->tly - is.height);
		is.firstcheck = 0;
	}
	is.xhold = is.xlast;
	while (is.ylast <= (board->ymax + 1))
	{
		is.xlast = is.xhold;
		while (is.xlast <= (board->xmax + 1))
		{
			if (checky(is, board, is.xlast))
			{
				return (1);//if you return 1, value is left shifted, and p.x and p.y are left
			}
			is.xlast++;
		}
		is.ylast++;
	}
	is.firstcheck = 1;
	return (0);
}

int     solvey(piece p, boards *board)
{
    if (!(p.id >= 'A' && p.id <= 'Z'))
        return (1);
    while(checker(p, board))
    {
        toggle(board, p);
        if (solvey((p + 1), board))
            return (1);
        toggle(board, p);
    }
    return (0);
}

int     solver(piece *p, boards *board)
{
    while (board->size < 52)
    {
        if(solvey(p, board))
            return (1);
        board->size++;
    }
    return (0);
}




/*
int		solvey(piece *p, boards *board)
{
    if (all_placed(p))
        return (1);
	board->i = 0;
	while(is_piece(p[board->i]))
	{
		while(!(p[board->i].placed) && checker(p[board->i], board, p))
		{
			p[board->i].i = board->i;
			toggle(board, p, board->i);
			if (solvey(p, board))
				return (1);
			board->i = p[board->i].i;
			toggle(board, p, board->i);
		}
		board->i++;
	}
	return (0);
}

int		solver(piece *p, boards *board)
{
	while (board->size < 52)
	{
		//board->i = 0;
		if(solvey(p, board))
			return (1);
		board->size++;
	}
	return (0);
}
ard->size++;
}
*/
