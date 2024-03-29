/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:47:36 by slombard          #+#    #+#             */
/*   Updated: 2024/01/31 18:47:37 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	free_lines_arr_and_exit(char **lines_arr, char *error_message)
{
	int	i;

	i = 0;
	while (lines_arr[i] != NULL)
	{
		free(lines_arr[i]);
		lines_arr[i] = NULL;
		i++;
	}
	free(lines_arr);
	lines_arr = NULL;
	error_exit(error_message);
}

void	*handle_ft_calloc(size_t *lines_arr_size, int fd)
{
	char	**lines_arr;

	lines_arr = ft_calloc(*lines_arr_size + 1, sizeof(char *));
	if (!lines_arr)
	{
		close(fd);
		error_exit("Malloc failed");
	}
	lines_arr[*lines_arr_size] = NULL;
	return (lines_arr);
}

void	*handle_ft_easy_realloc(char **lines_arr, size_t old_size,
		size_t new_size, int fd)
{
	char	**new_lines_arr;

	new_lines_arr = ft_easy_realloc(lines_arr, old_size, new_size);
	if (!new_lines_arr)
	{
		close(fd);
		free_lines_arr_and_exit(lines_arr, "Malloc failed");
	}
	return (new_lines_arr);
}

void	handle_empty_map(char **lines_arr, size_t lines_nbr)
{
	if (lines_nbr == 0)
	{
		free_str_arr(lines_arr);
		error_exit("Empty file");
	}
}

void	remove_new_line(char *line)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
}
