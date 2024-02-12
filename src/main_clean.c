/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:31 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/12 08:52:06 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_hook(void *tmp)
{
	int32_t	return_value;
	t_data	*data;
	void	*old_image;
	void	*old_minimap;

	(void)return_value;
	data = (t_data *)tmp;
	old_image = data->image;
	old_minimap = data->minimap;
	data->image = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	raycasting(data);
	minimap(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	return_valmlx_image_to_window(data->mlx, data->minimap, 50, 50);
	if (old_image)
		mlx_delete_image(data->mlx, old_image);
	if (old_minimap)
		mlx_delete_image(data->mlx, old_minimap);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:31 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 15:25:54 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_hook(void *tmp)
{
	t_data		*data;

	data = (t_data *)tmp;
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	if (data->minimap->image)
		mlx_delete_image(data->mlx, data->minimap->image);
	data->image = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->minimap->image = mlx_new_image(data->mlx, data->minimap->width,
			data->minimap->height);
	if (data->minimap->image == NULL)
		return ;
	raycasting(data);
	render_minimap(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap->image, data->minimap->offset_x,
		data->minimap->offset_y);
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
	data->debug = debug;
	parser(argc, argv, data);
	if (mode == PARSE_ONLY)
		free_exit_parser(data, "Chill! Parsing only mode is on!");
	init_data(data);
	render_background(data->mlx, data->map->c, data->map->f, data);
	mlx_loop_hook(data->mlx, &key_hook, data);
	mlx_loop_hook(data->mlx, &game_hook, data);
	mlx_loop(data->mlx);
	free_exit(data);
	return (0);
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
	data->debug = debug;
	parser(argc, argv, data);
	if (mode == PARSE_ONLY)
		free_exit_parser(data, "Chill! Parsing only mode is on!");
	init_data(data);
	render_background(data->mlx, data->map->c, data->map->f, data);
	mlx_loop_hook(data->mlx, &key_hook, data);
	mlx_loop_hook(data->mlx, &game_hook, data);
	mlx_loop(data->mlx);
	free_exit(data);
	return (0);
}
