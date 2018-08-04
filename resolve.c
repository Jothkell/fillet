/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 12:17:05 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/03 18:51:31 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int     all_placed(piece *p)
{
    while (p->id >= 'A' && p->id <= 'Z')
    {
        if (!(p->placed))
            return (0);
        p++;
    }
    return (1);
}

int touching(piece is, boards *board)//if a up down or left or right shift with & operator results in true, than retu\rn 1
{
	if (is.id == 'A')
		return (1);
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

int     is_piece(piece is) //return 1 if it is a piece 0 if not
{
    if (is.id >= 'A' && is.id <= 'Z')
        return (1);
    else
        return (0);
}

void    toggle(boards *board, piece *p)//toggle the piece in board and toggle is->placed.
{//add toggle firstcheck
    board->row[p[board->current].ylast] ^= p[board->current].value[0];
    board->row[p[board->current].ylast + 1] ^= p[board->current].value[1];
    board->row[p[board->current].ylast + 2] ^= p[board->current].value[2];
    board->row[p[board->current].ylast + 3] ^= p[board->current].value[3];
    if (p[board->current].placed == 0)
        p[board->current].placed = 1;
    else
        p[board->current].placed = 0;
	widtheight(p, board);
}

void widtheight(piece *p, boards *board)//amoung placed record lowest x value, highest x+width, subtract and return
{//assign this to boards, width and tlx respectively, and is.xlast
    p[board->current].i = 0;
	board->i = 0;
	board->tlx = 0;
	board->tly = 0;
	board->xmax = 0;
	board->ymax = 0;
    while (is_piece(p[board->i]))
    {
        if (p[board->i].placed)
        {
            board->tlx = (p[board->i].xlast < board->tlx) ? (p[board->i].xlast) : (board->tlx);
            board->xmax = ((p[board->i].xlast + p[board->i].width) > board->xmax) ? (p[board->i].xlast + p[board->i].width) : (board->xmax);
            board->tly = (p[board->i].ylast < board->tly) ? (p[board->i].ylast) : (board->tly);
            board->ymax = ((p[board->i].ylast + p[board->i].height) > board->ymax) ? (p[board->i].ylast + p[board->i].height) : (board->ymax);
        }
        board->i++;
    }
}

int leftof(piece is, boards *board)
{
	if (is.value[0] > board->row[is.ylast] || is.value[1] > board->row[is.ylast + 1] || is.value[2] > board->row[is.ylast + 2] || is.value[3] > board->row[is.ylast + 3])
		return (1);
	return (0);
}

int checky(piece *p, boards *board)
{//add a while loop within while but outside if, runs through possibly moving right.  
	while ((p[board->current].ylast + p[board->current].height - board->tly) <= (board->size))
	{
		if ((board->hold = touching(p[board->current], board)) && !(board->row[p[board->current].ylast] & p[board->current].value[0]) && !(board->row[p[board->current].ylast + 1] & p[board->current].value[1])
			&& !(board->row[p[board->current].ylast + 2] & p[board->current].value[2]) && !(board->row[p[board->current].ylast + 3] & p[board->current].value[3]))
			return (1);
		p[board->current].ylast++;
		board->count += board->hold;
	}
    return (board->count);
}

void  shifter(piece *p, boards *board, uint8_t lr)//lr 1 means right shift 1, 
{
	if (lr)
	{
		p[board->current].value[0] >>= 1;
		p[board->current].value[1] >>= 1;
		p[board->current].value[2] >>= 1;
		p[board->current].value[3] >>= 1;
	}
	else 
	{
		p[board->current].value[0] <<= 1;
		p[board->current].value[1] <<= 1;
		p[board->current].value[2] <<= 1;
		p[board->current].value[3] <<= 1;
	}
}

int checker(piece *p, boards *board)//restart at xlast/ylast.   reset them if firstcheck.  if false reset firstcheck true
{//start by setting xmax/ymax, tlx, tly,
	int flag = 1;
	int flag2 = 0;
    if ((board->xmax - board->tlx) > board->size || (board->ymax - board->tly) > board->size)
        return (0);
	if (all_placed(p))
		return (1);
	if ((p[board->current].width > board->size) || (p[board->current].height > board->size))
	{
		p[board->current].firstcheck = 1;		
		return (2);
	}
	widtheight(p, board);
    p[board->current].xlast = (p[board->current].id != 'A') ? 1 : 0; //p[board->current].xlast = 0;
	(p[board->current].id != 'A') ? (shifter(p, board, 1)) : (1);
    p[board->current].ylast= board->tly;
	/*while (p[board->current].id != 'A' && (touching(p[board->current], board) || leftof(p[board->current], board)) && ((p[board->current].xlast + p[board->current].width - board->tlx) <= board->size))
	{
		shifter(p, board, 1);
		p[board->current].xlast++;
	}
	(p[board->current].id != 'A') ? (shifter(p, board, 0)) : (1);
	p[board->current].xlast -= (p[board->current].id != 'A') ? (1) : (0);*/
	while (flag != 2 && ((p[board->current].xlast + p[board->current].width - board->tlx) <= board->size)) //check every piece on the right of board
	{
		p[board->current].ylast = board->tly;
		board->count = 2;
		while(1 == (flag = checky(p, board)))
		{
			toggle(board, p);
			board->current++;
			if ((flag2 = checker(p, board)) == 1)
				return (1);
            board->current--;
            toggle(board, p);
			if (flag2 == 2)//if piece was too big in any pos
			{
				p[board->current].firstcheck = 1;
				return (2);
			}
			p[board->current].ylast++;
		}
		shifter(p, board, 1);//shift right
	   p[board->current].xlast++;
	}
	flag = 1;
	shifter(p, board, 0);
	p[board->current].xlast--;
	widtheight(p, board);
	while (flag != 2 && (board->size >= (board->xmax  - p[board->current].xlast)))//check all pos moving left until beyond touching
	{
		p[board->current].ylast = board->tly;
		board->count = 2;
		while(1 == (flag = checky(p, board)))
		{
            toggle(board, p);
			board->current++;
            if ((flag2 = checker(p, board)) == 1)
                return (1);
			board->current--;
            toggle(board, p);
            if (flag2 == 2)
			{
                p[board->current].firstcheck = 1;
                return (2);
            }
			p[board->current].ylast++;
		}
		p[board->current].xlast--;
		shifter(p, board, 0);
	}
	while ((p[board->current].xlast) != 0)
	{
		if ((p[board->current].xlast) < 0)
		{
			p[board->current].xlast++;
			shifter(p, board, 1);
		}
		else
		{
			p[board->current].xlast--;
			shifter(p, board, 0);
		}
	}
	return (0);
}

int     solver(piece *p, boards *board)
{
	int sizehold;//i think this is unneccessary

	sizehold = 0;
	board->size = 3;
    while (board->size < 52)
    {
		zero_it(board, p);
        sizehold = board->size;
		widtheight(p, board);
        if(checker(p, board) == 1)
            return (1);
		board->size = sizehold;
        board->size++;
    }
    return (0);
}
