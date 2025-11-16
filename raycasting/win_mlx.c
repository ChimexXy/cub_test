/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:44:36 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/16 13:27:07 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void draw_vertical_line(t_config *cfg, int x, int start, int end, t_ray *ray, double wall_dist __attribute__((unused)))
{
    int tex_x, tex_y;
    double wall_x; /* fractional coordinate [0..1] along the wall */
    mlx_texture_t *texture = NULL;
    int tex_w, tex_h;
    double line_height;
    double step;
    double tex_pos;
    uint8_t *pixels;
    uint32_t color;

    /* 1) choose texture pointer correctly (use your loaded mlx_texture_t * fields) */
    if (ray->side == 0) /* vertical wall: select East or West */
    {
        /* when ray.step_x > 0 it went to increasing x — that usually means
           we hit the WEST face (tile to the right) or you may invert depending on map convention.
           Adjust if visually inverted. */
        if (ray->step_x > 0)
            texture = cfg->txt->ea_path; /* east texture pointer — match your loader */
        else
            texture = cfg->txt->we_path;
    }
    else /* horizontal wall: North or South */
    {
        if (ray->step_y > 0)
            texture = cfg->txt->so_path;
        else
            texture = cfg->txt->no_path;
    }

    /* fallback if texture missing */
    if (!texture || !texture->pixels)
    {
        color = 0xFF00FFFF; /* magenta debug */
        for (int y = start; y <= end; ++y)
            mlx_put_pixel(cfg->img, x, y, color);
        return;
    }

    tex_w = texture->width;
    tex_h = texture->height;
    pixels = texture->pixels; /* RGBA bytes */

    /* 2) Compute fractional wall_x from exact hit point (no fmod of uninitialized fields) */
    if (ray->side == 0)
        wall_x = ray->hit_y; /* for vertical wall use world Y coordinate */
    else
        wall_x = ray->hit_x; /* for horizontal wall use world X coordinate */

    wall_x -= floor(wall_x); /* keep fractional part between 0..1 */

    /* 3) tex_x and flip rules */
    tex_x = (int)(wall_x * (double)tex_w);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex_w) tex_x = tex_w - 1;

    /* flip horizontally when needed so texture orientation matches face */
    if ((ray->side == 0 && ray->step_x > 0) || (ray->side == 1 && ray->step_y < 0))
        tex_x = tex_w - tex_x - 1;

    /* 4) vertical sampling: compute step and initial tex_pos */
    line_height = (double)(end - start + 1);
    if (line_height <= 0) line_height = 1.0;
    step = (double)tex_h / line_height;
    tex_pos = (start - (WIN_H / 2.0) + line_height / 2.0) * step;

    /* 5) draw loop */
    for (int y = start; y <= end; ++y)
    {
        tex_y = (int)tex_pos;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= tex_h) tex_y = tex_h - 1;
        tex_pos += step;

        uint8_t *p = pixels + (tex_y * tex_w + tex_x) * 4;
        uint8_t r = p[0], g = p[1], b = p[2], a = p[3];
        /* pack into 0xRRGGBBAA for MLX42 */
        color = ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;

        mlx_put_pixel(cfg->img, x, y, color);
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
