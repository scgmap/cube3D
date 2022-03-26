/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:47:45 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/26 20:26:57 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	proc_esc_window(void)
{
	exit(EXIT_SUCCESS);
}

int	proc_key_keyboard(int key, void *param)
{
	double	move;
	double	rotate;

	move = 0.3;
	rotate = 0.2;
	if (key == 13)
		move_forward(((t_all *)(param)), move);
	if (key == 1)
		move_backward(((t_all *)(param)), move);
	if (key == 0)
		move_left(((t_all *)(param)), move);
	if (key == 2)
		move_right(((t_all *)(param)), move);
	if (key == 123)
		turn_left(((t_all *)(param)), rotate);
	if (key == 124)
		turn_right(((t_all *)(param)), rotate);
	if (key == 53)
		exit(EXIT_SUCCESS);
	if (key == 123 || key == 124 || key == 13 || key == 1 || \
		key == 0 || key == 2)
		make_3d((t_all *)(param));
	return (0);
}

void	exit_failure(char *str)
{
	if (!str)
		perror(strerror(errno));
	else
		perror(str);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_all	*all;
	t_data	data;

	all = malloc(sizeof(t_all));
	printf("___1a___\n");
	parsing_start(&data, argc, argv);
	printf("___2a___\n");
	all->mlx_ptr_main = mlx_init();
	printf("___3a___\n");
	init_main_struct(all, &data);
	make_3d(all);
	mlx_hook(all->data->win_ptr, 2, 1L << 0, proc_key_keyboard, all);
	mlx_hook(all->data->win_ptr, 1, 0L, proc_key_keyboard, all);
	mlx_hook(all->data->win_ptr, 17, 0L, proc_esc_window, all);
	mlx_loop(all->data->mlx_ptr);
	clean_all(all);
	free_after_parsing(&data);
	return (0);
}
