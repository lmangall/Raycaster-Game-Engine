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
	return (new_lines_arr);
}

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
