/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:06:22 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 17:12:38 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define IMG_SIZE	16
# define ZOOM		2

# define FILE_EXTENSION	".ber"

# include "../library/MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_node
{
	int				index;
	char			value;
	char			f_value;
	int				xaxis;
	int				yaxis;
	struct s_node	*west;
	struct s_node	*east;
	struct s_node	*nort;
	struct s_node	*sout;
}t_node;

typedef struct s_object
{
	int				qty;
	t_node			node;
	mlx_image_t		*image;
	mlx_texture_t	*texture;
}t_object;

typedef struct s_window
{
	int				x;
	int				y;
	int				fd;
	int				index;
	char			value[2];
	int				collectible;
	int				movements;
	mlx_t			*mlx;
	t_node			*head;
	t_node			*node;
	t_node			*temp;
	t_object		exit;
	t_object		player;
	mlx_image_t		*wall_image;
	mlx_texture_t	*wall_texture;
	mlx_image_t		*collectible_image;
	mlx_texture_t	*collectible_texture;
}t_window;

size_t	ft_strlen(const char *str);
void	error(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);

int		ft_printf(const char *str, ...);
int		put_str(const char *str);
int		put_chr(const char chr);
int		is_txt(va_list args, const char flag);
int		is_num(va_list args, const char flag);
int		is_hex(va_list args, const char flag);

int		init_game(t_window *game, int argc, char **argv);
int		check_argument(int argc, char *argv);
int		check_extension(char *argv);
int		check_content(t_window *game, char *argv);

void	init_vars(t_window *game);
int		open_map(t_window *game, char *argv);
int		read_map(t_window *game);
int		check_character(char character);
int		create_new_node(t_window *game);

int		node_aloc(t_window *game);
void	find_last_node(t_window *game);
void	link_line(t_window *game);
void	link_column(t_window *game);
int		check_rectangle(t_window *game);

int		check_edge(t_window *game);
int		check_valid_path(t_window *game);
void	check_player(t_window *game);
void	flood_fill(t_window *game);
int		flood_fill_util(t_node *node);

int		check_rest(t_window *game);
int		open_window(t_window *game);
int		init_wall(t_window *game);
int		init_collectible(t_window *game);
int		init_player(t_window *game);
int		init_exit(t_window *game);

int		put_map(t_window *game);
void	put_wall(t_window *game);
void		put_collectible(t_window *game);
void	put_player(t_window *game);
void	put_exit(t_window *game);

void	keyhook(mlx_key_data_t keydata, void *game);
void	action_up(t_window *game);
void	action_down(t_window *game);
void	action_left(t_window *game);
void	action_right(t_window *game);
void	collect(t_window *game);

void	exit_map(t_window *game);
void	free_map(t_window *game);

# define WARNING_1    "Alert: Please insert a map."
# define WARNING_2    "Alert: Invalid argument!"
# define WARNING_3    "Alert: Too many arguments when calling the function."
# define WARNING_4    "Alert: Map not found!"
# define WARNING_5    "Alert: Invalid map!"
# define WARNING_6    "Alert: Empty map or insufficient characters."
# define WARNING_7    "Alert: Invalid characters in the map."
# define WARNING_8    "Alert: Error allocating memory."
# define WARNING_9    "Alert: Non-rectangular map"
# define WARNING_10   "Alert: Allowed to contain 1 player"
# define WARNING_11   "Alert: Allowed to contain 1 exit"
# define WARNING_12   "Alert: Allowed to contain at least 1 collectible"
# define WARNING_13   "Alert: Evasive map"
# define WARNING_14   "Alert: Player arrested"

#endif
