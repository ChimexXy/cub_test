/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:41:36 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/16 12:34:06 by mozahnou         ###   ########.fr       */
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

double	calc_wall_dist(t_config *cfg, t_ray *ray)
{
	double	raw_dist;
	double	camera_angle;
	double	ray_angle;
	double	angle_diff;

	// Calculate raw distance
	if (ray->side == 0)
		raw_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		raw_dist = ray->side_dist_y - ray->delta_dist_y;

	// Get camera angle (direction player is facing)
	camera_angle = atan2(cfg->dir_y, cfg->dir_x);
	
	// Get ray angle
	ray_angle = atan2(ray->dir_y, ray->dir_x);
	
	// Calculate angle difference
	angle_diff = ray_angle - camera_angle;
	
	// Normalize angle to [-PI, PI]
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	
	// Apply cosine correction to eliminate fisheye
	// This is the KEY fix - multiply by cos of angle difference
	ray->perp_wall_dist = raw_dist * cos(angle_diff);
	
	return (ray->perp_wall_dist);
}


void	calc_draw_bounds(double wall_dist, int *start, int *end)
{
	int	wall_height;

	if (wall_dist < 0.1)
		wall_dist = 0.1;
	
	wall_height = (int)(1080 / wall_dist);
	
	*start = (1080 - wall_height) / 2;
	*end = *start + wall_height;
	
	// Clamp to screen bounds
	if (*start < 0)
		*start = 0;
	if (*end >= 1080)
		*end = 1080 - 1;
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
	
	// Fixed distance with cosine correction
	wall_dist = calc_wall_dist(cfg, &ray);
	calc_draw_bounds(wall_dist, &draw_start, &draw_end);
	
	// Calculate hit position for texture mapping
	if (ray.side == 0)
	{
		ray.hit_x = cfg->player.y + wall_dist * ray.dir_y;
		ray.hit_y = ray.map_y * 1.0;
	}
	else
	{
		ray.hit_x = ray.map_x * 1.0;
		ray.hit_y = cfg->player.x + wall_dist * ray.dir_x;
	}
	
	// Draw wall with texture
	draw_vertical_line(cfg, x, draw_start, draw_end, &ray, wall_dist);
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
