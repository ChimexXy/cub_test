/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:44:36 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/16 12:34:43 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_vertical_line(t_config *cfg, int x, int start, int end, t_ray *ray, double wall_dist __attribute__((unused)))
{
	int				y;
	int				tex_x;
	int				tex_y;
	double			wall_x;
	mlx_texture_t	*texture;
	uint32_t		color;
	uint8_t			*pixel;

	y = start;
	
	// Determine which wall we hit and get texture
	if (ray->side == 0)  // Vertical wall (East or West)
	{
		wall_x = fmod(ray->hit_x, 1.0);
		if (wall_x < 0)
			wall_x += 1.0;
		
		if (ray->step_x > 0)
			texture = cfg->txt->ea_path;  // East
		else
			texture = cfg->txt->we_path;  // West
	}
	else  // Horizontal wall (North or South)
	{
		wall_x = fmod(ray->hit_y, 1.0);
		if (wall_x < 0)
			wall_x += 1.0;
		
		if (ray->step_y > 0)
			texture = cfg->txt->so_path;  // South
		else
			texture = cfg->txt->no_path;  // North
	}
	
	// Check if texture is loaded
	if (!texture || !texture->pixels)
	{
		cfg->color = 0xFF0000FF;  // Red for missing texture
		while (y <= end)
		{
			if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
				mlx_put_pixel(cfg->img, x, y, cfg->color);
			y++;
		}
		return ;
	}
	
	// Clamp tex_x value
	tex_x = (int)(wall_x * (texture->width - 1));
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	
	// Avoid division by zero
	if (end <= start)
		end = start + 1;
	
	while (y <= end)
	{
		if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		{
			// Calculate vertical position on texture
			tex_y = (int)(((y - start) / (double)(end - start + 1)) * (texture->height - 1));
			
			// Clamp tex_y
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= (int)texture->height)
				tex_y = texture->height - 1;
			
			// Get pixel from texture safely
			if (tex_x >= 0 && tex_x < (int)texture->width && 
			    tex_y >= 0 && tex_y < (int)texture->height)
			{
				pixel = texture->pixels + (tex_y * texture->width + tex_x) * 4;
				// Extract RGBA values from pixel data
				uint8_t r = pixel[0];
				uint8_t g = pixel[1];
				uint8_t b = pixel[2];
				uint8_t a = pixel[3];
				// Convert to MLX42 format (RGBA as uint32_t)
				color = (r << 24) | (g << 16) | (b << 8) | a;
				mlx_put_pixel(cfg->img, x, y, color);
			}
		}
		y++;
	}
}


int	init_mlx(t_config *cfg)
{
	cfg->mlx = mlx_init(WIN_W, WIN_H, "Cub3D", true);
	if (!cfg->mlx)
	{
		puts("Error: MLX init failed\n");
		return (0);
	}
	cfg->img = mlx_new_image(cfg->mlx, WIN_W, WIN_H);
	if (!cfg->img)
	{
		puts("Error: Image creation failed\n");
		mlx_terminate(cfg->mlx);
		return (0);
	}
	return (1);
}
