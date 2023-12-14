/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:50:10 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 14:36:54 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	keyhook(mlx_key_data_t keydata, void *game);
void	action_up(t_window *game);
void	action_down(t_window *game);
void	action_left(t_window *game);
void	action_right(t_window *game);

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_window	*game;

	game = param;
	if ((keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS))
		action_up(game);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		action_down(game);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		action_left(game);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		action_right(game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (game->collectible == 0)
	{
		mlx_image_to_window
			(game->mlx,
				game->exit.image,
				game->exit.node.xaxis * IMG_SIZE * ZOOM,
				game->exit.node.yaxis * IMG_SIZE * ZOOM);
	}
	if (game->collectible == 0 && game->player.node.value == 'E')
		mlx_close_window(game->mlx);
}

void	action_up(t_window *game)
{
	if (game->player.node.nort && game->player.node.nort->value != '1')
	{
		game->player.image->instances[0].y -= IMG_SIZE * ZOOM;
		if (game->player.node.nort->value == 'C')
		{
			mlx_delete_image(game->mlx, game->player.node.nort->image);
			mlx_delete_texture(game->player.node.nort->texture);
			game->player.node.nort->value = '0';
			game->collectible -= 1;
		}
		game->player.node = *game->player.node.nort;
		ft_printf("\nNumber of movements: %d", (game->movements += 1));
	}
}

void	action_down(t_window *game)
{
	if (game->player.node.sout && game->player.node.sout->value != '1')
	{
		game->player.image->instances[0].y += IMG_SIZE * ZOOM;
		if (game->player.node.sout->value == 'C')
		{
			mlx_delete_image(game->mlx, game->player.node.sout->image);
			mlx_delete_texture(game->player.node.sout->texture);
			game->player.node.sout->value = '0';
			game->collectible -= 1;
		}
		game->player.node = *game->player.node.sout;
		ft_printf("\nNumber of movements: %d", (game->movements += 1));
	}
}

void	action_left(t_window *game)
{
	if (game->player.node.west && game->player.node.west->value != '1')
	{
		game->player.image->instances[0].x -= IMG_SIZE * ZOOM;
		if (game->player.node.west->value == 'C')
		{
			mlx_delete_image(game->mlx, game->player.node.west->image);
			mlx_delete_texture(game->player.node.west->texture);
			game->player.node.west->value = '0';
			game->collectible -= 1;
		}
		game->player.node = *game->player.node.west;
		ft_printf("\nNumber of movements: %d", (game->movements += 1));
	}
}

void	action_right(t_window *game)
{
	if (game->player.node.east && game->player.node.east->value != '1')
	{
		game->player.image->instances[0].x += IMG_SIZE * ZOOM;
		if (game->player.node.east->value == 'C')
		{
			mlx_delete_image(game->mlx, game->player.node.east->image);
			mlx_delete_texture(game->player.node.east->texture);
			game->player.node.east->value = '0';
			game->collectible -= 1;
		}
		game->player.node = *game->player.node.east;
		ft_printf("\nNumber of movements: %d", (game->movements += 1));
	}
}
