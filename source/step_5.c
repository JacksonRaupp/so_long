/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:50:07 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 17:12:47 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		put_map(t_window *game);
void	put_wall(t_window *game);
void	put_collectible(t_window *game);
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
				put_collectible(game);
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

void	put_collectible(t_window *game)
{
	mlx_image_to_window
		(
			game->mlx,
			game->collectible_image,
			game->temp->xaxis * IMG_SIZE * ZOOM,
			game->temp->yaxis * IMG_SIZE * ZOOM);
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
