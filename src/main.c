/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:31 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/14 09:27:01 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this  function replace a single "0" in the map by a "2"
// it replace the 8th character on the 4th line
static void	add_2_map(t_data *data)
{
	if (data->map->grid[4][8] == '0')
		data->map->grid[4][8] = '2';
}

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
	add_2_map(data);
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
