/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 01:02:27 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/15 20:14:31 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void ft_putstr_fd(char *s, int fd)
{
	int i = 0;
	while(s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	load_single_texture(mlx_texture_t **tex, char *path)
{
	printf("<%s>\n", path);
	*tex = mlx_load_png(path);
	if (!*tex)
	{
		ft_putstr_fd("Error: Failed to load texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

int	load_textures(t_config *cfg)
{
	if (!load_single_texture(&cfg->textures.north,
			cfg->txt->no_texture))
		return (0);
	if (!load_single_texture(&cfg->textures.south,
			cfg->txt->so_texture))
		return (0);
	if (!load_single_texture(&cfg->textures.west,
			cfg->txt->we_texture))
		return (0);
	if (!load_single_texture(&cfg->textures.east,
			cfg->txt->ea_texture))
		return (0);
	return (1);
}

void	free_textures(t_config *cfg)
{
	if (cfg->textures.north)
		mlx_delete_texture(cfg->textures.north);
	if (cfg->textures.south)
		mlx_delete_texture(cfg->textures.south);
	if (cfg->textures.west)
		mlx_delete_texture(cfg->textures.west);
	if (cfg->textures.east)
		mlx_delete_texture(cfg->textures.east);
}

int	get_texture_num(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->step_y > 0)
			return (2);
		else
			return (3);
	}
}

void	calc_wall_x(t_config *cfg, t_ray *ray, double wall_dist)
{
	if (ray->side == 0)
		ray->wall_x = cfg->player.y + wall_dist * ray->dir_y;
	else
		ray->wall_x = cfg->player.x + wall_dist * ray->dir_x;
	
	// Keep only fractional part
	ray->wall_x = ray->wall_x - floor(ray->wall_x);
}

mlx_texture_t	*get_texture(t_config *cfg, int tex_num)
{
	if (tex_num == 0)
		return (cfg->textures.east);
	else if (tex_num == 1)
		return (cfg->textures.west);
	else if (tex_num == 2)
		return (cfg->textures.south);
	else
		return (cfg->textures.north);
}

uint32_t	get_texture_color(mlx_texture_t *tex, int tex_x, int tex_y)
{
	uint8_t	*pixel;
	uint32_t	color;

	if (tex_x < 0 || tex_x >= (int)tex->width)
		tex_x = 0;
	if (tex_y < 0 || tex_y >= (int)tex->height)
		tex_y = 0;
	pixel = tex->pixels + (tex_y * tex->width + tex_x) * tex->bytes_per_pixel;
	color = ((uint32_t)pixel[0] << 24) | ((uint32_t)pixel[1] << 16)
		| ((uint32_t)pixel[2] << 8) | 0xFF;
	return (color);
}

void	calc_tex_x(t_ray *ray, mlx_texture_t *tex, int *tex_x)
{
	double	wall_x_temp;
	
	wall_x_temp = ray->wall_x;
	
	// Make sure wall_x is between 0 and 1
	wall_x_temp = wall_x_temp - floor(wall_x_temp);
	
	*tex_x = (int)(wall_x_temp * (double)tex->width);
	
	// Flip texture coordinate for certain sides to avoid mirroring
	if (ray->side == 0 && ray->dir_x < 0)
		*tex_x = tex->width - *tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		*tex_x = tex->width - *tex_x - 1;
	
	// Safety bounds check
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= (int)tex->width)
		*tex_x = tex->width - 1;
}
void	draw_textured_line(t_config *cfg, t_ray *ray, int x, int draw_start,
		int draw_end)
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				y;
	int				line_height;

	tex = get_texture(cfg, ray->tex_num);
	if (!tex)
		return;
	calc_tex_x(ray, tex, &tex_x);
	line_height = draw_end - draw_start;
	step = (double)tex->height / line_height;
	tex_pos = 0;
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos % tex->height;
		tex_pos += step;
		
		if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
			mlx_put_pixel(cfg->img, x, y, get_texture_color(tex, tex_x, tex_y));
		y++;
	}
}

uint32_t	rgb_to_color(t_rgb *rgb)
{
	return (((uint32_t)rgb->red << 24) | ((uint32_t)rgb->green << 16)
		| ((uint32_t)rgb->blue << 8) | 0xFF);
}

void	draw_floor_ceiling(t_config *cfg, int x, int draw_start, int draw_end)
{
	int			y;
	uint32_t	ceil_color;
	uint32_t	floor_color;

	ceil_color = rgb_to_color(cfg->ceiling_color);
	floor_color = rgb_to_color(cfg->floor_color);
	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(cfg->img, x, y, ceil_color);
		y++;
	}
	y = draw_end + 1;
	while (y < WIN_H)
	{
		mlx_put_pixel(cfg->img, x, y, floor_color);
		y++;
	}
}