/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:36:15 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/18 10:38:33 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_minimap(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	minimap_init(data);
	minimap_render_background(data);
	minimap_render_walls(data);
	minimap_render_player(data);
	minimap_render_ray(data);
}
