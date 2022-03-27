/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:53:37 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/26 14:53:39 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	turn_left(t_all *all, double rotate)
{
	double	old_dir_x;
	double	old_cam_x;

	old_dir_x = all->player->x_dir;
	old_cam_x = all->player->x_cam;
	all->player->x_dir = all->player->x_dir * cos(-rotate) - \
	all->player->y_dir * sin (-rotate);
	all->player->y_dir = old_dir_x * sin(-rotate) + \
	all->player->y_dir * cos (-rotate);
	all->player->x_cam = all->player->x_cam * cos(-rotate) - \
	all->player->y_cam * sin (-rotate);
	all->player->y_cam = old_cam_x * sin(-rotate) + \
	all->player->y_cam * cos (-rotate);
}

void	turn_right(t_all *all, double rotate)
{
	double	old_dir_x;
	double	old_cam_x;

	old_dir_x = all->player->x_dir;
	old_cam_x = all->player->x_cam;
	all->player->x_dir = all->player->x_dir * cos(rotate) - \
		all->player->y_dir * sin (rotate);
	all->player->y_dir = old_dir_x * sin(rotate) + \
		all->player->y_dir * cos (rotate);
	all->player->x_cam = all->player->x_cam * \
		cos(rotate) - all->player->y_cam * sin (rotate);
	all->player->y_cam = old_cam_x * sin(rotate) + \
		all->player->y_cam * cos (rotate);
}
