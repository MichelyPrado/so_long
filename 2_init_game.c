/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:01:02 by msilva-p          #+#    #+#             */
/*   Updated: 2022/11/13 19:04:42 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

int	ft_init_game(t_mlx *window)
{
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
	{
		ft_print_error(ERROR_12"\n");
		return (1);
	}
	window->win_ptr = mlx_new_window(window->mlx_ptr, window->col * \
		PIXEL_SIZE, window->line * PIXEL_SIZE, "So_long");
	if (window->win_ptr == NULL)
	{
		ft_print_error(ERROR_12"\n");
		return (1);
	}
	window->movements = 0;
	ft_put_sprites(window);
	window->player = window->player_down;
	mlx_hook(window->win_ptr, 2, (1L << 0), &ft_event, window);
	mlx_hook(window->win_ptr, 17, 0, &ft_close, window);
	mlx_loop_hook(window->mlx_ptr, &ft_show_map, window);
	mlx_loop(window->mlx_ptr);
	return (0);
}

void	ft_put_sprites(t_mlx *window)
{
	ft_sprites(window, &window->player_left, "sprites/player_left.xpm");
	ft_sprites(window, &window->player_right, "sprites/player_right.xpm");
	ft_sprites(window, &window->player_up, "sprites/player_up.xpm");
	ft_sprites(window, &window->player_down, "sprites/player_down.xpm");
	ft_sprites(window, &window->wall, "sprites/wall.xpm");
	ft_sprites(window, &window->collec, "sprites/Collectable.xpm");
	ft_sprites(window, &window->exit_c, "sprites/exit_close.xpm");
	ft_sprites(window, &window->exit_o, "sprites/exit_open.xpm");
	ft_sprites(window, &window->floor, "sprites/floor.xpm");
}

void	ft_sprites(t_mlx *window, void **image, char *path)
{
	int	width;
	int	height;

	*image = mlx_xpm_file_to_image(window->mlx_ptr, path, &width, &height);
	if (*image == NULL)
	{	
		ft_print_error(ERROR_13"\n");
		ft_close(window);
	}
}

int	ft_close(t_mlx *window)
{
	mlx_destroy_image(window->mlx_ptr, window->player_left);
	mlx_destroy_image(window->mlx_ptr, window->player_right);
	mlx_destroy_image(window->mlx_ptr, window->player_down);
	mlx_destroy_image(window->mlx_ptr, window->player_up);
	mlx_destroy_image(window->mlx_ptr, window->collec);
	mlx_destroy_image(window->mlx_ptr, window->exit_c);
	mlx_destroy_image(window->mlx_ptr, window->exit_o);
	mlx_destroy_image(window->mlx_ptr, window->wall);
	mlx_destroy_image(window->mlx_ptr, window->floor);
	ft_free_matrix(window->map);
	mlx_destroy_window (window->mlx_ptr, window->win_ptr);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	exit (0);
	return (0);
}
