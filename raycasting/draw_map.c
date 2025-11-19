/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:38:08 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/19 11:38:47 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	set_player_position(t_config *cfg)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	x = 0;
	while (cfg->map[y])
	{
		x = 0;
		while (cfg->map[y][x])
		{
			c = cfg->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				cfg->player.x = (double)x + 0.3;
				cfg->player.y = (double)y + 0.3;
				init_player_direction(cfg, c); 
				return ;
			}
			x++;
		}
		y++;
	}
}

void	draw_player(t_config *cfg)
{
	t_norm	*norm;

	norm = NULL;
	norm->y = 0;
	norm->size = CELL / 3;
	norm->px = (int)(cfg->player.x * CELL);
	norm->py = (int)(cfg->player.y * CELL);
	norm->start_x = norm->px - (norm->size / 2);
	norm->start_y = norm->py - (norm->size / 2);
	while (norm->y < norm->size)
	{
		norm->x = 0;
		while (norm->x < norm->size)
		{
			mlx_put_pixel(cfg->img, (uint32_t)(norm->start_x + norm->x),
				(uint32_t)(norm->start_y + norm->y), 0xFF0000FF);
			norm->x++;
		}
		norm->y++;
	}
}

void	draw_map(t_config *cfg)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (cfg->map[y])
	{
		x = 0;
		while (cfg->map[y][x])
		{
			c = cfg->map[y][x];
			x++;
		}
		y++;
	}
}
