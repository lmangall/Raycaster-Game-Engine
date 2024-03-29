/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:19:29 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/18 19:22:53 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	if (str_arr == NULL)
		return ;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		str_arr[i] = NULL;
		i++;
	}
	free(str_arr);
	str_arr = NULL;
}

void	free_textures_paths(t_textures_paths *textures_paths)
{
	if (textures_paths == NULL)
		return ;
	if (textures_paths->north != NULL)
	{
		free(textures_paths->north);
		textures_paths->north = NULL;
	}
	if (textures_paths->south != NULL)
	{
		free(textures_paths->south);
		textures_paths->south = NULL;
	}
	if (textures_paths->west != NULL)
	{
		free(textures_paths->west);
		textures_paths->west = NULL;
	}
	if (textures_paths->east != NULL)
	{
		free(textures_paths->east);
		textures_paths->east = NULL;
	}
	free(textures_paths);
}

void	free_map_data(t_data *data)
{
	int	i;

	if (data->map)
	{
		if (data->map->lines_arr != NULL)
			free_str_arr(data->map->lines_arr);
		if (data->map->grid != NULL)
		{
			i = 0;
			while (data->map->grid[i] && data->map->height > 0)
			{
				free(data->map->grid[i]);
				data->map->grid[i] = NULL;
				i++;
			}
			free(data->map->grid);
			data->map->grid = NULL;
		}
		if (data->map->textures_paths != NULL)
			free_textures_paths(data->map->textures_paths);
		free(data->map);
		data->map = NULL;
	}
}

void	free_data(t_data *data)
{
	free_map_data(data);
	if (data->ray != NULL)
	{
		free(data->ray);
		data->ray = NULL;
	}
	if (data->player != NULL)
	{
		free(data->player);
		data->player = NULL;
	}
	if (data->textures != NULL)
		free_textures_mlx(data->textures);
	if (data->minimap != NULL)
	{
		free(data->minimap);
		data->minimap = NULL;
	}
	free(data);
	data = NULL;
}

void	free_exit_parser(t_data *data, char *error_message)
{
	free_data(data);
	if (error_message != NULL)
		error_exit(error_message);
	exit(0);
}
