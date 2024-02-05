/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:00 by slombard          #+#    #+#             */
/*   Updated: 2024/02/05 15:40:01 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	print_lines_arr(char **lines_arr)
{
	int	i;

	printf("Printing lines_arr...\n");
	if (lines_arr == NULL)
	{
		printf("No lines to print.\n");
		return ;
	}
	i = 0;
	while (lines_arr[i] != NULL)
	{
		printf("%s\n", lines_arr[i]);
		i++;
	}
}

void	print_map_grid(char **str_arri, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		ft_printf("%s\n", str_arri[i]);
		i++;
	}
}

void	print_map_final(t_data *data)
{
	print_texture_paths(data->map->textures_paths);
	print_ceiling_and_floor(&data->map->c, &data->map->f);
	ft_printf("Parsing is complete!\n");
	if (data->map->player_found == FOUND)
		ft_printf("We have only one player\n");
	ft_printf("The position of the player is: %d, %d\n", data->map->p_x,
		data->map->p_y);
	ft_printf("The orientation of the player is: %c\n",
		data->map->player_orientation);
	ft_printf("The map width is: %d\n", data->map->width);
	ft_printf("The map height is: %d\n", data->map->height);
	ft_printf("The map grid is:\n");
	print_map_grid(data->map->grid, data->map->height);
}
