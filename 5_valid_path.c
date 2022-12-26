/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_valid_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:14:46 by msilva-p          #+#    #+#             */
/*   Updated: 2022/11/13 18:50:30 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

int	ft_valid_character(t_mlx *window)
{
	int	y;
	int	x;
	int	p;
	int	e;
	int	invalid;

	p = 0;
	e = 0;
	invalid = 0;
	y = -1;
	while (window->map[++y] != NULL)
	{
		x = -1;
		while (++x < window->col)
		{
			if (window->map[y][x] == 'P')
				p++;
			else if (window->map[y][x] == 'E')
				e++;
			else if (window->map[y][x] != 'C' && window->map[y][x] != '0' \
				&& window->map[y][x] != '1')
				invalid++;
		}
	}
	return (ft_check_characters(window, e, p, invalid));
}

int	ft_check_characters(t_mlx *window, int e, int p, int invalid)
{
	if (ft_count_collectibles(window) == 1)
		ft_print_error(ERROR_9"\n");
	if (e != 1)
		ft_print_error(ERROR_8"\n");
	if (p != 1)
		ft_print_error(ERROR_7"\n");
	if (invalid > 0)
		ft_print_error(ERROR_10"\n");
	if (window->stars == 0 || e != 1 || p != 1 || invalid > 0)
		return (1);
	return (0);
}

int	ft_count_collectibles(t_mlx *window)
{
	int	x;
	int	y;

	window->stars = 0;
	y = 0;
	while (window->map[y] != NULL)
	{
		x = 0;
		while (window->map[y][x] != '\0')
		{
			if (window->map[y][x] == 'C')
			{
				window->stars = window->stars + 1;
			}
			x++;
		}
		y++;
	}
	if (window->stars == 0)
		return (1);
	else
		return (0);
}

int	ft_check_path(char **copy, t_mlx *window)
{
	int	line;
	int	col;
	int	exit;
	int	collec;

	line = 0;
	exit = 0;
	collec = 0;
	col = 0;
	while (copy[line] != NULL)
	{
		col = 0;
		while (col < window->col)
		{
			if (copy[line][col] == 'E' && exit == 0)
				exit = 1;
			if (copy[line][col] == 'C' && collec == 0)
				collec = 1;
			col++;
		}
		line++;
	}
	return (ft_check_exit(exit, collec));
}

int	ft_check_exit(int exit, int collec)
{
	if (exit != 0)
		ft_print_error(ERROR_5"\n");
	if (collec != 0)
		ft_print_error(ERROR_6"\n");
	if (exit != 0 || collec != 0)
		return (1);
	return (0);
}
