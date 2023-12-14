/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:50:07 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 13:02:10 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		put_map(t_window *game);
void	put_wall(t_window *game);
int		put_collectible(t_window *game);
void	put_player(t_window *game);
void	put_exit(t_window *game);

int	put_map(t_window *game)
{
	game->node = game->head;
	while (game->node)
	{
		game->temp = game->node;
		while (game->temp)
		{
			if (game->temp->value == '1')
				put_wall(game);
			else if (game->temp->value == 'C')
			{
				if (put_collectible(game))
					return (EXIT_FAILURE);
			}
			else if (game->temp->value == 'P')
				put_player(game);
			else if (game->temp->value == 'E')
				put_exit(game);
			game->temp = game->temp->east;
		}
		game->node = game->node->sout;
	}
	return (EXIT_SUCCESS);
}

void	put_wall(t_window *game)
{
	mlx_image_to_window
		(
			game->mlx,
			game->wall_image,
			game->temp->xaxis * IMG_SIZE * ZOOM,
			game->temp->yaxis * IMG_SIZE * ZOOM
			);
}

int	put_collectible(t_window *game)
{
	game->temp->texture = mlx_load_png
		("textures/collectible.png");
	if (!game->temp->texture)
		return (error(WARNING_8), EXIT_FAILURE);
	game->temp->image = mlx_texture_to_image
		(game->mlx, game->temp->texture);
	if (!game->temp->image)
		return (error(WARNING_8), EXIT_FAILURE);
	mlx_resize_image
		(
			game->temp->image,
			IMG_SIZE * ZOOM,
			IMG_SIZE * ZOOM);
	mlx_image_to_window
		(
			game->mlx,
			game->temp->image,
			game->temp->xaxis * IMG_SIZE * ZOOM,
			game->temp->yaxis * IMG_SIZE * ZOOM);
	return (EXIT_SUCCESS);
}

void	put_player(t_window *game)
{
	game->player.node = *game->temp;
	mlx_image_to_window
		(
			game->mlx,
			game->player.image,
			game->player.node.xaxis * IMG_SIZE * ZOOM,
			game->player.node.yaxis * IMG_SIZE * ZOOM
			);
}

void	put_exit(t_window *game)
{
	game->exit.node = *game->temp;
}
