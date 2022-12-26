/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_show_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:10:25 by msilva-p          #+#    #+#             */
/*   Updated: 2022/11/13 18:45:37 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

int	ft_show_map(t_mlx *window)
{
	int	y;
	int	x;

	y = -1;
	while (window->map[++y] != NULL)
	{
		x = 0;
		while (x < window->col)
		{
			if (window->map[y][x] == '1')
				ft_put_image_to_window(window, window->wall, x, y);
			else if (window->map[y][x] == 'P')
				ft_put_image_to_window(window, window->player, x, y);
			else if (window->map[y][x] == 'C')
				ft_put_image_to_window(window, window->collec, x, y);
			else if (window->map[y][x] == 'E' && window->stars != 0)
				ft_put_image_to_window(window, window->exit_c, x, y);
			else if (window->map[y][x] == 'E' && window->stars == 0)
				ft_put_image_to_window(window, window->exit_o, x, y);
			else if (window->map[y][x] == '0')
				ft_put_image_to_window(window, window->floor, x, y);
			x++;
		}
	}
	return (ft_show_moves(window));
}

int	ft_show_moves(t_mlx *window)
{
	char	*movements;

	mlx_string_put(window->mlx_ptr, window->win_ptr, 12, 16, \
	0x0100ff00, "Moves: ");
	movements = ft_itoa(window->movements);
	mlx_string_put(window->mlx_ptr, window->win_ptr, 60, 16, \
	0x0100ff00, movements);
	free(movements);
	return (0);
}

int	ft_event(int key, t_mlx *window)
{
	if (key == XK_Escape)
	{
		ft_close(window);
	}
	if (key == XK_a || key == XK_A || key == XK_Left)
	{
		window->player = window->player_left;
		ft_event_arrow(window, -1, 0);
	}
	if (key == XK_d || key == XK_D || key == XK_Right)
	{
		window->player = window->player_right;
		ft_event_arrow(window, +1, 0);
	}
	if (key == XK_w || key == XK_W || key == XK_Up)
	{
		window->player = window->player_up;
		ft_event_arrow(window, 0, -1);
	}
	if (key == XK_s || key == XK_S || key == XK_Down)
	{
		window->player = window->player_down;
		ft_event_arrow(window, 0, +1);
	}
	return (0);
}

void	ft_event_arrow(t_mlx *window, int col, int line)
{
	ft_locate_player(window);
	if (window->map[window->player_line + line][window->player_col + col] == 48)
	{
		window->map[window->player_line + line][window->player_col + col] = 80;
		window->map[window->player_line][window->player_col] = 48;
		window->movements ++;
	}
	if (window->map[window->player_line + line][window->player_col + col] == 67)
	{
		window->map[window->player_line + line][window->player_col + col] = 80;
		window->map[window->player_line][window->player_col] = 48;
		window->stars --;
		window->movements ++;
	}
	if (window->map[window->player_line + line][window->player_col + col] == 69 \
		&& window->stars == 0)
	{
		window->map[window->player_line][window->player_col] = 48;
		window->movements ++;
		ft_print_error("\n***You are the champion!***\n\n");
		ft_close(window);
	}
}

void	ft_locate_player(t_mlx *window)
{
	int	x;
	int	y;

	y = 0;
	while (window->map[y] != NULL)
	{
		x = 0;
		while (window->map[y][x] != '\0')
		{
			if (window->map[y][x] == 'P')
			{
				window->player_line = y;
				window->player_col = x;
				return ;
			}
			x++;
		}
		y++;
	}
}
