/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:31 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/17 16:37:20 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_mode	mode;
	t_debug	debug;

	mode = FULL_EXPERIENCE;
	debug = OFF;
	data = ft_calloc(1, sizeof(t_data));
	init_data_parser(data);
	data->debug = debug;
	parser(argc, argv, data);
	if (mode == PARSE_ONLY)
		free_exit_parser(data, "Chill! Parsing only mode is on!");
	init_data(data);
	mlx_loop_hook(data->mlx, &key_hook, data);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, &raycasting, data);
	mlx_loop_hook(data->mlx, &render_minimap, data);
	mlx_loop(data->mlx);
	free_exit(data);
	return (0);
}
