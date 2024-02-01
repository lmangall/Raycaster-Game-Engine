#include "cub3d.h"

void	error_exit(char *error_message, t_data *data)
{
	(void)data;
	printf("Error\n");
	printf("%s\n", error_message);
	// free whatever was allocated before
	exit(EXIT_FAILURE);
}
