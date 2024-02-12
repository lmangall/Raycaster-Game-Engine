/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:18:27 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/12 08:52:03 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this is from the mlx42 library but the compiler is not finding it
static void	mlx_draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	render_pixel(t_data *data, int y, int color)
{
	uint8_t	*pixelstart;

	if (y < 0)
		return ;
	else if (y >= WINDOW_HEIGHT)
		return ;
	pixelstart = &data->image->pixels[(y * WINDOW_WIDTH + data->ray->screen_x)
		* 4];
	mlx_draw_pixel(pixelstart, color);
}

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	reverse_bytes(int c)
{
	int	byte0;
	int	byte1;
	int	byte2;
	int	byte3;

	byte0 = (c & 0xFF) << 24;
	byte1 = (c & 0xFF00) << 8;
	byte2 = (c >> 8) & 0xFF00;
	byte3 = (c >> 24) & 0xFF;
	return (byte0 + byte1 + byte2 + byte3);
}
