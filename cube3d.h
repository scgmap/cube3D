#ifndef CUBE3D_H
# define CUBE3D_H

# include "./minilibx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>

typedef struct s_data
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
}	t_data;

typedef struct s_player
{
	double		x_pos;
	double		y_pos;
	double		x_dir;
	double		y_dir;
	double		x_cam;
	double		y_cam;
	double		moveX;
	double		moveY;
}	t_player;

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

typedef struct s_textures
{
	int			tex_w;
	int			tex_h;
	int			size_line;
	int			bits;
	double		text_y;
	double		step_y;
	void		*img_2;
	char		**textures;
}	t_textures;

typedef struct s_all
{
	t_ray		*ray;
	t_data		*data;
	t_player	*player;
	t_textures	*text;
	int			*map;
}	t_all;

//init
void			init_main_struct(t_all *all, char **path);
t_textures		*make_textures(t_all *all, char **path);
int				*get_map(void); // take out
void			get_path(char **path); // take out
void			init_data(t_data *data, t_player *player);

//movement
int				check_position(t_all *all, double move);
void			move_forward(t_all *all, double move);
void			move_backward(t_all *all, double move);
void			turn_right(t_all *all, double rotate);
void			turn_left(t_all *all, double rotate);

//colors
unsigned int	create_trgb(int t, int r, int g, int b);
void			make_black(t_data *data);
void			make_texture_color(t_all *all, char *dst, int y, int text_num);
void			get_proper_color(char *dst, t_all *all, int y);
void			drawline(t_all *all, int x);

//clean and exit
void			exit_failure(char *str);

//raycasting
void			make_3d(t_all *all);

#endif
