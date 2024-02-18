/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:35:15 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/18 19:22:20 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	minimap_color_init(t_data *data)
{
	t_rgba	block_color_rgb;
	t_rgba	player_color_rgb;
	t_rgba	ray_color_rgb;
	t_rgba	minimap_background_color;

	block_color_rgb.r = 255;
	block_color_rgb.g = 255;
	block_color_rgb.b = 255;
	block_color_rgb.a = 255;
	player_color_rgb.r = 255;
	player_color_rgb.g = 0;
	player_color_rgb.b = 0;
	player_color_rgb.a = 255;
	ray_color_rgb.r = 0;
	ray_color_rgb.g = 255;
	ray_color_rgb.b = 0;
	ray_color_rgb.a = 255;
	minimap_background_color.r = 0;
	minimap_background_color.g = 0;
	minimap_background_color.b = 0;
	minimap_background_color.a = 255;
	data->minimap->block_color = rgba_to_int(block_color_rgb);
	data->minimap->player_color = rgba_to_int(player_color_rgb);
	data->minimap->ray_color = rgba_to_int(ray_color_rgb);
}

void	minimap_init(t_data *data)
{
	minimap_color_init(data);
	data->minimap->height = 150;
	data->minimap->width = 300;
	data->minimap->offset_x = 20;
	data->minimap->offset_y = 20;
	data->minimap->scale_x = (double)data->minimap->width
		/ ((double)data->map->width * TILE_SIZE);
	data->minimap->scale_y = (double)data->minimap->height
		/ ((double)data->map->height * TILE_SIZE);
	data->minimap->player_position_x = (int)(data->player->x_pos_px
			* data->minimap->scale_x);
	data->minimap->player_position_y = (int)(data->player->y_pos_px
			* data->minimap->scale_y);
}
