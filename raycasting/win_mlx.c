/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:44:36 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/19 11:18:52 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static mlx_texture_t	*select_texture(t_config *cfg, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (cfg->txt->ea_path);
		return (cfg->txt->we_path);
	}
	if (ray->step_y > 0)
		return (cfg->txt->so_path);
	return (cfg->txt->no_path);
}

static void	calc_texture_pos(t_ray *ray, mlx_texture_t *tex, int start,
			double *tex_pos_step)
{
	double	tex_step;
	double	wall_x;
	double	line_h;
	double	d_calc;

	d_calc = ray->perp_wall_dist;
	if (d_calc < 0.1)
		d_calc = 0.1;
	line_h = (double)WIN_H / d_calc;
	if (ray->side == 0)
		wall_x = ray->hit_y;
	else
		wall_x = ray->hit_x;
	wall_x -= floor(wall_x);
	tex_pos_step[0] = (int)(wall_x * tex->width);
	tex_step = (double)tex->height / line_h;
	tex_pos_step[1] = (start - (-line_h / 2 + WIN_H / 2)) * tex_step;
	tex_pos_step[2] = tex_step;
}

int	draw_vertical_line(t_config *cfg, int x, int start, int end, t_ray *r)
{
	mlx_texture_t	*tex;
	uint8_t			*p;
	uint32_t		col;
	double			tinfo[3];
	int				ty;

	tex = select_texture(cfg, r);
	if (!tex || !tex->pixels)
		return (0);
	calc_texture_pos(r, tex, start, tinfo);
	if ((r->side == 0 && r->step_x > 0) || (r->side == 1 && r->step_y < 0))
		tinfo[0] = tex->width - (int)tinfo[0] - 1;
	while (start <= end)
	{
		ty = (int)tinfo[1];
		if (ty < 0)
			ty = 0;
		if (ty >= (int)tex->height)
			ty = tex->height - 1;
		p = tex->pixels + (ty * tex->width + (int)tinfo[0]) * 4;
		col = ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16)
			| ((uint32_t)p[2] << 8) | p[3];
		mlx_put_pixel(cfg->img, x, start, col);
		tinfo[1] += tinfo[2];
		start++;
	}
	return (1);
}

int	init_mlx(t_config *cfg)
{
	cfg->mlx = mlx_init(WIN_W, WIN_H, "Cub3D", true);
	if (!cfg->mlx)
		return (0);
	cfg->img = mlx_new_image(cfg->mlx, WIN_W, WIN_H);
	if (!cfg->img)
	{
		mlx_terminate(cfg->mlx);
		return (0);
	}
	return (1);
}
