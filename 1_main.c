/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:54:06 by msilva-p          #+#    #+#             */
/*   Updated: 2022/11/13 18:48:47 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/so_long.h"

int	main(int argc, char **argv)
{
	int		size;
	t_mlx	window;

	if (argc != 2)
	{
		ft_print_error(ERROR_0"\n");
		return (1);
	}
	size = ft_strlen(argv[1]);
	if (size < 5 || ft_strncmp(".ber", argv[1] + size - 4, 5))
	{
		ft_print_error(ERROR_1"\n");
		return (1);
	}
	ft_struct_init(&window);
	if (ft_check_errors(&window, argv[1]) == 1)
		return (1);
	return (ft_init_game(&window));
}

void	ft_print_error(char *error)
{
	write (1, error, ft_strlen(error));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_struct_init(t_mlx *window)
{
	window->mlx_ptr = NULL;
	window->win_ptr = NULL;
	window->map = NULL;
	window->player = NULL;
	window->player_left = NULL;
	window->player_right = NULL;
	window->player_down = NULL;
	window->player_up = NULL;
	window->collec = NULL;
	window->exit_c = NULL;
	window->exit_o = NULL;
	window->wall = NULL;
	window->floor = NULL;
	window->stars = 0;
	window->movements = 0;
	window->col = 0;
	window->line = 0;
	window->player_line = 0;
	window->player_col = 0;
}

int	ft_check_errors(t_mlx *window, char *path)
{
	int		has_error;
	char	**copy;

	has_error = 0;
	has_error += ft_read_map(window, path);
	if (has_error != 0)
		return (1);
	has_error += ft_create_map(window, path);
	if (has_error != 0)
		return (1);
	has_error += ft_valid_walls(window) + ft_valid_character(window);
	if (has_error != 0)
		return (1);
	copy = ft_dup_map(window);
	if (copy == NULL)
		return (1);
	ft_locate_player(window);
	ft_test_path(copy, window->player_line, window->player_col, window);
	has_error += ft_check_path(copy, window);
	ft_free_matrix(copy);
	if (has_error != 0)
		return (1);
	return (0);
}
