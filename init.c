#include "cube3d.h"

// TEMP FUNC TO MAKE ARRAY COPY
void	*ft_memcpy_int(int *dst, int *src, size_t n)
{
	size_t	i;

	if (n == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (dst);
	i = -1;
	while (++i < n)
		dst[i] = src[i];
	return (dst);
}

void	init_main_struct(t_all *all, char **path)
{
	t_data		*data;
	t_player	*player;
	t_ray		*ray;

	data = malloc(sizeof(t_data));
	player = malloc(sizeof(t_player));
	ray = malloc(sizeof(t_ray));
	if (data == NULL || player == NULL || ray == NULL)
		exit_failure(NULL);
	init_data(data, player);
	all->ray = ray;
	all->data = data;
	all->player = player;
	all->map = get_map();
	all->text = make_textures(all, path);
}

void	make_texture_string(t_textures *text, t_all *all, char **path, int i)
{
	int	endi;

	endi = 0;
	text->img_2 = mlx_xpm_file_to_image(all->data->mlx_ptr, \
		path[i], &text->tex_w, &text->tex_h);
	text->textures[i] = mlx_get_data_addr(text->img_2, &(text->bits), \
	&(text->size_line), &endi);
}

t_textures	*make_textures(t_all *all, char **path)
{
	t_textures	*text;
	int			i;

	text = malloc(sizeof(t_textures));
	if (!text)
		exit_failure(NULL);
	text->textures = malloc(sizeof(char **));
	if (!(text->textures))
		exit_failure(NULL);
	text->tex_w = 115;
	text->tex_h = 266;
	text->bits = 32;
	text->size_line = text->tex_w * (text->bits / 8);
	i = -1;
	while (++i < 1)// fix here to upload all text files
		make_texture_string(text, all, path, i);
	return (text);
}

int	*get_map(void)
{
	int	*out;
	int	map[100] = {1,1,1,1,1,1,1,1,1,1,
						1,0,0,1,0,1,0,0,0,1,
						1,0,0,1,1,1,0,0,0,1,
						1,0,0,0,0,0,0,0,0,1,
						1,0,0,0,0,0,0,0,0,1,
						1,0,0,0,0,0,0,0,0,1,
						1,0,0,0,0,0,0,0,0,1,
						1,0,0,0,0,0,0,0,0,1,
						1,0,0,0,0,0,0,0,0,1,
						1,1,1,1,1,1,1,1,1,1};
	out = malloc(sizeof(int) * 100);
	out = ft_memcpy_int(out, map, 100);
	//printf("0 elem is %d",out[10]);
	return (out);
}

void	get_path(char **path)
{
	char	*no_path = "./red_long.xpm";
	path[0] = no_path;
}

void	init_data(t_data *data, t_player *player)
{
	int	endi;
	// part from peer
	data->map_width = 10;
	player->x_dir = 0;
	player->y_dir = -1;
	player->x_cam = 0.66;
	player->y_cam = 0;
	player->x_pos = 4;
	player->y_pos = 8;
	data->floor_color = 0xADFF2F;
	data->ceiling_color = 0x808080;
	// part from peer
	endi = 0;
	data->scr_h = 480;
	data->scr_w = 640;
	data->bits = 32;
	data->mlx_ptr = mlx_init(); //add fail check
	if (data->mlx_ptr == NULL)
		exit_failure("mlx init error");
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->scr_w, data->scr_h, \
		"Cube3D"); // add fail check
	if (data->win_ptr == NULL)
		exit_failure("mlx ptr error");
	data->img = mlx_new_image(data->mlx_ptr, data->scr_w, data->scr_h);
	if (data->img == NULL)
		exit_failure("mlx img error");
	data->size_line = data->scr_w * (data->bits / 8);
	data->mlx_data_addr = mlx_get_data_addr(data->img, &(data->bits), \
	&(data->size_line), &endi);
	if (data->mlx_data_addr == NULL)
		exit_failure("mlx data_addr error");
}
