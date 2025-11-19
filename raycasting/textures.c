/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:13:08 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/19 11:08:05 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	load_texture(mlx_texture_t **texture, const char *path)
{
	if (!path || path[0] == '\0')
		return (0);
	*texture = mlx_load_png(path);
	if (!(*texture))
		return (0);
	return (1);
}

int	load_all_textures(t_config *cfg)
{
	int	err;

	if (!cfg || !cfg->txt)
		return (0);
	err = 0;
	if (!load_texture(&cfg->txt->no_path, cfg->txt->no_texture))
		err++;
	if (!load_texture(&cfg->txt->so_path, cfg->txt->so_texture))
		err++;
	if (!load_texture(&cfg->txt->we_path, cfg->txt->we_texture))
		err++;
	if (!load_texture(&cfg->txt->ea_path, cfg->txt->ea_texture))
		err++;
	if (err > 0)
		return (0);
	return (1);
}

int	unload_all_textures(t_config *cfg)
{
	if (!cfg || !cfg->txt)
		return (0);
	if (cfg->txt->no_path)
	{
		mlx_delete_texture((mlx_texture_t *)cfg->txt->no_path);
		cfg->txt->no_path = NULL;
	}
	if (cfg->txt->so_path)
	{
		mlx_delete_texture((mlx_texture_t *)cfg->txt->so_path);
		cfg->txt->so_path = NULL;
	}
	if (cfg->txt->we_path)
	{
		mlx_delete_texture((mlx_texture_t *)cfg->txt->we_path);
		cfg->txt->we_path = NULL;
	}
	if (cfg->txt->ea_path)
	{
		mlx_delete_texture((mlx_texture_t *)cfg->txt->ea_path);
		cfg->txt->ea_path = NULL;
	}
	return (1);
}
