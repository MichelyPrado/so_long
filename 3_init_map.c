/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_init_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:07:03 by msilva-p          #+#    #+#             */
/*   Updated: 2022/11/13 18:49:45 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

void	ft_put_image_to_window(t_mlx *window, void *image, int x, int y)
{
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, \
		image, PIXEL_SIZE * x, PIXEL_SIZE * y);
}

int	ft_create_map(t_mlx *window, char *path)
{
	int		y;
	int		fd;
	char	*temp;

	y = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_print_error(ERROR_2"\n");
	temp = get_next_line(fd);
	if (temp == NULL)
		return (1);
	window->map = malloc((window->line + 1) * sizeof(char *));
	if (window->map == NULL)
		return (1);
	while (y < window->line)
	{
		window->map[y] = temp;
		y++;
		temp = get_next_line(fd);
		if (y < window->line && temp == NULL)
			return (1);
	}
	close (fd);
	window->map[y] = NULL;
	return (0);
}

char	**ft_dup_map(t_mlx *window)
{
	char	**copy;
	int		y;

	copy = malloc((window->line + 1) * sizeof(char *));
	y = 0;
	while (window->map[y] != NULL)
	{
		copy[y] = ft_strdup(window->map[y]);
		if (copy[y] == NULL)
		{
			ft_free_matrix(copy);
			return (NULL);
		}
		copy[y][window->col] = '\0';
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

void	ft_free_matrix(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free (matrix[i]);
		i++;
	}
	free(matrix);
}

int	ft_read_map(t_mlx *window, char *path)
{
	int		fd;
	char	*temp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_print_error(ERROR_2"\n");
		return (1);
	}
	temp = get_next_line(fd);
	if (temp == NULL)
		ft_print_error(ERROR_11"\n");
	if (temp[0] != '1')
		ft_print_error(ERROR_3"\n");
	if (temp == NULL || temp[0] != '1')
		return (1);
	if (ft_count_lines(fd, temp, window) == 1)
		return (1);
	if (window->col < 5 || window->col > 37 || \
		window->line < 3 || window->line > 28)
	{
		ft_print_error(ERROR_3"\n");
		return (1);
	}
	return (0);
}
