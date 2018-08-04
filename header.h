/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dknoll <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:02:15 by dknoll            #+#    #+#             */
/*   Updated: 2018/08/03 18:27:53 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_piece piece;
typedef struct  s_boards boards;// 

/*
typedef union {
	uint64_t low;
	uint64_t high;
} uint128_t;
*/

struct s_piece
{
	uint64_t value[4];
	uint8_t id;
	int xhold;
	int xlast;
	int ylast;
	uint8_t placed;
	uint8_t width;
	uint8_t height;
	uint8_t firstcheck;
	uint8_t i;
};

struct s_boards
{
	char final;
	uint8_t current;
	uint64_t row[52];
	int size;
	int i;
	int tlx;
	int tly;
	int xmax;
	int ymax;
	uint8_t count;
	uint8_t hold;
};

int solver (piece *p, boards *board);
int     all_placed(piece *p);
int     is_piece(piece is);
void    toggle(boards *board, piece *p); //int i);
int checky(piece *p, boards *board);
int checker(piece *p, boards *board);
void zero_it(boards *board, piece *p);
void widtheight(piece *p, boards *board);
void    printer(piece *p, boards *board);
void print_res(char **res, boards *board);

#endif
