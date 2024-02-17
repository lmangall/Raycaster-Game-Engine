/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:15:49 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/17 17:28:33 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "MLX42.h"
# include "doxy.h"
# include "structs.h"


static int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	minimap_init(t_data *data);
void	minimap_render_background(t_data *data);
void	minimap_render_block(int offset_x, int offset_y, t_data *data);
void	minimap_render_walls(t_data *data);
void	minimap_render_player(t_data *data);
void	minimap_render_ray(t_data *data);
void	render_minimap(void *tmp);


#endif // CUB3D_H