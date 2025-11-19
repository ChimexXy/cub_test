/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:17:52 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/11/19 11:01:57 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "./raycasting/raycasting.h"

void ll()
{
	system("leaks -q cub3d");
}
int	main(int ac, char **av)
{
	t_config	config;

	atexit(ll);
	if (ac != 2 || !handle_format(av[1], ".cub"))
		return (p_error("Argument not valid\n"), 0);
	if (!is_valid_map(&config, av[1]))
		return (1);
	if (!render_2d_map(&config))
		return (1);
	return (0);
}
