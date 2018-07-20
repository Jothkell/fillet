/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:38:23 by jkellehe          #+#    #+#             */
/*   Updated: 2018/07/19 21:38:52 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

int		get_top(uint64_t *value) //return the highest value digit in input, 1 or 0
{
	//uint8_t hold;
	int i;
	int j;
	uint64_t holder;

	j = 0;
	i = 0;
	while (i < 4)
	{
		holder = value[i];
		j = 0;
		while (j < 51 && holder)
		{
			holder /= 2;
			j++;
		}
		if (holder == 1)
			return (0);
		i++;
	}
	return (1);
}

void	switch_em(uint64_t *value)
{
	value[0] = value[1];
	value[1] = value[2];
	value[2] = value[3];
	value[3] = 0;
}

//if value[0] is 0, replace with value[1], and so forth, and make value[3] = 0;
void		slider(uint64_t *value)//if leftmost column is 0s, leftshift until not, if first 
{

	while (get_top(value))
	{
		value[0] <<= 1;
		value[1] <<= 1;
		value[2] <<= 1;
		value[3] <<= 1;
	}
	while (value[0] == 0)
		switch_em(value);
}

int		bitter(char *buf, piece *p)//place the pieces into the 4 x 64bit array pointed by p->value
{
	int		j;
    uint64_t value;
	int		girth;
	int     maxgirth;

	maxgirth = 0;
	girth = 0;
	p->i = 1;
	value = 0;
	j = 0;
	while (p->i <= 20)
	{
        if (*buf == '#' || *buf == '.')
            value <<= 1;
		if (*buf == '#')
		{
			girth++;
			value += 1;
		}
		if (!(p->i % 5) && *buf == '\n')
		{
			maxgirth = (girth > maxgirth) ? (girth) : (maxgirth);
			girth = 0;
			value <<= 48;
			p->value[j++] = value;
			value = 0;
		}
		p->i++;
		buf++;
	}
	p->width = maxgirth;
	slider(p->value);
	return (0);
}

int		check_valid(char *buf)//check for 4 pieces, and for the appropriate newlines within the string buf.
{
	int		i;
	int		count;

	count = 0;
	i = 1;
	while (i <= 20)
	{
		if (!(i % 20) && (*buf != '\n' || (buf[1] != '\n' && buf[1])))
			return (0);
		if (((i % 5) && (*buf != '#' && *buf != '.')) || (!(i % 5) && (*buf != '\n')))
			return (0);
		count += ((*buf == '#') ? 1 : 0);
		buf++;
		i++;
	}
	if (count != 4)
		return (0);
	return (1);
}

void	printbits(uint64_t this)
{
	int hold;

	hold = 0;
	if (this)
	{
		hold = (int)(this % 2);
		this /= 2;
		printbits(this);
		printf("%d", hold);
	}
}

void	print_res(piece *p) //based on printbits
{
	int i;
    int hold;
	char c;
	uint64_t this;

	c = 0;
	i = 0;
    hold = 0;
	while (i < 4)
	{
		this = (uint64_t)p[i].value;
		if (p->id >= 'A' && p->id <= 'Z')
		{
			hold = ((int)p->value % 2);
			this /= 2;
			print_res(p);
			if (hold == 1)
				write(1, &p->id, 1);
			else
				write(1, "\n", 1);
		}
		p++;
		i++;
	}
}

int		reader(int fd, piece *p) //return 1 or 0 for success or fail
{
	int bytes;
	char buf[22];
	char letter;
	uint64_t value;
	int		i;

	i = 0;
	letter = 'A';
	while ((bytes = read(fd, buf, 21)))
	{
		if (!(check_valid(buf)))
			return (0);
		bitter(buf, p);
		p->id = letter++;
		i = 0;
		while (i < 4)
		{
			printbits(p->value[i++]);
			printf("\n");
		}
		printf("\n");
		p += 1;
		i++;
	}
	return (1);
}

char get_final(piece *p) //get the final piece, return its id
{
	int i;
	int j;
	int height;

	height = 0;
	j = 0;
	i = 0;
	while (is_piece(p[i]))
	{
		j = 0;
		height = 0;
		while (j++ < 4)
			if (p[i].value[j] > 0)
				height++;
		p[i].height = height;
		i++;
	}
	i--;
	return (p[i].id);
}

void zero_it(boards *board, piece *p)
{
	int i;

	i = 0;
	while (i < 28)
	{
		p[i].id = 0;
		p[i].placed = 0;
		i++;
	}
	board[0].final = (char)malloc(sizeof(char));
	i = 0;
	while (i < 52)
	{
		board[0].row[i] = 0;
		i++;
	}
}

int main(int argc, char ** argv)
{
	int file;
	piece p[27];
	boards *board;

	board = (boards*)malloc(sizeof(boards*));
	zero_it(board, p);//initialize everything to 0
	if(!reader((file = open(argv[1], O_RDONLY)), p))
		return (1);
	board->final = get_final(p);
	board->size = 2;
	if (solver(p, board))
		print_res(p);
	else
		write (1, "sorry, no answer\n", 17);
	return (0);
}
