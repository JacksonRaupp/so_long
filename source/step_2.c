/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:49:59 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 16:27:53 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		node_aloc(t_window *game);
void	find_last_node(t_window *game);
void	link_line(t_window *game);
void	link_column(t_window *game);
int		check_rectangle(t_window *game);

int	node_aloc(t_window *game)
{
	game->node = ft_calloc(sizeof(t_node), 1);
	if (!game->node)
		return (error(WARNING_8), EXIT_FAILURE);
	game->node->index = game->index++;
	game->node->value = game->value[0];
	game->node->f_value = game->value[0];
	game->node->xaxis = game->x;
	game->node->yaxis = game->y;
	return (EXIT_SUCCESS);
}

void	find_last_node(t_window *game)
{
	game->temp = game->head;
	while (game->temp->sout)
		game->temp = game->temp->sout;
	while (game->temp->east)
		game->temp = game->temp->east;
}

void	link_line(t_window *game)
{
	game->temp->east = game->node;
	game->node->west = game->temp;
	if (game->temp->nort)
	{
		game->temp = game->temp->nort;
		if (game->temp->east)
		{
			game->temp = game->temp->east;
			game->temp->sout = game->node;
			game->node->nort = game->temp;
		}
	}
}

void	link_column(t_window *game)
{
	while (game->temp->west)
		game->temp = game->temp->west;
	game->temp->sout = game->node;
	game->node->nort = game->temp;
}

int	check_rectangle(t_window *game)
{
	if (((game->node->xaxis + 1) * (game->node->yaxis + 1))
		!= game->node->index)
		return (error(WARNING_9), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
