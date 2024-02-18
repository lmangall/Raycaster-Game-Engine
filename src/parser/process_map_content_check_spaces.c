/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_content_check_spaces.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:51:14 by slombard          #+#    #+#             */
/*   Updated: 2024/02/18 18:17:44 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	check_same_line(char **lines_arr, int current_line, int idx)
{
	int	line_len;
	int	start;
	int	end;

	printf("check_same_line\n");
	printf("lines_arr[%d]: %s\n", current_line, lines_arr[current_line]);
	line_len = ft_strlen(lines_arr[current_line]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (is_valid_char(lines_arr[current_line][start]) == FAILURE)
		{
			printf("FAILURE\n");
			return (FAILURE);
		}
		start++;
	}
	printf("SUCCESS\n");
	return (SUCCESS);
}

int	check_previous_line(char **lines_arr, int current_line, int first_line,
		int idx)
{
	int	line_len;
	int	start;
	int	end;

	if (current_line == first_line)
	{
		ft_printf("if (current_line == first_line)\nSUCCESS\n");
		return (SUCCESS);
	}
	line_len = ft_strlen(lines_arr[current_line - 1]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (is_valid_char(lines_arr[current_line - 1][start]) == FAILURE)
		{
			printf("FAILURE\n");
			return (FAILURE);
		}
		start++;
	}
	ft_printf("SUCCESS\n");
	return (SUCCESS);
}

int	check_next_line(char **lines_arr, int current_line, int last_line, int idx)
{
	int	line_len;
	int	start;
	int	end;

	if (current_line == last_line)
	{
		printf("check_next_line SUCCESS\n");
		return (SUCCESS);
	}
	line_len = ft_strlen(lines_arr[current_line + 1]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (is_valid_char(lines_arr[current_line + 1][start]) == FAILURE)
		{
			printf("check_next_line FAILURE\n");
			return (FAILURE);
		}
		start++;
	}
	printf("check_next_line SUCCESS\n");
	return (SUCCESS);
}

int	spaces_are_surrounded_by_walls(char **lines_arr, int current_line,
		int first_line, int last_line)
{
	int	i;

	i = 0;
	while (lines_arr[current_line][i] != '\0')
	{
		if (current_line == first_line || current_line == last_line)
		{
			i++;
			continue ;
		}
		if (lines_arr[current_line][i] == ' ')
		{
			if (check_same_line(lines_arr, current_line, i) == FAILURE)
				return (FAILURE);
			if (check_previous_line(lines_arr, current_line, first_line, i)
				== FAILURE)
				return (FAILURE);
			if (check_next_line(lines_arr, current_line, last_line, i)
				== FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
