/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dknoll <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:02:15 by dknoll            #+#    #+#             */
/*   Updated: 2018/07/20 14:35:24 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_piece piece;
typedef struct  s_boards boards;

struct s_piece
{
	uint64_t value[4];
	//piece *last;//maybe replace this with pieces placed so far, a string. 
	uint8_t id;
	int x;
	int y;
	int xlast;
	int ylast;
	uint8_t width;
	uint8_t height;
	uint8_t placed;
	uint8_t i;
};

struct s_boards
{
	char final;
	uint64_t row[52];
	uint8_t size;
	uint8_t i;
};

int solver (piece *p, boards *board);
int     all_placed(piece *p);
int     is_piece(piece is);
void    toggle(boards *board, piece *p, int i);
int checky(piece is, boards *board, uint8_t shift);
int checker(piece is, boards *board);



#endif
