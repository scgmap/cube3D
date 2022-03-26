/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:52:30 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/26 19:15:12 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	make_black(t_screen *data)
{
	int		x;
	int		y;
	char	*dst;

	x = 0;
	y = 0;
	while (y++ < data->scr_h)
	{
		while (x++ < data->scr_w)
		{
			dst = data->mlx_data_addr + (y * (data->size_line) + \
			x * (data->bits / 8));
			*(unsigned int *)dst = 0xFFFFFFF;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	make_texture_color(t_all *all, char *dst, int y, char *texture)
{
	double	dist_to_wall_below_one;

	dist_to_wall_below_one = all->ray->dist_to_wall_hit - \
	(double)((int)(all->ray->dist_to_wall_hit));
	*(unsigned int *)dst = *(unsigned int *)(texture + \
		(int)(all->text->step_y * y) *(int)all->text->size_line + \
		(int)(dist_to_wall_below_one *(double)(all->text->tex_w)) *\
		(int)(all->text->bits / 8));
}

void	get_proper_color(char *dst, t_all *all, int y)
{
	if (all->ray->strike == -1)
		*(unsigned int *)dst = 0xFFFFF00;
		//make_texture_color(all, dst, y, all->text->t_n);
	if (all->ray->strike == 1)
		*(unsigned int *)dst = 0xFFF00FF;
		//make_texture_color(all, dst, y, all->text->t_e);
	if (all->ray->strike == 2)
		*(unsigned int *)dst = 0x00FFFF;
		//make_texture_color(all, dst, y, all->text->t_s);
	if (all->ray->strike == -2)
		*(unsigned int *)dst = 0xFF2244;
		//make_texture_color(all, dst, y, all->text->t_w);
}

void	drawline(t_all *all, int x)
{
	char	*dst;
	int		y;
	int		start_wall;
	int		stop_wall;

	all->ray->line_height = (int)(all->data->scr_h / all->ray->distance);
	start_wall = (all->data->scr_h - all->ray->line_height) / 2;
	stop_wall = start_wall + all->ray->line_height;
	if (stop_wall > all->data->scr_h)
		stop_wall = all->data->scr_h - 1;
	y = -1;
	all->text->step_y = \
	((double)all->text->tex_h / (double)(all->ray->line_height));
	while (++y < all->data->scr_h)
	{
		dst = all->data->mlx_data_addr + (y * (all->data->size_line) + \
		x * (all->data->bits / 8));
		if (y < start_wall)
			*(unsigned int *)dst = all->data->ceiling_color;
		else if (y < stop_wall)
			get_proper_color(dst, all, y - start_wall);
		else
			*(unsigned int *)dst = all->data->floor_color;
	}
}
