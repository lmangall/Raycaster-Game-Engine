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
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

typedef struct s_ints_middle_lines
{
	int	i;
	int	current_line;
	int	first_line;
	int	last_line;
}		t_ints_middle_lines;

int	check_line_before_and_after(char **lines_arr, t_ints_middle_lines ints)
{
	if ((ints.current_line > ints.first_line))
	{
		if (!lines_arr[ints.current_line - 1][ints.i])
			return (FAILURE);
		if (ft_isspace(lines_arr[ints.current_line - 1][ints.i]))
			return (FAILURE);
	}
	if (ints.current_line < ints.last_line)
	{
		if (!lines_arr[ints.current_line + 1][ints.i])
			return (FAILURE);
		if (ft_isspace(lines_arr[ints.current_line + 1][ints.i]))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	check_middle_lines(char **lines_arr, t_ints_middle_lines ints)
{
	if (lines_arr[ints.current_line][ints.i] != '1')
		return (FAILURE);
	while (lines_arr[ints.current_line][ints.i] != '\0')
	{
		if (lines_arr[ints.current_line][ints.i] != '1'
			&& !ft_isspace(lines_arr[ints.current_line][ints.i]))
		{
			if (check_line_before_and_after(lines_arr, ints) == FAILURE)
				return (FAILURE);
		}
		ints.i++;
	}
	ints.i = ft_strlen(lines_arr[ints.current_line]) - 1;
	while (lines_arr[ints.current_line][ints.i] == ' ')
		ints.i--;
	if (lines_arr[ints.current_line][ints.i] != '1')
		return (FAILURE);
	return (SUCCESS);
}

int	is_surrounded_by_walls(char **lines_arr, int current_line, int first_line,
		int last_line)
{
	t_ints_middle_lines	ints;

	ints.i = 0;
	ints.current_line = current_line;
	ints.first_line = first_line;
	ints.last_line = last_line;
	while (lines_arr[current_line][ints.i] != '\0'
		&& ft_isspace(lines_arr[current_line][ints.i]))
		ints.i++;
	if (current_line == first_line || current_line == last_line)
	{
		while (lines_arr[current_line][ints.i] != '\0')
		{
			if (lines_arr[current_line][ints.i] != '1'
				&& !ft_isspace(lines_arr[current_line][ints.i]))
				return (FAILURE);
			ints.i++;
		}
	}
	else
	{
		if (check_middle_lines(lines_arr, ints) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
