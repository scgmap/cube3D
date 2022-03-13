#include "cube3d.h"

void clean_all(t_all *all)
{
	mlx_destroy_image(all->data->mlx_ptr, all->data->img);
	mlx_destroy_image(all->data->mlx_ptr, all->text->img_2);
	mlx_destroy_window(all->data->mlx_ptr, all->data->win_ptr);
	free(all->map);
	free(all->ray);
	free(all->player);
	free(all->text->textures); // check later
	free(all->text);
	free(all->data->mlx_ptr);
	free(all->data);
	free(all);
};
