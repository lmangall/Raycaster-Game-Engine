/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prints_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:39:47 by slombard          #+#    #+#             */
/*   Updated: 2024/02/05 15:39:48 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	print_texture_paths(t_textures_paths *textures_paths)
{
	ft_printf("The saved texture paths are:\n");
	ft_printf("textures_paths->north: %s\n", textures_paths->north);
	ft_printf("textures_paths->south: %s\n", textures_paths->south);
	ft_printf("textures_paths->west: %s\n", textures_paths->west);
	ft_printf("textures_paths->east: %s\n", textures_paths->east);
}

void	print_elements_status(t_map_elements_check *elements)
{
	if (elements->no == NOT_FOUND)
		ft_printf("NO : NOT_FOUND\n");
	else
		ft_printf("NO : FOUND\n");
	if (elements->so == NOT_FOUND)
		ft_printf("SO : NOT_FOUND\n");
	else
		ft_printf("SO : FOUND\n");
	if (elements->we == NOT_FOUND)
		ft_printf("WE: NOT FOUND\n");
	else
		ft_printf("WE: FOUND\n");
	if (elements->ea == NOT_FOUND)
		ft_printf("EA: NOT FOUND\n");
	else
		ft_printf("EA: FOUND\n");
	if (elements->c == NOT_FOUND)
		ft_printf("C: NOT FOUND\n");
	else
		ft_printf("C: FOUND\n");
	if (elements->f == NOT_FOUND)
		ft_printf("F: NOT FOUND\n");
	else
		ft_printf("F: FOUND\n");
}

void	print_ceiling_and_floor(t_rgba *c, t_rgba *f)
{
	ft_printf("The saved ceiling and floor colors are:\n");
	ft_printf("C: %d, %d, %d, %d\n", c->r, c->g, c->b, c->a);
	ft_printf("F: %d, %d, %d, %d\n", f->r, f->g, f->b, f->a);
}

void	print_map_elements(t_data *data)
{
	ft_printf("Processing map elements done.\n");
	ft_printf("The correct number of map elements have been found.\n");
	print_texture_paths(data->map->textures_paths);
	print_ceiling_and_floor(&data->map->c, &data->map->f);
}
