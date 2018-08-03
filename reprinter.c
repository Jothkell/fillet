/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprinter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 00:18:25 by jkellehe          #+#    #+#             */
/*   Updated: 2018/08/03 16:34:02 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

void	periods(char **res)
{
	int j;
	int i;

    j = 0;
    i = 0;
    while (i < 52)
    {
        res[i] = (char*)malloc(sizeof(char) * 53);
        j = 0;
        while (j < 52)
        {
            res[i][j] = '.';
            j++;
        }
        res[i][j] = '\0';
        i++;
    }
}

void	printer(piece *p, boards *board)
{
	char **res;
	int i;
	int j;
	int k;
	uint64_t hold;

	hold = 0;
	k = 0;
	j = 0;
	i = 0;
    res = (char**)malloc(sizeof(char*) * 53);
	periods(res);
	while (is_piece(p[i]))
	{
		j = 0;
		while (j < 4)
		{
			hold = p[i].value[j];
			k = 40;
			while (hold)
			{
                if (hold % 2 == 1)
				{
                    res[25 + j + p[i].ylast][k]= p[i].id;
				}
				else if (hold % 2 == 0 && res[25 + j + p[i].ylast][k] == '.')
					res[25 + j + p[i].ylast][k] = ' ';
				hold /= 2;
				k--;
			}
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	print_res(res);
}

void print_res(char **res)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = 0;
	j = 0;
	while (i < 52)
	{
		j = 0;
		flag = 0;
		while (j < 52)
		{
			if (res[i][j] >= 'A' && res[i][j] <= 'Z' && (flag = 1))
				printf("%c", res[i][j]);//write(1, &res[i][j], 1);
			else if (res[i][j] == ' ')
				printf(" ");
			j++;
		}
		flag ? (printf("\n")) : (1);
		i++;
	}
}
