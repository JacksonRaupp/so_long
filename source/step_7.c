/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:55:47 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 17:15:25 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	exit_map(t_window *game);
void	free_map(t_window *game);

void	exit_map(t_window *game)
{
	mlx_delete_texture(game->wall_texture);
	mlx_delete_image(game->mlx, game->wall_image);
	mlx_delete_texture(game->collectible_texture);
	mlx_delete_image(game->mlx, game->collectible_image);
	mlx_delete_texture(game->player.texture);
	mlx_delete_image(game->mlx, game->player.image);
	mlx_delete_texture(game->exit.texture);
	mlx_delete_image(game->mlx, game->exit.image);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	free_map(game);
}

void	free_map(t_window *game)
{
	while (game->head)
	{
		game->node = game->head;
		while (game->node)
		{
			game->temp = game->node;
			game->node = game->node->east;
			free(game->temp);
		}
		game->head = game->head->sout;
	}
}
