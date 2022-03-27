/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:28:09 by gvolibea          #+#    #+#             */
/*   Updated: 2022/03/27 13:44:23 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "./parser/Includes/cub3d.h"
# include "./mlx/mlx.h"
# include <math.h>

typedef struct s_screen
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	char			*mlx_data_addr;
	int				bits;
	int				size_line;
	int				scr_w;
	int				scr_h;
	int				map_width;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}	t_screen;

typedef struct s_plr
{
	double		x_pos;
	double		y_pos;
	double		x_dir;
	double		y_dir;
	double		x_cam;
	double		y_cam;
}	t_plr;

typedef struct s_ray
{
	double		camera;
	double		x_ray;
	double		y_ray;
	double		x_dist_ray_step;
	double		y_dist_ray_step;
	double		x_dist_ray_real;
	double		y_dist_ray_real;
	int			x_map;
	int			y_map;
	int			strike;
	double		distance;
	double		dist_to_wall_hit;
	int			line_height;

}	t_ray;

typedef struct s_text
{
	int			tex_w;
	int			tex_h;
	int			size_line;
	int			bits;
	double		text_y;
	double		step_y;
	void		*img_no;
	void		*img_ea;
	void		*img_so;
	void		*img_we;
	char		*t_n;
	char		*t_e;
	char		*t_s;
	char		*t_w;
}	t_text;

typedef struct s_all
{
	t_ray		*ray;
	t_screen	*data;
	t_plr		*player;
	t_text		*text;
	int			*map;
}	t_all;

//init
void			init_main_struct(t_all *all, t_data *parse_data);
t_text			*make_textures(t_all *all, t_data *parse_data);
int				*get_map(t_data *parse_data);
void			init_data(t_screen *data, t_plr *player, t_data *parse_data);

//movement
int				check_position(t_all *all, double move);
void			move_forward(t_all *all, double move);
void			move_backward(t_all *all, double move);
void			turn_right(t_all *all, double rotate);
void			turn_left(t_all *all, double rotate);
void			move_left(t_all *all, double move);
void			move_right(t_all *all, double move);

//colors
unsigned int	create_trgb(int t, int r, int g, int b);
void			make_black(t_screen *data);
void			make_texture_color(t_all *all, char *dst, int y, char *texture);
void			get_proper_color(char *dst, t_all *all, int y);
void			drawline(t_all *all, int x);

//clean and exit
void			exit_failure(char *str);
void			clean_all(t_all *all);

//raycasting
void			make_3d(t_all *all);

#endif
