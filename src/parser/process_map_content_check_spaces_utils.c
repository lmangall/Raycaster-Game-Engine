/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_content_check_spaces_utils.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:48:33 by slombard          #+#    #+#             */
/*   Updated: 2024/02/05 15:48:37 by slombard         ###   ########.fr       */
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
