/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:29:52 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/14 10:44:36 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define FIXED_DISTANCE 10

// static mlx_texture_t	*load_sprite(t_data *data)
// {
// 	// data->sprite = mlx_load_png("sprites/sprite.png");
// 	data->sprite = mlx_load_png("textures/jesus_is_brian.png");
// 	return (data->sprite);
// }

static uint32_t	sprite_pixel_color(mlx_texture_t *sprite, double sprite_x,
		double sprite_y)
{
	uint32_t	*sprite_pixels;
	int			sprite_pixel_x;
	int			sprite_pixel_y;
	uint32_t	color;

	sprite_pixels = (uint32_t *)sprite->pixels;
	// Scaling
	sprite_x = sprite_x / TILE_SIZE * sprite->width;
	sprite_y = sprite_y / TILE_SIZE * sprite->height;
	sprite_x = fmax(0.0, fmin(sprite_x, sprite->width - 1));
	sprite_y = fmax(0.0, fmin(sprite_y, sprite->height - 1));
	sprite_pixel_x = (int)sprite_x;
	sprite_pixel_y = (int)sprite_y;
	// Sample pixel color from the sprite texture
	color = sprite_pixels[sprite_pixel_y * sprite->width + sprite_pixel_x];
	return (color);
}

// renders an image at a fixed distance of the player
void	render_sprite(t_data *data)
{
	uint32_t		color;
	mlx_texture_t	*sprite;
	double			world_x;
	double			world_y;

	int sprite_x, sprite_y; // Changed to int for pixel coordinates
	int pixel_x, pixel_y;
	sprite = data->textures->sprite;
	// Calculate the world position of the sprite
	world_x = data->player->x_pos_px + cos(data->player->orientation_angle_rd)
		* FIXED_DISTANCE;
	world_y = data->player->y_pos_px + sin(data->player->orientation_angle_rd)
		* FIXED_DISTANCE;
	// Iterate over the pixels of the sprite
	pixel_x = 0;
	while (pixel_x < (int)sprite->width) // Cast to int
	{
		pixel_y = 0;
		while (pixel_y < (int)sprite->height) // Cast to int
		{
			// Calculate the position of the pixel in the world
			sprite_x = (int)(world_x + pixel_x - sprite->width / 2);
			sprite_y = (int)(world_y + pixel_y - sprite->height / 2);
			// Ensure that the calculated pixel coordinates are within the bounds of the sprite dimensions
			if (sprite_x >= 0 && sprite_x < (int)sprite->width && sprite_y >= 0
				&& sprite_y < (int)sprite->height) // Cast to int
			{
				color = sprite_pixel_color(sprite, sprite_x, sprite_y);
				color = reverse_bytes(color);
				mlx_put_pixel(data->img, sprite_x, sprite_y, color);
			}
			pixel_y++;
		}
		pixel_x++;
	}
}
