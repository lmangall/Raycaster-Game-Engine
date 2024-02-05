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
