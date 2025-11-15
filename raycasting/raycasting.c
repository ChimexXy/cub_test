/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:41:36 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/15 01:49:37 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	perform_dda(t_config *cfg, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		hit = check_hit(cfg, ray);
	}
}

double	calc_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		return (ray->side_dist_x - ray->delta_dist_x);
	else
		return (ray->side_dist_y - ray->delta_dist_y);
}

void	calc_draw_bounds(double wall_dist, int *start, int *end)
{
	int	line_height;

	// Prevent division by zero or very small distances
	if (wall_dist < 0.1)
		wall_dist = 0.1;
	
	line_height = (int)(WIN_H / wall_dist);
	*start = -line_height / 2 + WIN_H / 2;
	*end = line_height / 2 + WIN_H / 2;
	
	// Clamp to screen bounds
	if (*start < 0)
		*start = 0;
	if (*end >= WIN_H)
		*end = WIN_H - 1;
}

void	cast_single_ray(t_config *cfg, int x)
{
	t_ray		ray;
	double		wall_dist;
	int			draw_start;
	int			draw_end;

	init_ray_direction(cfg, x, &ray);
	init_delta_dist(&ray);
	init_step_x(cfg, &ray);
	init_step_y(cfg, &ray);
	perform_dda(cfg, &ray);
	wall_dist = calc_wall_dist(&ray);
	calc_wall_x(cfg, &ray, wall_dist);
	ray.tex_num = get_texture_num(&ray);
	calc_draw_bounds(wall_dist, &draw_start, &draw_end);
	draw_floor_ceiling(cfg, x, draw_start, draw_end);
	draw_textured_line(cfg, &ray, x, draw_start, draw_end);  // CHANGE THIS LINE
}

void	raycasting(t_config *cfg)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		cast_single_ray(cfg, x);
		x++;
	}
}
