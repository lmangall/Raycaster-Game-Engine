#include "cub3d.h"

void	check_file_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		error_exit("Invalid file extension: it should be a .cub extension!",
			NULL);
}
void	check_file(char *map_file)
{
	check_file_extension(map_file);
}