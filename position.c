/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:52:42 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/26 14:57:25 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_forward(t_all *all, double move)
{
	if (check_position(all, move))
	{
		all->player->y_pos += move * all->player->y_dir;
		all->player->x_pos += move * all->player->x_dir;
	}
}

void	move_backward(t_all *all, double move)
{
	if (check_position(all, -1 * move))
	{
		all->player->y_pos -= move * all->player->y_dir;
		all->player->x_pos -= move * all->player->x_dir;
	}
}

void	move_left(t_all *all, double move)
{
	double	old_dir_x;
	double	old_dir_y;
	double	rotate;

	rotate = M_PI / 2;
	old_dir_x = all->player->x_dir;
	old_dir_y = all->player->y_dir;
	all->player->x_dir = all->player->x_dir * cos(-rotate) - \
	all->player->y_dir * sin (-rotate);
	all->player->y_dir = old_dir_x * sin(-rotate) + \
	all->player->y_dir * cos (-rotate);
	move_forward(all, move);
	all->player->x_dir = old_dir_x;
	all->player->y_dir = old_dir_y;
}

void	move_right(t_all *all, double move)
{
	double	old_dir_x;
	double	old_dir_y;
	double	rotate;

	rotate = M_PI / 2;
	old_dir_x = all->player->x_dir;
	old_dir_y = all->player->y_dir;
	all->player->x_dir = all->player->x_dir * cos(rotate) - \
		all->player->y_dir * sin (rotate);
	all->player->y_dir = old_dir_x * sin(rotate) + \
		all->player->y_dir * cos (rotate);
	move_forward(all, move);
	all->player->x_dir = old_dir_x;
	all->player->y_dir = old_dir_y;
}

int	check_position(t_all *all, double move)
{
	int	y_new;
	int	x_new;

	y_new = (int)(all->player->y_pos + move * all->player->y_dir);
	x_new = (int)(all->player->x_pos + move * all->player->x_dir);
	if (all->map[y_new * all->data->map_width + x_new] == 1)
		return (0);
	return (1);
}
