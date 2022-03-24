/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriyp <dmitriyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:03:21 by dmitriyp          #+#    #+#             */
/*   Updated: 2022/03/24 22:26:39 by gvolibea         ###   ########.fr       */
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

	move = 0.2;
	rotate = 0.15;
	if (key == 126)
		move_forward(((t_all *)(param)), move);
	if (key == 125)
		move_backward(((t_all *)(param)), move);
	if (key == 123)
		turn_left(((t_all *)(param)), rotate);
	if (key == 124)
		turn_right(((t_all *)(param)), rotate);
	if (key == 53)
		exit(EXIT_SUCCESS);
	if (key == 123 || key == 124 || key == 125 || key == 126)
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
	parsing_start(&data, argc, argv);
	init_main_struct(all, &data);
	make_3d(all);
	mlx_hook(all->data->win_ptr, 2, 1L << 2, proc_key_keyboard, all);
	mlx_hook(all->data->win_ptr, 17, 0L, proc_esc_window, all);
	mlx_loop(all->data->mlx_ptr);
	clean_all(all);
	free_after_parsing(&data);

	return (0);
}
