/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:42:05 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/23 21:02:44 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "./../cub3d.h"

# define MOVE_SPEED 0.03
# define ROT_SPEED 0.035
# define WIN_W 1920
# define WIN_H 1080
# define CELL 64

typedef struct s_norm
{
	mlx_texture_t	*tex;
	uint8_t			*p;
	uint32_t		col;
	double			tinfo[3];
	int				ty;
	int				start;
	int				x;
	int				draw_start;
	int				draw_end;
}	t_norm;

//init_data//
void		init_player_flags(t_config *cfg);
void		init_player_direction(t_config *cfg, char c);
void		init_player_direction1(t_config *cfg, char c);
void		*ft_memset(void *b, int c, size_t len);

//key_mlx//
void		set_key_state(mlx_key_data_t key, t_config *cfg, int press);
void		handle_keys(mlx_key_data_t key, void *param);

//move//
int			check_point_wall(t_config *cfg, int mx, int my);
int			is_wall(t_config *cfg, double x, double y);
void		rotate(t_config *cfg, double angle);
void		apply_rotation(t_config *cfg);
void		apply_movement(t_config *cfg, double *nx, double *ny);

//raycasting//
void		raycasting(t_config *cfg);
void		cast_single_ray(t_config *cfg, int x, t_norm *norm);
void		calc_draw_bounds(double wall_dist, int *start, int *end);
double		calc_wall_dist(t_config *cfg, t_ray *ray);
void		perform_dda(t_config *cfg, t_ray *ray);

//raycasting2//
int			check_hit(t_config *cfg, t_ray *ray);
void		init_step_y(t_config *cfg, t_ray *ray);
void		init_step_x(t_config *cfg, t_ray *ray);
void		init_delta_dist(t_ray *ray);
void		init_ray_direction(t_config *cfg, int x, t_ray *ray);

//render//
void		update_player_position(t_config *cfg);
int			render_2d_map(t_config *cfg);
void		render_frame(void *param);
void		set_player_position(t_config *cfg);

//win_mlx//
int			draw_vertical_line(t_config *cfg, t_norm *norm, t_ray *ray);
int			init_mlx(t_config *cfg);

//textures//
int			load_all_textures(t_config *cfg);
int			load_texture(mlx_texture_t **texture, const char *path);
int			unload_all_textures(t_config *cfg);

//floor_ceiling//
uint32_t	rgb_to_color(t_rgb *color);
void		draw_ceiling(t_config *cfg);
void		draw_floor(t_config *cfg);
void		draw_floor_ceiling(t_config *cfg);

#endif
