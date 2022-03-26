/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:58:13 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/26 16:59:59 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	define_dist_wo_fisheye(t_ray *ray, t_plr *player)
{
	if (abs(ray->strike) == 1)
	{
		ray->distance = ray->x_dist_ray_real - ray->x_dist_ray_step;
		ray->dist_to_wall_hit = player->y_pos + ray->y_ray * \
			ray->distance;
	}
	else
	{
		ray->distance = ray->y_dist_ray_real - ray->y_dist_ray_step;
		ray->dist_to_wall_hit = player->x_pos + ray->x_ray * \
			ray->distance;
	}
}

// here we simply look for a movement along the camera ray
// reognize min dist on which ray goes to between 2 closest x and y values
void	get_ray_distance(t_ray *ray, t_plr *player)
{
	if (ray->x_ray > 0)
		ray->x_dist_ray_real = (ray->x_map + 1 - player->x_pos) * \
		ray->x_dist_ray_step;
	else
		ray->x_dist_ray_real = (player->x_pos - ray->x_map) * \
		ray->x_dist_ray_step;
	if (ray->y_ray > 0)
		ray->y_dist_ray_real = (ray->y_map + 1 - player->y_pos) * \
		ray->y_dist_ray_step;
	else
		ray->y_dist_ray_real = (player->y_pos - ray->y_map) * \
		ray->y_dist_ray_step;
}

void	update_ray_position(t_ray *ray, t_plr *player, t_screen *data, int x)
{
	ray->camera = ((double)((2 * x) / (double)data->scr_w)) - 1.0;
	ray->x_ray = player->x_dir + player->x_cam * ray->camera;
	ray->y_ray = player->y_dir + player->y_cam * ray->camera;
	if (ray->x_ray)
		ray->x_dist_ray_step = 1 / fabs(ray->x_ray);
	else
		ray->x_dist_ray_step = 9223372036854775807;
	if (ray->y_ray)
		ray->y_dist_ray_step = 1 / fabs(ray->y_ray);
	else
		ray->y_dist_ray_step = 9223372036854775807;
	ray->x_map = (int)player->x_pos;
	ray->y_map = (int)player->y_pos;
	get_ray_distance(ray, player);
	ray->strike = 0;
}

// check closest root to the next "wall"
// in case rays directly inside corner? - looks like is the same
// 1 = NORTH, -1 = SOUTH, 2 = EAST, -2 = WEST
void	find_dist_to_wall(t_ray *ray, t_screen *data, t_all *all)
{
	while (ray->strike == 0)
	{
		if (ray->x_dist_ray_real <= ray->y_dist_ray_real)
		{
			ray->x_dist_ray_real += ray->x_dist_ray_step;
			if (ray->x_ray > 0)
				ray->x_map++;
			else
				ray->x_map--;
			if (all->map[ray->y_map * data->map_width + ray->x_map] == 1)
				ray->strike = 1 * (int)(ray->x_ray / fabs(ray->x_ray));
		}
		else
		{
			ray->y_dist_ray_real += ray->y_dist_ray_step;
			if (ray->y_ray > 0)
				ray->y_map++;
			else
				ray->y_map--;
			if (all->map[ray->y_map * data->map_width + ray->x_map] == 1)
				ray->strike = 2 * (int)(ray->y_ray / fabs(ray->y_ray));
		}
	}
}

void	make_3d(t_all *all)
{
	t_ray		*ray;
	t_screen	*data;
	t_plr		*player;
	int			x;

	ray = all->ray;
	data = all->data;
	player = all->player;
	x = -1;
	while (++x < data->scr_w)
	{
		update_ray_position(ray, player, data, x);
		find_dist_to_wall(ray, data, all);
		define_dist_wo_fisheye(ray, player);
		all->text->text_y = 0;
		drawline(all, x);
	}
	make_black(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}
