#include "cub3d.h"
#include "parser.h"

void	init_map(t_map *map)
{
	if (map == NULL)
	{
		return ; // Handle null pointer if necessary
	}
	// Initialize integer members to 0
	map->p_x = 0;
	map->p_y = 0;
	map->w_map = 0;
	map->h_map = 0;
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

void	init_textures_paths(t_textures_paths *textures_paths)
{
	if (textures_paths == NULL)
	{
		return ; // Handle null pointer if necessary
	}

	// Initialize texture path pointers to NULL
	textures_paths->north = NULL;
	textures_paths->south = NULL;
	textures_paths->west = NULL;
	textures_paths->east = NULL;

	// If you have defaultk texture paths, you can initialize them here
	// For example:
	// textures_paths->north = strdup("default_north_texture_path");
	// ... and so on for south, west, east
	// Make sure to free these strings later if they are dynamically allocated
}