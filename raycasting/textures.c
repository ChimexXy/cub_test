/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:13:08 by mozahnou          #+#    #+#             */
/*   Updated: 2025/11/17 10:33:47 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"


int	load_texture(mlx_texture_t **texture, const char *path)
{
	if (!path || path[0] == '\0')
	{
		printf("Error: Texture path is NULL or empty\n");
		return (0);
	}
	
	*texture = mlx_load_png(path);
	
	if (!(*texture))
	{
		printf("Error: Failed to load texture from: %s\n", path);
		return (0);
	}
	
	printf("✓ Successfully loaded: %s (%dx%d)\n", 
		path, (*texture)->width, (*texture)->height);
	
	return (1);
}


// ===== Load all 4 textures =====
void	load_all_textures(t_config *cfg)
{
	int	error_count;

	if (!cfg || !cfg->txt)
	{
		printf("Error: cfg or txt structure not initialized\n");
		return ;
	}

	error_count = 0;
	
	printf("\n=== Loading Textures ===\n");
	
	// Load North texture
	if (!load_texture(&cfg->txt->no_path, cfg->txt->no_texture))
		error_count++;
	
	// Load South texture
	if (!load_texture(&cfg->txt->so_path, cfg->txt->so_texture))
		error_count++;
	
	// Load West texture
	if (!load_texture(&cfg->txt->we_path, cfg->txt->we_texture))
		error_count++;
	
	// Load East texture
	if (!load_texture(&cfg->txt->ea_path, cfg->txt->ea_texture))
		error_count++;
	
	printf("======================\n\n");
	
	if (error_count > 0)
	{
		printf("⚠ WARNING: %d texture(s) failed to load!\n", error_count);
		exit(1);
	}
	else
		printf("✓ All textures loaded successfully!\n");
}

// ===== Unload all textures (cleanup) =====
void	unload_all_textures(t_config *cfg)
{
	if (!cfg || !cfg->txt)
		return ;
	
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
	
	printf("✓ All textures unloaded\n");
}
