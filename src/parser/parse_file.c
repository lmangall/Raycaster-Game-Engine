/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:46:30 by slombard          #+#    #+#             */
/*   Updated: 2024/02/02 02:04:00 by slombard         ###   ########.fr       */
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

void	remove_newline_char(char *line)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
}

void	eventual_resize(t_build_lines_arr_data *blad)
{
	char	**tmp;

	if (*blad->lines_nbr == *blad->lines_arr_size)
	{
		*blad->lines_arr_size *= 2;
		tmp = handle_ft_easy_realloc(*blad->lines_arr, *blad->lines_arr_size / 2
			* sizeof(char *), (*blad->lines_arr_size + 1) * sizeof(char *),
			blad->fd);
		tmp[*blad->lines_arr_size] = NULL;
		blad->lines_arr = &tmp;
	}
	blad->lines_arr[*blad->lines_nbr] = &blad->line;
	(*blad->lines_nbr)++;
}

char	**build_lines_arr(t_build_lines_arr_data *blad)
{
	blad->lines_arr = handle_ft_calloc(blad->lines_arr_size, blad->fd);
	blad->line = get_next_line(blad->fd);
	while (blad->line)
	{
		remove_newline_char(blad->line);
		eventual_resize(blad);
		blad->line = get_next_line(blad->fd);
	}
	blad->lines_arr[*blad->lines_nbr] = NULL;
	if (*blad->lines_nbr == 0)
	{
		free_str_arr(*blad->lines_arr);
		error_exit("Empty file");
	}
	close(blad->fd);
	return (*blad->lines_arr);
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
	t_build_lines_arr_data	*blad;

	// size_t					lines_arr_size;
	blad = ft_calloc(1, sizeof(t_build_lines_arr_data));
	blad->fd = 0;
	blad->lines_arr = lines_arr;
	blad->lines_nbr = 0;
	*blad->lines_arr_size = 10;
	open_and_check_file(file_path, &blad->fd);
	*blad->lines_arr = build_lines_arr(blad);
	close(blad->fd);
	*lines_arr = resize_lines_arr(*blad->lines_arr, *blad->lines_arr_size,
		*blad->lines_nbr);
}
