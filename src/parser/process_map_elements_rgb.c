/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_elements_rgb.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:25 by slombard          #+#    #+#             */
/*   Updated: 2024/02/05 15:52:26 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

typedef struct s_collect_elements_data_rgba
{
	char	**rgb_values;
	int		rgb[3];
	t_rgba	*target;
}			t_collect_elements_data_rgba;

void	build_rgb_values(char **line_ptr, char *identifier,
		t_collect_elements_data_rgba *vars)
{
	char	*start;
	char	*end;
	char	*rgb_str;

	while(ft_isspace(**line_ptr))
		(*line_ptr)++;
	(*line_ptr) += ft_strlen(identifier);
	while(ft_isspace(**line_ptr))
		(*line_ptr)++;
	start = *line_ptr;
	while(!ft_isspace(**line_ptr) && **line_ptr != '\0')
		(*line_ptr)++;
	end = *line_ptr;
	rgb_str = ft_substr(start, 0, end - start);
	vars->rgb_values = ft_split(rgb_str, ',');
	int i = 0;
	while (vars->rgb_values[i] != NULL)
		i++;
	free(rgb_str);
}

void	check_number_and_quality_rgb_values(t_collect_elements_data_rgba *vars,
		t_data *data)
{
	int	i;

printf("check_number_and_quality_rgb_values\n");
	i = 0;
	while (vars->rgb_values[i] != NULL)
		i++;
	if (i != 3)
	{
		free_str_arr(vars->rgb_values);
		free_exit_parser(data, "Invalid number of RGB values\n");
	}
	i = 0;
	while (vars->rgb_values[i] != NULL)
	{
		if (str_isdigit(vars->rgb_values[i]) == FAILURE)
		{
			free_str_arr(vars->rgb_values);
			free_exit_parser(data, "Invalid RGB values\n");
		}
		i++;
	}
}

void	convert_and_check_range_rgb_values(t_collect_elements_data_rgba *vars,
		t_data *data)
{
	int	i;

	i = 0;
	while (vars->rgb_values[i] != NULL)
	{
		vars->rgb[i] = ft_atoi(vars->rgb_values[i]);
		if (vars->rgb[i] < 0 || vars->rgb[i] > 255)
		{
			free_str_arr(vars->rgb_values);
			free_exit_parser(data, "Invalid range RGB values\n");
		}
		i++;
	}
}

void	collect_elements_data_rgba(char *line, char *identifier, t_data *data)
{
	t_collect_elements_data_rgba	vars;
	vars.target = NULL;
	if (ft_strncmp(identifier, "C", ft_strlen(identifier)) == 0)
		vars.target = &data->map->c;
	else if (ft_strncmp(identifier, "F", ft_strlen(identifier)) == 0)
		vars.target = &data->map->f;
	build_rgb_values(&line, identifier, &vars);
	check_number_and_quality_rgb_values(&vars, data);
	convert_and_check_range_rgb_values(&vars, data);
	if (line != NULL)
		while (*line == ' ' && *line != '\0')
			line++;
	if (line != NULL && *line != '\0')
	{
		free_str_arr(vars.rgb_values);
		free_exit_parser(data, "Extra data after C or F identifier");
	}
	vars.target->r = vars.rgb[0];
	vars.target->g = vars.rgb[1];
	vars.target->b = vars.rgb[2];
	free_str_arr(vars.rgb_values);
}
