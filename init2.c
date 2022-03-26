/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:39:09 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/26 22:13:41 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
//#include "./minilibx/mlx_int.h"

void	init_main_struct(t_all *all, t_data *parse_data)
{
	t_screen	*data;
	t_plr		*player;
	t_ray		*ray;

	data = malloc(sizeof(t_screen));// +sizeof(mlx_ptr_t));
	player = malloc(sizeof(t_plr));
	ray = malloc(sizeof(t_ray));
	if (data == NULL || player == NULL || ray == NULL)
		exit_failure(NULL);
	all->map = get_map(parse_data);
	all->text = make_textures(all, parse_data);
	init_data(data, player, parse_data);
	all->ray = ray;
	all->data = data;
	all->player = player;
	//all->map = get_map(parse_data);
	 ////

}

int	*get_map(t_data *parse_data)
{
	(void)parse_data;
	int out1[15] = {1,1,1,
				1,0,1,
				1,0,1,
				1,0,1,
				1,1,1};
	int *out;
	int i;

	out = malloc(sizeof(int) * 15);
	i = -1;
	while(++i < 15)
	{
		out[i] = out1[i];
	}
	return (out);
}
/*
int	*get_map(t_data *parse_data)
{
	int	*out;
	int	i;

	i = -1;
	out = malloc(sizeof(int) * ft_strlen(parse_data->map_str));
	while (parse_data->map_str[++i])
	{
		if (parse_data->map_str[i] != ' ')
			out[i] = parse_data->map_str[i] - '0';
		else
			out[i] = 1;
	}
	return (out);
}*/
