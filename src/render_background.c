/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:18:20 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 11:18:24 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	render_background_pixel(mlx_image_t *img, uint32_t top_color,
		uint32_t bottom_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y, top_color);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y, bottom_color);
			x++;
		}
		y++;
	}
}

static uint32_t	rgba_to_int(t_rgba color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
}

void	render_background(mlx_t *mlx, t_rgba c, t_rgba f)
{
	mlx_image_t	*image;
	uint32_t	top_color;
	uint32_t	bottom_color;

	top_color = rgba_to_int(c);
	bottom_color = rgba_to_int(f);
	image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_background_pixel(image, top_color, bottom_color);
	mlx_image_to_window(mlx, image, 0, 0);
}
