/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:50:02 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 13:23:59 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		check_edge(t_window *game);
int		check_valid_path(t_window *game);
void	check_player(t_window *game);
void	flood_fill(t_window *game);
int		flood_fill_util(t_node *node);

int	check_edge(t_window *game)
{
	while (game->temp->east)
	{
		game->temp = game->temp->east;
		if (game->temp->value != '1')
			return (error(WARNING_13), EXIT_FAILURE);
	}
	while (game->temp->sout)
	{
		game->temp = game->temp->sout;
		if (game->temp->value != '1')
			return (error(WARNING_13), EXIT_FAILURE);
	}
	while (game->temp->west)
	{
		game->temp = game->temp->west;
		if (game->temp->value != '1')
			return (error(WARNING_13), EXIT_FAILURE);
	}
	while (game->temp->nort)
	{
		game->temp = game->temp->nort;
		if (game->temp->value != '1')
			return (error(WARNING_13), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_valid_path(t_window *game)
{
	check_player(game);
	flood_fill(game);
	if (check_rest(game))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	check_player(t_window *game)
{
	game->node = game->head;
	game->temp = game->head;
	while (game->temp)
	{
		while (game->node)
		{
			if (game->node->f_value == 'P')
				game->player.node = *game->node;
			if (!game->node->east)
				break ;
			game->node = game->node->east;
		}
		if (!game->temp->sout)
			break ;
		game->temp = game->temp->sout;
		game->node = game->temp;
	}
}

void	flood_fill(t_window *game)
{
	if (game)
		flood_fill_util(&game->player.node);
}

int	flood_fill_util(t_node *node)
{
	if (node->east == NULL || node->west == NULL
		|| node->sout == NULL || node->nort == NULL || node->f_value == '1')
		return (0);
	node->f_value = '1';
	if (flood_fill_util(node->east) || flood_fill_util(node->west)
		|| flood_fill_util(node->sout) || flood_fill_util(node->nort))
		return (1);
	return (0);
}
