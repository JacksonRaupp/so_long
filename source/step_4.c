/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:50:05 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 17:35:34 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		check_rest(t_window *game);
int		open_window(t_window *game);
int		init_wall(t_window *game);
int		init_collectible(t_window *game);
int		init_player(t_window *game);
int		init_exit(t_window *game);

int	check_rest(t_window *game)
{
	game->node = game->head;
	game->temp = game->head;
	while (game->temp)
	{
		while (game->node)
		{
			if (game->node->f_value == 'C'
				|| game->node->f_value == 'E')
				return (error(WARNING_14), EXIT_FAILURE);
			if (!game->node->east)
				break ;
			game->node = game->node->east;
		}
		if (!game->temp->sout)
			break ;
		game->temp = game->temp->sout;
		game->node = game->temp;
	}
	return (EXIT_SUCCESS);
}

int	open_window(t_window *game)
{
	game->mlx = mlx_init
		(
			(game->node->xaxis + 1) * IMG_SIZE * ZOOM,
			(game->node->yaxis + 1) * IMG_SIZE * ZOOM,
			"so_long",
			false);
	if (!game->mlx)
		return (error(WARNING_8), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_wall(t_window *game)
{
	game->wall_texture = mlx_load_png
		("textures/wall.png");
	if (!game->wall_texture)
		return (error(WARNING_8), EXIT_FAILURE);
	game->wall_image = mlx_texture_to_image
		(game->mlx, game->wall_texture);
	if (!game->wall_image)
		return (error(WARNING_8), EXIT_FAILURE);
	mlx_resize_image
		(
			game->wall_image,
			IMG_SIZE * ZOOM,
			IMG_SIZE * ZOOM
			);
	return (EXIT_SUCCESS);
}

int	init_collectible(t_window *game)
{
	game->collectible_texture = mlx_load_png
		("textures/collectible.png");
	if (!game->collectible_texture)
		return (error(WARNING_8), EXIT_FAILURE);
	game->collectible_image = mlx_texture_to_image
		(game->mlx, game->collectible_texture);
	if (!game->collectible_image)
		return (error(WARNING_8), EXIT_FAILURE);
	mlx_resize_image
		(
			game->collectible_image,
			IMG_SIZE * ZOOM,
			IMG_SIZE * ZOOM);
	return (EXIT_SUCCESS);
}

int	init_player(t_window *game)
{
	game->player.texture = mlx_load_png
		("textures/player.png");
	if (!game->player.texture)
		return (error(WARNING_8), EXIT_FAILURE);
	game->player.image = mlx_texture_to_image
		(game->mlx, game->player.texture);
	if (!game->player.image)
		return (error(WARNING_8), EXIT_FAILURE);
	mlx_resize_image
		(
			game->player.image,
			IMG_SIZE * ZOOM,
			IMG_SIZE * ZOOM
			);
	return (EXIT_SUCCESS);
}

int	init_exit(t_window *game)
{
	game->exit.texture = mlx_load_png
		("textures/exit.png");
	if (!game->exit.texture)
		return (error(WARNING_8), EXIT_FAILURE);
	game->exit.image = mlx_texture_to_image
		(game->mlx, game->exit.texture);
	if (!game->exit.image)
		return (error(WARNING_8), EXIT_FAILURE);
	mlx_resize_image
		(
		game->exit.image,
		IMG_SIZE * ZOOM,
		IMG_SIZE * ZOOM
		);
	return (EXIT_SUCCESS);
}
