#include "cube3d.h"

void clean_all(t_all *all)
{
	mlx_destroy_image(all->data->mlx_ptr, all->data->img);
	free(all->map);
	free(all->ray);
	free(all->player);
	mlx_destroy_image(all->data->mlx_ptr, all->text->img_no);
	mlx_destroy_image(all->data->mlx_ptr, all->text->img_so);
	mlx_destroy_image(all->data->mlx_ptr, all->text->img_we);
	mlx_destroy_image(all->data->mlx_ptr, all->text->img_ea);
	mlx_destroy_window(all->data->mlx_ptr, all->data->win_ptr);
	free(all->text->textures);
	free(all->text);
	free(all->data->mlx_ptr);
	free(all->data);
	free(all);
};
