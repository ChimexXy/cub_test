/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:51:30 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/19 02:21:59 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

uint32_t	rgb_to_color(t_rgb *color)
{
	uint32_t	result;

	if (!color)
		return (0x000000FF);
	result = ((uint32_t)color->red << 24) 
		| ((uint32_t)color->green << 16)
		| ((uint32_t)color->blue << 8) 
		| 0xFF;
	return (result);
}

void	draw_ceiling(t_config *cfg)
{
	int			y;
	int			x;
	uint32_t	ceiling_color;

	ceiling_color = rgb_to_color(cfg->ceiling_color);
	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			mlx_put_pixel(cfg->img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_config *cfg)
{
	int			y;
	int			x;
	uint32_t	floor_color;

	floor_color = rgb_to_color(cfg->floor_color);
	y = WIN_H / 2;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			mlx_put_pixel(cfg->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	draw_floor_ceiling(t_config *cfg)
{
	draw_ceiling(cfg);
	draw_floor(cfg);
}
