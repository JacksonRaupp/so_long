/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:49:57 by jraupp            #+#    #+#             */
/*   Updated: 2023/12/14 11:44:19 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_vars(t_window *game);
int		open_map(t_window *game, char *argv);
int		read_map(t_window *game);
int		check_character(char character);
int		create_new_node(t_window *game);

void	init_vars(t_window *game)
{
	game->head = NULL;
	game->node = NULL;
	game->temp = NULL;
	game->x = -1;
	game->y = 0;
	game->index = 1;
	game->value[1] = '\0';
	game->movements = 0;
}

int	open_map(t_window *game, char *argv)
{
	game->fd = open(argv, O_RDONLY);
	game->player.qty = 0;
	game->exit.qty = 0;
	game->collectible = 0;
	if (read_map(game))
		return (EXIT_FAILURE);
	if (game->player.qty != 1)
	{
		close(game->fd);
		return (error(WARNING_10), EXIT_FAILURE);
	}
	if (game->exit.qty != 1)
	{
		close(game->fd);
		return (error(WARNING_11), EXIT_FAILURE);
	}
	if (game->collectible <= 0)
	{
		close(game->fd);
		return (error(WARNING_12), EXIT_FAILURE);
	}
	if (check_rectangle(game))
		return (EXIT_FAILURE);
	close(game->fd);
	return (EXIT_SUCCESS);
}

int	read_map(t_window *game)
{
	while (game->x++, read(game->fd, game->value, 1))
	{
		if (game->value[0] == 'P')
			game->player.qty += 1;
		if (game->value[0] == 'E')
			game->exit.qty += 1;
		if (game->value[0] == 'C')
			game->collectible += 1;
		if (check_character(game->value[0]))
			return (error(WARNING_7), EXIT_FAILURE);
		if (game->value[0] != '\n')
		{
			if (create_new_node(game))
				return (EXIT_FAILURE);
		}
		else
		{
			game->y++;
			game->x = -1;
		}
	}
	return (EXIT_SUCCESS);
}

int	check_character(char character)
{
	char	*str;

	str = "\n01PCE\0";
	while (*str)
	{
		if (*str++ == character)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	create_new_node(t_window *game)
{
	if (node_aloc(game))
		return (EXIT_FAILURE);
	if (!game->head)
		game->head = game->node;
	else
	{
		find_last_node(game);
		if (game->temp->yaxis == game->node->yaxis)
			link_line(game);
		else
			link_column(game);
	}
	return (EXIT_SUCCESS);
}
