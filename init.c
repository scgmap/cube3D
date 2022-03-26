/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:39:06 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/26 20:19:30 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	*get_tetxt_arr(t_text *text, char *txtr, t_all *all, char **text_name)
{
	void	*out;
	int		endi;
	int		bits;
	int		sizeline;
	int		tex_w_h[2];

	endi = 0;
	bits = text->bits;
	sizeline = text->size_line;
	out = mlx_xpm_file_to_image(all->data->mlx_ptr, txtr, \
		&tex_w_h[0], &tex_w_h[1]);
	if (!out)
		exit_failure("mlx img error");
	*text_name = mlx_get_data_addr(out, &(bits), &(sizeline), &endi);
	return (out);
}

t_text	*make_textures(t_all *all, t_data *parse_data)
{
	t_text	*text;

	text = malloc(sizeof(t_text));
	if (!text)
		exit_failure(NULL);
	text->tex_w = 115;
	text->tex_h = 230;
	text->bits = 32;
	text->size_line = text->tex_w * (text->bits / 8);
	//text->img_no = get_tetxt_arr(text, parse_data->txtr->no, all, &text->t_n);
	//text->img_ea = get_tetxt_arr(text, parse_data->txtr->ea, all, &text->t_e);
	//text->img_so = get_tetxt_arr(text, parse_data->txtr->so, all, &text->t_s);
	//text->img_we = get_tetxt_arr(text, parse_data->txtr->we, all, &text->t_w);
	return (text);
}

void	define_direction(t_plr *player, char dir)
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

void	init_parse_data(t_screen *data, t_plr *player, t_data *parse_data)
{
	data->map_width = parse_data->t.map_width;
	player->x_pos = (double)parse_data->plyr.x + 0.5;
	player->y_pos = (double)parse_data->plyr.y + 0.5;
	define_direction(player, parse_data->plyr.dir);
	data->floor_color = create_trgb(10, parse_data->txtr->f[0], \
		parse_data->txtr->f[1], parse_data->txtr->f[2]);
	data->ceiling_color = create_trgb(10, parse_data->txtr->c[0], \
		parse_data->txtr->c[1], parse_data->txtr->c[2]);
}

void	init_data(t_screen *data, t_plr *player, t_data *parse_data)
{
	int	endi;
	int	bits;
	int	sz_l;

	init_parse_data(data, player, parse_data);
	endi = 0;
	data->scr_h = 480;
	data->scr_w = 640;
	data->bits = 32;
	//data->mlx_ptr = mlx_init();
	//if (data->mlx_ptr == NULL)
	//	exit_failure("mlx init error");
	printf("___1___\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->scr_w, data->scr_h, \
		"Cube3D");
	if (data->win_ptr == NULL)
		exit_failure("mlx ptr error");
	printf("___2___\n");
	data->img = mlx_new_image(data->mlx_ptr, data->scr_w, data->scr_h);
	if (data->img == NULL)
		exit_failure("mlx img error");
	data->size_line = data->scr_w * (data->bits / 8);
	printf("___3___\n");
	data->mlx_data_addr = mlx_get_data_addr(data->img, &(bits), \
		&(sz_l), &endi);
	if (data->mlx_data_addr == NULL)
		exit_failure("mlx data_addr error");
}
