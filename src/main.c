/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:31 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 15:21:16 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_hook(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

// place render_background somewhere else ?
int	main(int argc, char **argv)
{
	t_data	*data;
	t_mode	mode;
	t_debug	debug;

	mode = FULL_EXPERIENCE;
	debug = OFF;
	data = ft_calloc(1, sizeof(t_data));
	init_data_parser(data);
	// debug = ALL;
	data->debug = debug;
	parser(argc, argv, data);
	if (mode == PARSE_ONLY)
		free_exit_parser(data, "Chill! Parsing only mode is on!");
	init_data(data);
	render_background(data->mlx, data->map->c, data->map->f);
	mlx_loop_hook(data->mlx, &key_hook, data);
	mlx_loop_hook(data->mlx, &game_hook, data);
	mlx_loop(data->mlx);
	free_exit(data);
	return (0);
}
