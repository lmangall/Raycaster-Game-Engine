/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:59 by slombard          #+#    #+#             */
/*   Updated: 2024/02/07 15:18:06 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	free_str_arr(char **str_arr)
// {
// 	int	i;

// 	i = 0;
// 	if (str_arr == NULL)
// 		return ;
// 	while (str_arr[i] != NULL)
// 	{
// 		free(str_arr[i]);
// 		str_arr[i] = NULL;
// 		i++;
// 	}
// 	free(str_arr);
// 	str_arr = NULL;
// }

void	error_exit(char *error_message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error_message);
	exit(EXIT_FAILURE);
}

// void	free_textures_paths(t_textures_paths *textures_paths)
// {
// 	if (textures_paths == NULL)
// 		return ;
// 	if (textures_paths->north != NULL)
// 	{
// 		free(textures_paths->north);
// 		textures_paths->north = NULL;
// 	}
// 	if (textures_paths->south != NULL)
// 	{
// 		free(textures_paths->south);
// 		textures_paths->south = NULL;
// 	}
// 	if (textures_paths->west != NULL)
// 	{
// 		free(textures_paths->west);
// 		textures_paths->west = NULL;
// 	}
// 	if (textures_paths->east != NULL)
// 	{
// 		free(textures_paths->east);
// 		textures_paths->east = NULL;
// 	}
// 	free(textures_paths);
// }

// void	free_exit_parser(t_data *data, char *error_message)
// {
// 	int	i;

// 	if (data->map->lines_arr != NULL)
// 		free_str_arr(data->map->lines_arr);
// 	if (data->map->grid != NULL)
// 	{
// 		i = 0;
// 		while (data->map->grid[i] && data->map->height > 0)
// 		{
// 			free(data->map->grid[i]);
// 			data->map->grid[i] = NULL;
// 			i++;
// 		}
// 		free(data->map->grid);
// 		data->map->grid = NULL;
// 	}
// 	free_textures_paths(data->map->textures_paths);
// 	if (data->map)
// 	{
// 		free(data->map);
// 		data->map = NULL;
// 	}
// 	free(data);
// 	data = NULL;
// 	error_exit(error_message);
// }
