#include "cube3d.h"

// TEMP FUNC TO MAKE ARRAY COPY
/*void	*ft_memcpy_int(int *dst, int *src, size_t n)
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
}*/

void print_map(t_all *map) // temps
{
	int i;
	int j;
	i = -1;
	j = -1;

	while(++i < 19)
	{
		while(++j < map->data->map_width)
			printf("%d",map->map[i* map->data->map_width + j]);
		j = -1;
		printf("\n");
	}

}

int	*get_map(t_data *parse_data)
{
	int	*out;
	int	i;

	i = -1;
	out = malloc(sizeof(int) * ft_strlen(parse_data->map_str));
	while(parse_data->map_str[++i])
	{
		if (parse_data->map_str[i] != ' ')
			out[i] = parse_data->map_str[i] - '0';
		else
			out[i] = 1;
	}
	return (out);
}

void	init_main_struct(t_all *all, t_data *parse_data)
{
	t_screen	*data;
	t_plr		*player;
	t_ray		*ray;

	data = malloc(sizeof(t_screen));
	player = malloc(sizeof(t_plr));
	ray = malloc(sizeof(t_ray));
	if (data == NULL || player == NULL || ray == NULL)
		exit_failure(NULL);
	init_data(data, player, parse_data);

	all->ray = ray;
	all->data = data;
	all->player = player;
	all->map = get_map(parse_data);
//	print_map(all);
	all->text = make_textures(all, parse_data);
}

void *get_tetxt_arr(t_text *text, char *txtr, t_all *all, int i)
{
	void *out;
	int	endi;
	int	bits;
	int	sizeline;
	int	tex_w;
	int	tex_h;

	endi = 0;
	bits = text->bits;
	sizeline = text->size_line;
	tex_w = text->tex_w;
	tex_h = text->tex_h;

	out = mlx_xpm_file_to_image(all->data->mlx_ptr, txtr, &tex_w, &tex_h);
	if(!out)
		exit_failure("mlx img error");
	text->textures[i] = mlx_get_data_addr(out, &(bits), &(sizeline), &endi);
	if (!text->textures[i])
		exit_failure("mlx data_addr error");
	return (out);
};


void	make_texture_string(t_text *text, t_all *all, t_textures *txtr)//, int i)
{

	//check if you need so many
	/*endi = 0;

	bits = text->bits;
	sizeline = text->size_line;
	tex_w = text->tex_w;
	tex_h = text->tex_h;

	text->img_no = mlx_xpm_file_to_image(all->data->mlx_ptr, \
		txtr->no, &text->tex_w, &text->tex_h);
	text->img_ea = mlx_xpm_file_to_image(all->data->mlx_ptr, \
		txtr->ea, &tex_w, &tex_h);
	text->img_so = mlx_xpm_file_to_image(all->data->mlx_ptr, \
		txtr->so, &text->tex_w, &text->tex_h);
	text->img_we = mlx_xpm_file_to_image(all->data->mlx_ptr, \
		txtr->we, &text->tex_w, &text->tex_h);
	if(!text->img_no || !text->img_ea || !text->img_so || !text->img_we)
		exit_failure("mlx img error");*/
	//text->textures[0] = mlx_get_data_addr(text->img_no, &(text->bits), \
//		&(text->size_line), &endi);
	//printf("add is %d %d\n", text->tex_w, text->tex_h);

//	text->textures[1] = mlx_get_data_addr(text->img_ea, &(bits), \
//		&(sizeline), &endi);
	/*text->textures[2] = mlx_get_data_addr(text->img_so, &(text->bits), \
		&(text->size_line), &endi);
	text->textures[3] = mlx_get_data_addr(text->img_we, &(text->bits), \
		&(text->size_line), &endш);
	if (!text->textures[0] || !text->textures[1] || !text->textures[2] ||\
		!text->textures[3])
		exit_failure("mlx data_addr error");*/
//printf("add textt is %p\n",text->textures[i]); // leaks;
}

t_text	*make_textures(t_all *all, t_data *parse_data)
{
	t_text	*text;

	text = malloc(sizeof(t_text));
	if (!text)
		exit_failure(NULL);
	text->textures = malloc(sizeof(char **));
	if (!(text->textures))
		exit_failure(NULL);
	text->tex_w = 115;
	text->tex_h = 230;
	text->bits = 32;
	text->size_line = text->tex_w * (text->bits / 8);
	//make_texture_string(text, all, parse_data->txtr);
	text->img_no = get_tetxt_arr(text, parse_data->txtr->no, all, 0);
	text->img_ea = get_tetxt_arr(text, parse_data->txtr->so, all, 1);
	text->img_we = get_tetxt_arr(text, parse_data->txtr->we, all, 2);
	text->img_we = get_tetxt_arr(text, parse_data->txtr->ea, all, 3);
	/*make_texture_string(text, all, parse_data->txtr->no, 0);
	make_texture_string(text, all, parse_data->txtr->ea, 1);
	make_texture_string(text, all, parse_data->txtr->so, 2);
	make_texture_string(text, all, parse_data->txtr->we, 3);*/
	return (text);
}

void define_direction(t_plr *player, char dir)
{
	if (dir == 'N' || dir == 'S')
	{
		player->x_dir = 0;
		player->y_dir = 1;
		player->x_cam = 0.66;
		player->y_cam = 0;
		if (dir == 'N')
			player->y_dir = -1;
	}
	else
	{
		player->x_dir = 1;
		player->y_dir = 0;
		player->x_cam = 0;
		player->y_cam = 0.66;
		if (dir == 'W')
			player->x_dir = -1;
	}
}

void	init_data(t_screen *data, t_plr *player, t_data *parse_data)
{
	int	endi;
	// part from peer
	data->map_width = parse_data->t.map_width;
	player->x_pos = (double)parse_data->plyr.x + 0.5;
	player->y_pos = (double)parse_data->plyr.y + 0.5;
	define_direction(player, parse_data->plyr.dir);
	data->floor_color = create_trgb(10, parse_data->txtr->f[0], \
		parse_data->txtr->f[1], parse_data->txtr->f[2]);
	data->ceiling_color = create_trgb(10, parse_data->txtr->c[0], \
		parse_data->txtr->c[1], parse_data->txtr->c[2]);
	endi = 0;
	data->scr_h = 480;
	data->scr_w = 640;
	data->bits = 32;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		exit_failure("mlx init error");
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->scr_w, data->scr_h, \
		"Cube3D");
	if (data->win_ptr == NULL)
		exit_failure("mlx ptr error");
	data->img = mlx_new_image(data->mlx_ptr, data->scr_w, data->scr_h);
	if (data->img == NULL)
		exit_failure("mlx img error");
	data->size_line = data->scr_w * (data->bits / 8);
	data->mlx_data_addr = mlx_get_data_addr(data->img, &(data->bits), \
		&(data->size_line), &endi); // changed img
	if (data->mlx_data_addr == NULL)
		exit_failure("mlx data_addr error");
}
