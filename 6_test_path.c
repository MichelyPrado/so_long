/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_test_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 03:42:00 by msilva-p          #+#    #+#             */
/*   Updated: 2022/11/13 18:58:19 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

int	ft_valid_walls(t_mlx *window)
{
	int	x;
	int	max;

	x = 0;
	max = window->col;
	if (window->col < window->line)
		max = window->line;
	while (x < max)
	{
		if (window->col - x > 0)
			if (window->map[0][x] != '1' || \
				window->map[window->line - 1][x] != '1')
				break ;
		if (window->line - x > 0)
			if (window->map[x][0] != '1' || \
				window->map[x][window->col - 1] != '1')
				break ;
		x++;
	}
	if (x != max)
	{
		ft_print_error(ERROR_4"\n");
		return (1);
	}
	return (0);
}

void	ft_test_path(char **copy, int line, int col, t_mlx *window)
{
	if (copy[line][col] == 'X' || copy[line][col] == '1' || \
	copy[line][col] == 'S')
		return ;
	if (copy[line][col] == 'E')
	{
		copy[line][col] = 'S';
		return ;
	}
	else
		copy[line][col] = 'X';
	ft_test_path(copy, line - 1, col, window);
	ft_test_path(copy, line + 1, col, window);
	ft_test_path(copy, line, col - 1, window);
	ft_test_path(copy, line, col + 1, window);
}

int	ft_count_lines(int fd, char *temp, t_mlx *window)
{
	int		count_line_break;

	count_line_break = 0;
	window->line = 0;
	window->col = ft_count_col (temp);
	while (temp != NULL)
	{
		if (temp[0] != '\n' && count_line_break == 0)
			window->line++;
		else if (temp[0] != '\n' && count_line_break != 0)
			return (ft_close_and_free(fd, temp));
		else if (temp[0] == '\n')
			count_line_break++;
		free(temp);
		temp = get_next_line(fd);
		if (temp && temp[0] != '\n' && window->col != ft_count_col(temp))
			return (ft_close_and_free(fd, temp));
	}
	close (fd);
	return (0);
}

int	ft_count_col(char *temp)
{
	int	i;

	i = 0;
	while (temp != NULL && temp[i] != 0 && temp[i] != '\n' && temp[i] != '\r')
		i++;
	return (i);
}

int	ft_close_and_free(int fd, char *temp)
{
	ft_print_error(ERROR_3"\n");
	free(temp);
	close(fd);
	return (1);
}
