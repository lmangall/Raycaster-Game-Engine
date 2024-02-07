/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:46:30 by slombard          #+#    #+#             */
/*   Updated: 2024/02/07 15:20:11 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	check_file_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		error_exit("Invalid file extension: it should be a .cub extension!");
}

void	open_and_check_file(char *file_path, int *fd)
{
	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
		error_exit(ERROR_OPENING_FILE);
	check_file_extension(file_path);
}

typedef struct build_lines_arr_vars
{
	char	*line;
	char	**lines_arr;
	char	**tmp;
	size_t	line_len;
}			t_build_lines_arr_vars;

char	**build_lines_arr(int fd, size_t *lines_arr_size, size_t *lines_nbr)
{
	t_build_lines_arr_vars	vars;

	vars.lines_arr = handle_ft_calloc(lines_arr_size, fd);
	vars.line = get_next_line(fd);
	while ((vars.line))
	{
		vars.line_len = ft_strlen(vars.line);
		remove_new_line(vars.line);
		if (*lines_nbr == *lines_arr_size)
		{
			*lines_arr_size *= 2;
			vars.tmp = handle_ft_easy_realloc(vars.lines_arr, *lines_arr_size
					/ 2 * sizeof(char *), (*lines_arr_size + 1)
					* sizeof(char *), fd);
			vars.tmp[*lines_arr_size] = NULL;
			vars.lines_arr = vars.tmp;
		}
		vars.lines_arr[*lines_nbr] = vars.line;
		(*lines_nbr)++;
		vars.line = get_next_line(fd);
	}
	vars.lines_arr[*lines_nbr] = NULL;
	handle_empty_map(vars.lines_arr, *lines_nbr);
	close(fd);
	return (vars.lines_arr);
}

char	**resize_lines_arr(char **lines_arr, size_t lines_arr_size,
		size_t lines_nbr)
{
	char	**tmp;

	tmp = ft_easy_realloc(lines_arr, lines_arr_size * sizeof(char *), (lines_nbr
				+ 1) * sizeof(char *));
	if (!tmp)
		free_lines_arr_and_exit(lines_arr, "Malloc failed");
	lines_arr = tmp;
	lines_arr[lines_nbr] = NULL;
	return (lines_arr);
}

void	parse_file(char *file_path, char ***lines_arr)
{
	int		fd;
	size_t	lines_arr_size;
	size_t	lines_nbr;

	open_and_check_file(file_path, &fd);
	lines_nbr = 0;
	lines_arr_size = 10;
	*lines_arr = build_lines_arr(fd, &lines_arr_size, &lines_nbr);
	close(fd);
	*lines_arr = resize_lines_arr(*lines_arr, lines_arr_size, lines_nbr);
}
