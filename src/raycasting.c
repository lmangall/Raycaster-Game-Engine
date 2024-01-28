
#include "../include/cub3d.h"

int	unit_circle(float angle, char c) // check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step,
				int is_horizon) // check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		// if we look down on the map (behind the player)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		// if we look right on the map
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_data *data) // check the wall hit
{
	int x_m;
	int y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE); // get the x position in the map
	y_m = floor(y / TILE_SIZE); // get the y position in the map
	if ((y_m >= data->map->h_map || x_m >= data->map->w_map))
		return (0);
	if (data->map->grid[y_m] && x_m <= (int)strlen(data->map->grid[y_m]))
		if (data->map->grid[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_data *data, float angl) // get the horizontal intersection
{
	float h_x;
	float h_y;
	// y-coordinate of the horizontal intersection point of the ray with a wall.
	float x_step;
	float y_step;
	int pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	// calculates the y-coordinate of the bottom edge of the grid cell in which the player is currently located,
	// effectively aligning the intersection point
	// with the horizontal grid lines in the game world
	h_y = floor(data->player->y_pos_px / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = data->player->x_pos_px + (h_y - data->player->y_pos_px) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y')
			&& x_step < 0))
		// check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, data))
	// check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	data->ray->horizontal_x = h_x;
	// h_x: The x-coordinate of the point where the horizontal ray intersects a wall.
	data->ray->horizontal_y = h_y;
	// h_y: The y-coordinate of the point where the horizontal ray intersects a wall.
	return (sqrt(pow(h_x - data->player->x_pos_px, 2) + pow(h_y
				- data->player->y_pos_px, 2))); // get the distance
}

float	get_v_inter(t_data *data, float angl) // get the vertical intersection
{
	float v_x;
	float v_y;
	float x_step;
	float y_step;
	int pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(data->player->x_pos_px / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	// check the intersection and get the pixel value
	v_y = data->player->y_pos_px + (v_x - data->player->x_pos_px) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x')
			&& y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, data))
	// check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	data->ray->vertical_x = v_x;
	data->ray->vertical_y = v_y;
	return (sqrt(pow(v_x - data->player->x_pos_px, 2) + pow(v_y
				- data->player->y_pos_px, 2))); // get the distance
}

void	raycasting(t_data *data)
{
	double	h_inter;
	double	v_inter;

	data->ray->screen_x = 0;
	data->ray->angle_rd = data->player->orientation_angle_rd
		- (data->player->fov_rd / 2); // the start angle
	while (data->ray->screen_x < WINDOW_WIDTH)
	// loop for the rays
	{
		data->ray->is_wall = 0;
		// flag for the wall
		h_inter = get_h_inter(data, nor_angle(data->ray->angle_rd));
		// get the horizontal intersection
		v_inter = get_v_inter(data, nor_angle(data->ray->angle_rd));
		// get the vertical intersection
		if (v_inter <= h_inter)
			// check the distance
			data->ray->length = v_inter;
		// get the distance
		else
		{
			data->ray->length = h_inter; // get the distance
			data->ray->is_wall = 1;      // flag for the wall
		}
		init_ray(data);
		render_wall(data);
		render_floor_ceiling(data);
		data->ray->screen_x++;
		// next pixel/ray
		data->ray->angle_rd += (data->player->fov_rd / WINDOW_WIDTH);
		// next angle
	}
}
