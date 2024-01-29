#include "cub3d.h"

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

char	**parse_file(char *file_path)
{
	int		fd;
	char	*line;
	char	**lines_arr;
	size_t	lines_nbr;
	size_t	capacity;
	char	**tmp;
	size_t	i;

	printf("Parsing file...\n");
	lines_nbr = 0;
	capacity = 10;
	i = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (NULL);
	}
	lines_arr = malloc(capacity * sizeof(char *));
	if (!lines_arr)
	{
		close(fd);
		return (NULL);
	}
	while ((line = get_next_line(fd)))
	{
		// printf("line: %s\n", line);
		if (lines_nbr == capacity)
		{
			// printf("Reallocating...\n");
			// printf("capacity: %zu\n", capacity);
			// printf("lines_nbr: %zu\n", lines_nbr);
			capacity *= 2;
			tmp = ft_easy_realloc(lines_arr, (capacity / 2) * sizeof(char *),
				capacity * sizeof(char *));
			if (!tmp)
			{
				while (i < lines_nbr)
				{
					free(lines_arr[i]);
					i++;
				}
				free(lines_arr);
				close(fd);
				// We can exit here.
				return (NULL);
			}
			lines_arr = tmp;
		}
		lines_arr[lines_nbr++] = line;
		// printf("lines_nbr: %zu\n", lines_nbr);
		// printf("lines_arr[%zu]: %s\n", lines_nbr - 1, lines_arr[lines_nbr
		// - 1]);
	}
	close(fd);
	// printf("capacity: %zu\n", capacity);
	// printf("lines_nbr: %zu\n", lines_nbr);
	tmp = ft_easy_realloc(lines_arr, capacity * sizeof(char *), (lines_nbr + 1)
		* sizeof(char *));
	if (!tmp)
	{
		for (size_t i = 0; i < lines_nbr; i++)
			free(lines_arr[i]);
		free(lines_arr);
		return (NULL);
	}
	lines_arr = tmp;
	lines_arr[lines_nbr] = NULL;
	// printf("lines_nbr: %zu\n", lines_nbr);
	// printf("last line before NULL: lines_arr[%zu]: %s\n", lines_nbr,
	// 	lines_arr[lines_nbr - 1]);
	// printf("Printing lines_arr before exiting...\n");
	// i = 0;
	// printf("printing pointers...\n");
	// while (lines_arr[i] != NULL)
	// {
	// 	printf("%p\n", lines_arr[i]);
	// 	i++;
	// }
	// i = 0;
	// while (lines_arr[i] != NULL)
	// {
	// 	if (lines_arr[i][0] == '\0')
	// 		printf("Empty line\n");
	// 	else
	// 		printf("%s\n", lines_arr[i]);
	// 	i++;
	// }
	// printf("Exiting parse_file...\n");
	return (lines_arr);
}
