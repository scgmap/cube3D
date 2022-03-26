/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:26:46 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/26 18:27:03 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>

# define NO	0b00000001
# define SO	0b00000010
# define WE	0b00000100
# define EA	0b00001000
# define F	0b00010000
# define C	0b00100000

# define VLD 0b00111111

typedef struct s_player
{
	char			dir;
	unsigned int	x;
	unsigned int	y;
}					t_player;

typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f[3];
	int				c[3];
}					t_textures;

typedef struct s_temp
{
	char			**mass;
	char			*ptr;
	int				lines_cnt;
	int				map_width;
}					t_temp;

typedef struct s_data
{
	char			**map;
	char			*map_str;
	t_textures		*txtr;
	t_player		plyr;
	t_temp			t;
	unsigned char	f;
}					t_data;

void	parsing_start(t_data *s, int ac, char *av[]);
int		get_correctly_maps_fd(int ac, char *av[]);
int		init_texture(char *line, t_data *s);
void	convert_one_dimension_map(t_data *s);
void	check_color(char *line, t_data *s, int mask);
void	init_map(char *line, t_data *s);
void	checking_boundary_symbols(t_data *s, const char c);
void	check_player(t_data *s);
void	free_after_parsing(t_data *s);

#endif
