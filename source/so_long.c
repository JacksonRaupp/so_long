/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:12:34 by jackson           #+#    #+#             */
/*   Updated: 2023/12/14 17:04:41 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		main(int argc, char **argv);
int		init_game(t_window *game, int argc, char **argv);
int		check_argument(int argc, char *argv);
int		check_extension(char *argv);
int		check_content(t_window *game, char *argv);

int	main(int argc, char **argv)
{
	t_window	game;

	if (init_game(&game, argc, argv))
		return (EXIT_FAILURE);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop(game.mlx);
	exit_map(&game);
	return (0);
}

int	init_game(t_window *game, int argc, char **argv)
{
	if (check_argument(argc, argv[1]))
		return (EXIT_FAILURE);
	if (check_content(game, argv[1]))
		return (EXIT_FAILURE);
	init_vars(game);
	if (open_map(game, argv[1]))
		return (EXIT_FAILURE);
	game->temp = game->head;
	if (check_edge(game))
		return (EXIT_FAILURE);
	if (check_valid_path(game))
		return (EXIT_FAILURE);
	if (open_window(game))
		return (EXIT_FAILURE);
	if (init_wall(game))
		return (EXIT_FAILURE);
	if (init_collectible(game))
		return (EXIT_FAILURE);
	if (init_player(game))
		return (EXIT_FAILURE);
	if (init_exit(game))
		return (EXIT_FAILURE);
	if (put_map(game))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_argument(int argc, char *argv)
{
	if (argc == 1)
		return (error(WARNING_1), EXIT_FAILURE);
	else if (argc == 2 && check_extension(argv))
		return (error(WARNING_2), EXIT_FAILURE);
	else if (argc > 2)
		return (error(WARNING_3), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_extension(char *argv)
{
	char	*suffix;
	size_t	length_suffix;
	size_t	length_map_name;

	suffix = FILE_EXTENSION;
	length_suffix = ft_strlen(suffix);
	length_map_name = ft_strlen(argv);
	if (length_map_name <= length_suffix)
		return (EXIT_FAILURE);
	while (length_map_name--, length_suffix--)
	{
		if (argv[length_map_name] != suffix[length_suffix])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_content(t_window *game, char *argv)
{
	game->fd = 0;
	game->fd = open(argv, O_RDONLY);
	if (game->fd < 0)
		return (close(game->fd), error(WARNING_4), EXIT_FAILURE);
	if (read(game->fd, game->value, 17) < 17)
		return (error(WARNING_6), EXIT_FAILURE);
	close(game->fd);
	game->fd = 0;
	return (EXIT_SUCCESS);
}
