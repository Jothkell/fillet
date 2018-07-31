/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resemi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:39:09 by jkellehe          #+#    #+#             */
/*   Updated: 2018/07/30 15:05:12 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

void zero_it(boards *board, piece *p)
{
    int i;

    i = 0;
    while (i < 28)
    {
        p[i].id = 0;
        p[i].placed = 0;
        p[i].firstcheck = 1;
        p[i].xlast = 0;
        p[i].ylast = 0;
        p[i].width = 0;
        p[i].height = 0;
        i++;
    }
    board[0].final = (char)malloc(sizeof(char));
    i = 0;
    board[0].tlx = 0;
    board[0].tly = 0;
    board[0].xmax = 0;
    board[0].ymax = 0;
    board[0].current = 0;
    board[0].i = 0;
    while (i < 52)
    {
        board[0].row[i] = 0;
        i++;
    }
}

int main(int argc, char **argv)
{
    int file;
    piece p[27];
    boards *board;

    board = (boards*)malloc(sizeof(boards) * 2);
	zero_it(board, p);
	file = open(argv[1], O_RDONLY);
	printf("%d", file);
	//reader(file, p);
}
