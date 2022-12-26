/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:23:24 by msilva-p          #+#    #+#             */
/*   Updated: 2022/11/13 18:54:57 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "defines.h"
# include "../GNL/get_next_line.h"
# include <mlx.h>
# include <fcntl.h>
# include <X11/keysym.h>

struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	void	*player;
	void	*player_left;
	void	*player_right;
	void	*player_down;
	void	*player_up;
	void	*collec;
	void	*exit_c;
	void	*exit_o;
	void	*wall;
	void	*floor;
	int		stars;
	int		movements;
	int		col;
	int		line;
	int		player_line;
	int		player_col;
};
typedef struct s_mlx	t_mlx;

//Functions
//Check
int		ft_check_characters(t_mlx *window, int e, int p, int invalid);
int		ft_check_exit(int exit, int collec);
int		ft_check_path(char **copy, t_mlx *window);
void	ft_print_error(char *error);
int		ft_check_errors(t_mlx *window, char *path);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_test_path(char **copy, int line, int col, t_mlx *window);
int		ft_valid_character(t_mlx *window);
int		ft_valid_walls(t_mlx *window);

//starting
int		ft_count_col(char *temp);
int		ft_count_collectibles(t_mlx *window);
int		ft_count_lines(int fd, char *temp, t_mlx *window);
int		ft_create_map(t_mlx *window, char *path);
char	**ft_dup_map(t_mlx *window);
int		ft_init_game(t_mlx *window);
int		ft_read_map(t_mlx *window, char *path);
int		ft_show_map(t_mlx *window);
void	ft_struct_init(t_mlx *window);

//events
int		ft_event(int key, t_mlx *window);
void	ft_event_arrow(t_mlx *window, int col, int line);
int		ft_show_moves(t_mlx *window);

//images
void	ft_locate_player(t_mlx *window);
void	ft_put_image_to_window(t_mlx *window, void *image, int x, int y);
void	ft_put_sprites(t_mlx *window);
void	ft_sprites(t_mlx *window, void **image, char *path);

//ending
int		ft_close(t_mlx *window);
int		ft_close_and_free(int fd, char *temp);
void	ft_free_matrix(char **matrix);

#endif