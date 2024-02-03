#include "cub3d.h"

int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		error_exit(ERROR_OPENING_FILE, NULL);
	return (fd);
}

void	check_file_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		error_exit("Invalid file extension: it should be a .cub extension!",
			NULL);
}
void	open_and_check_file(char *file_path, int *fd)
{
	*fd = open_file(file_path);
	check_file_extension(file_path);
}