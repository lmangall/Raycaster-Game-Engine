/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_content_check_spaces.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:51:14 by slombard          #+#    #+#             */
/*   Updated: 2024/02/01 17:51:19 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	is_valid_space_sorrounding_char(char c)
{
	if (c == ' ' || c == '1')
		return (SUCCESS);
	else
		return (FAILURE);
}

void	define_start_and_end(int *start, int *end, int idx, int line_len)
{
	*start = idx - 1;
	if (idx - 1 < 0)
		*start = 0;
	*end = idx + 1;
	if (idx + 1 > line_len - 1)
		*end = line_len - 1;
}

int	check_same_line(char **lines_arr, int current_line, int idx)
{
	int	line_len;
	int	start;
	int	end;

	line_len = ft_strlen(lines_arr[current_line]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (!is_valid_space_sorrounding_char(lines_arr[current_line][start]))
			return (FAILURE);
		start++;
	}
	return (SUCCESS);
}

int	check_previous_line(char **lines_arr, int current_line, int first_line,
		int idx)
{
	int	line_len;
	int	start;
	int	end;

	if (current_line == first_line)
		return (SUCCESS);
	line_len = ft_strlen(lines_arr[current_line - 1]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (!is_valid_space_sorrounding_char(lines_arr[current_line
				- 1][start]))
			return (FAILURE);
		start++;
	}
	return (SUCCESS);
}

int	check_next_line(char **lines_arr, int current_line, int last_line, int idx)
{
	int	line_len;
	int	start;
	int	end;

	if (current_line == last_line)
		return (SUCCESS);
	line_len = ft_strlen(lines_arr[current_line + 1]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (!is_valid_space_sorrounding_char(lines_arr[current_line
				+ 1][start]))
			return (FAILURE);
		start++;
	}
	return (SUCCESS);
}

int	spaces_are_surrounded_by_walls(char **lines_arr, int current_line,
		int first_line, int last_line)
{
	int i;

	i = 0;
	while (lines_arr[current_line][i] != '\0')
	{
		if (lines_arr[current_line][i] == ' ')
		{
			if (!check_same_line(lines_arr, current_line, i))
			{
				printf("check_same_line\n");
				return (FAILURE);
			}
			if (!check_previous_line(lines_arr, current_line, first_line, i))
			{
				printf("check_previous_line\n");
				return (FAILURE);
			}
			if (!check_next_line(lines_arr, current_line, last_line, i))
			{
				printf("check_next_line\n");
				return (FAILURE);
			}
		}
		i++;
	}
	printf("return (SUCCESS)\n");
	return (SUCCESS);
}
