#include "cub3d.h"
#include "parser.h"

t_textures_paths	*init_textures_paths(void)
{
	t_textures_paths	*textures_paths;

	textures_paths = ft_calloc(1, sizeof(t_textures_paths));
	textures_paths->north = NULL;
	textures_paths->south = NULL;
	textures_paths->west = NULL;
	textures_paths->east = NULL;
	return (textures_paths);
}

void	init_map(t_map *map)
{
	t_textures_paths	*textures_paths;

	textures_paths = NULL;
	textures_paths = init_textures_paths();
	map->textures_paths = textures_paths;
	// Initialize integer members to 0
	map->p_x = 0;
	map->p_y = 0;
	map->width = 0;
	map->height = 0;
	// Initialize player_orientation to 0 or another default value as appropriate for your application
	map->player_orientation = '0';
	// Initialize the player_found flag to NOT_FOUND
	map->player_found = NOT_FOUND;
	// Initialize grid pointer to NULL (assuming it will be dynamically allocated later)
	map->grid = NULL;
	// Initialize RGBA components of c and f to 0
	map->c.r = 0;
	map->c.g = 0;
	map->c.b = 0;
	map->c.a = 0;
	// Set alpha to 0 or another default value as appropriate for your application
	map->f.r = 0;
	map->f.g = 0;
	map->f.b = 0;
	map->f.a = 0;
	// Set alpha to 0 or another default value as appropriate for your application
}

void	init_elements_status(t_map_elements *elements)
{
	elements->no = NOT_FOUND;
	elements->so = NOT_FOUND;
	elements->we = NOT_FOUND;
	elements->ea = NOT_FOUND;
	elements->c = NOT_FOUND;
	elements->f = NOT_FOUND;
}
