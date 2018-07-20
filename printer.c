/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:32:00 by jkellehe          #+#    #+#             */
/*   Updated: 2018/07/20 11:38:09 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    print_res(uint64_t this, uint8_t y, char c, char **res) //based on printbits
{//in this imp will only print one piece at a time, x shifted but not y, so this is not a final product
    uint8_t hold;
    char *revhold;
    uint8_t xhold;
    uint8_t yhold;

    hold = 0;
    revhold = (char*)malloc(sizeof(char) * 52);
    *revhold++ = 46;
    while (this)
    {
        *revhold = (this % 2) + 48;
        this /= 2;
        revhold++;
    }
    hold = 0;
    while (*revhold != 46)
    {
        res[y][hold] = *revhold;
        revhold--;
        hold++;
    }
    res[y][hold] = '\0';
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

void    mallice(boards *board, char **res)
{
    uint8_t strnum;
    uint8_t i;

    i = 0;
    strnum = (board->final) - 64;
    while (i < strnum)
    {
        res[i] = (char*)malloc(sizeof(char) * 52);
    }
}


char **make_res(piece *p, boards *board)
{
    char **res;
    board->i = 0;
    uint8_t j;

    j = 0;
    res = (char**)malloc(sizeof(char*) * 52);
 
	int     ft_countwords(char **str)   //mallice(board, res);
    while(p->id >= 'A' && p->id <= 'Z')//through each piece
    {
        j = 0;
        while(p[board->i].i < 4)//through all 4 values for each piece
        {
            print_res(p[board->i].value[j], (p[board->i].y + j), p[board->i].id, res);//send the values one at a time
            j++;
        }
        board->i++;
    }
    return (res);
}

int     ft_countwords(char **str)
{
    int     i;

    i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return (i);
}

void    ft_putstr(char const *s)
{
    if (!s)
        return ;
    while (*s != '\0')
    {
        write(1, s, 1);
        s++;
    }
}

void        ft_putarr(char **str)
{
    int i;
    int wordct;

    wordct = ft_countwords(str);
    i = 0;
    while (i < wordct)
    {
        ft_putstr(str[i]);
        write(1, "\n", 1);
        i++;
    }
}
