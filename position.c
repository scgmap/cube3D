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
