/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:18:06 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/11/16 12:19:02 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "./parsing/parsing.h"
# include "./mlx/include/MLX42/MLX42.h"

# define ERR_MEM "Allocation Faield\n"

typedef struct s_rgb
{
	int		red;
	int		green;
	int		blue;
}	t_rgb;

typedef struct s_textures
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	mlx_texture_t			*no_path;
	mlx_texture_t			*so_path;
	mlx_texture_t			*we_path;
	mlx_texture_t			*ea_path;
}	t_textures;

typedef struct s_player {
    double x;
    double y;
    int move_up;
    int move_down;
    int move_left;
    int move_right;
	int rotate_left;
	int rotate_right;
} t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;  // ADD THIS - perpendicular distance (corrected)
	double	hit_x;           // ADD THIS - exact hit position on wall
	double	hit_y;  
}	t_ray;

typedef struct s_config
{
	char		**map;
	t_textures	*txt;
	t_rgb		*floor_color;
	t_rgb		*ceiling_color;
	int			pos_x;
	int			pos_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	mlx_t		*mlx;
    mlx_image_t	*img;   
	t_player	player;
	t_ray		*rays;
    int			num_rays;
	uint32_t 	color;
	
}	t_config;

#endif