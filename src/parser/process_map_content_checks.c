/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_content_checks.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:22:21 by slombard          #+#    #+#             */
/*   Updated: 2024/02/01 17:22:23 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	has_only_one_player(char *line)
{
	int	i;
	int	player_count;

	i = 0;
	player_count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			player_count++;
		i++;
	}
	if (player_count > 1)
		return (FAILURE);
	return (SUCCESS);
}

int	has_only_valid_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
		{
			printf("Found invalid character\n");
			printf("line[%d]: %c\n", i, line[i]);
			if (line[i] == '\n')
				printf("line[%d]: \\n\n", i);
			if (line[i] == '\0')
				printf("line[%d]: \\0\n", i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	check_middle_lines(char **lines_arr, int current_line, int first_line,
		int last_line, int i)
{
	if (lines_arr[current_line][i] != '1')
		return (FAILURE);
	while (lines_arr[current_line][i] != '\0')
	{
		if (lines_arr[current_line][i] != '1'
			&& !ft_isspace(lines_arr[current_line][i]))
		{
			if ((current_line > first_line))
			{
				if (!lines_arr[current_line - 1][i])
					return (FAILURE);
				if (ft_isspace(lines_arr[current_line - 1][i]))
					return (FAILURE);
			}
			if (current_line < last_line)
			{
				if (!lines_arr[current_line + 1][i])
					return (FAILURE);
				if (ft_isspace(lines_arr[current_line + 1][i]))
					return (FAILURE);
			}
		}
		i++;
	}
	i = ft_strlen(lines_arr[current_line]) - 1;
	while (lines_arr[current_line][i] == ' ')
		i--;
	if (lines_arr[current_line][i] != '1')
		return (FAILURE);
	return (SUCCESS);
}

int	is_surrounded_by_walls(char **lines_arr, int current_line, int first_line,
		int last_line)
{
	int	i;

	i = 0;
	while (lines_arr[current_line][i] != '\0'
		&& ft_isspace(lines_arr[current_line][i]))
		i++;
	if (current_line == first_line || current_line == last_line)
	{
		while (lines_arr[current_line][i] != '\0')
		{
			if (lines_arr[current_line][i] != '1'
				&& !ft_isspace(lines_arr[current_line][i]))
				return (FAILURE);
			i++;
		}
	}
	else
	{
		if (check_middle_lines(lines_arr, current_line, first_line, last_line,
				i) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
