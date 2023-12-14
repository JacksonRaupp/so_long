/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:50:10 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 18:03:40 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	keyhook(mlx_key_data_t keydata, void *game);
void	action_up(t_window *game);
void	action_down(t_window *game);
void	action_left(t_window *game);
void	action_right(t_window *game);
void	collect(t_window *game);

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
		game->player.node = *game->player.node.nort;
		if (game->player.node.value == 'C')
			collect(game);
		ft_printf("\nNumber of movements: %d", (game->movements += 1));
	}
}

void	action_down(t_window *game)
{
	if (game->player.node.sout && game->player.node.sout->value != '1')
	{
		game->player.image->instances[0].y += IMG_SIZE * ZOOM;
		game->player.node = *game->player.node.sout;
		if (game->player.node.value == 'C')
			collect(game);
		ft_printf("\nNumber of movements: %d", (game->movements += 1));
	}
}

void	action_left(t_window *game)
{
	if (game->player.node.west && game->player.node.west->value != '1')
	{
		game->player.image->instances[0].x -= IMG_SIZE * ZOOM;
		game->player.node = *game->player.node.west;
		if (game->player.node.value == 'C')
			collect(game);
		ft_printf("\nNumber of movements: %d", (game->movements += 1));
	}
}

void	action_right(t_window *game)
{
	if (game->player.node.east && game->player.node.east->value != '1')
	{
		game->player.image->instances[0].x += IMG_SIZE * ZOOM;
		game->player.node = *game->player.node.east;
		if (game->player.node.value == 'C')
			collect(game);
		ft_printf("\nNumber of movements: %d", (game->movements += 1));
	}
}

void	collect(t_window *game)
{
	int	i;

	i = 0;
	while (i < game->collectible)
	{
		if (game->collectible_image->instances[i].x
			/ (IMG_SIZE  * ZOOM) == game->player.node.xaxis
			&& game->collectible_image->instances[i].y
			/ (IMG_SIZE  * ZOOM) == game->player.node.yaxis)
		{
			game->collectible_image->instances[i].enabled = 0;
			game->player.node.value = '0';
			game->collectible -= 1;
			break ;
		}
		i++;
	}
}
