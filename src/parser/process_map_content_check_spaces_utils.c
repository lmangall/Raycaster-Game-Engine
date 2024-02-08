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

// This function is called for a space and check
// if the space is surrounded by walls or ny another space
int	is_valid_char(char c)
{
	printf("is_valid_char\n");
	if (c == ' ' || c == '1')
	{
		printf("is_valid_char SUCCESS\n");
		return (SUCCESS);
	}
	else
	{
		printf("is_valid_char FAILURE\n");
		return (FAILURE);
	}
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
