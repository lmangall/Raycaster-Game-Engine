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

void	*handle_ft_calloc(size_t *lines_arr_size, int fd)
{
	char	**lines_arr;

	lines_arr = ft_calloc(*lines_arr_size, sizeof(char *) + 1);
	if (!lines_arr)
	{
		close(fd);
		error_exit("Error\nMalloc failed", NULL);
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
		free_lines_arr_and_exit(lines_arr);
	}
	// new_lines_arr[new_size - 1] = NULL;
	return (new_lines_arr);
}
