/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:39:26 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/19 11:07:42 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	update_player_position(t_config *cfg)
{
	double	nx;
	double	ny;

	nx = cfg->player.x;
	ny = cfg->player.y;
	apply_rotation(cfg);
	apply_movement(cfg, &nx, &ny);
	if (!is_wall(cfg, nx, cfg->player.y))
		cfg->player.x = nx;
	if (!is_wall(cfg, cfg->player.x, ny))
		cfg->player.y = ny;
}

int	render_2d_map(t_config *cfg)
{
	if (!init_mlx(cfg))
		return (0);
	if (!load_all_textures(cfg))
		return (0);
	mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);
	init_player_flags(cfg);
	set_player_position(cfg);
	mlx_key_hook(cfg->mlx, &handle_keys, cfg);
	if (!mlx_loop_hook(cfg->mlx, &render_frame, cfg))
		return (0);
	mlx_loop(cfg->mlx);
	if (!unload_all_textures(cfg))
		return (0);
	mlx_terminate(cfg->mlx);
	return (1);
}

void	render_frame(void *param)
{
	t_config	*cfg;

	cfg = (t_config *)param;
	ft_memset(cfg->img->pixels, 0,
		cfg->img->width * cfg->img->height * sizeof(uint32_t));
	draw_floor_ceiling(cfg);
	update_player_position(cfg);
	raycasting(cfg);
}
