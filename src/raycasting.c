
#include "../include/cub3d.h"

// # define LOOK_RIGHT 10
// # define LOOK_UP_AND_DOWN 11

int	update_steps_direction(float angle, float *step, char c)
// check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
		{
			if (*step < 0)
				*step *= -1;
		}
		else
		{
			if (*step > 0)
				*step *= -1;
		}
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
		{
			if (*step > 0)
				*step *= -1;
		}
		else
		{
			if (*step < 0)
				*step *= -1;
		}
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
	if ((y_m >= data->map->height || x_m >= data->map->width))
		return (0);
	if (data->map->grid[y_m] && x_m <= (int)strlen(data->map->grid[y_m]))
		if (data->map->grid[y_m][x_m] == '1')
			return (0);
	return (1);
}

void	update_ray(t_data *data)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	data->ray->length *= cos(nor_angle(data->ray->angle_rd
				- data->player->orientation_angle_rd));   // fix the fisheye
	wall_h = (TILE_SIZE / data->ray->length) * ((WINDOW_WIDTH / 2)
			/ tan(data->player->fov_rd / 2)); // get the wall height
	b_pix = (WINDOW_HEIGHT / 2) + (wall_h / 2);
	t_pix = (WINDOW_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > WINDOW_HEIGHT)
		b_pix = WINDOW_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	// data->ray->current_texture = data->textures->north;//change this depending on orientation
	data->ray->current_texture = texture_selection(data);
	data->ray->wall_h = wall_h;
	data->ray->t_pix = t_pix;
	data->ray->b_pix = b_pix;
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
	update_steps_direction(angl, &x_step, 'y');
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
				- data->player->y_pos_px, 2)));
	// get the distance
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
	update_steps_direction(angl, &y_step, 'x');
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
	{
		data->ray->wall_collision_orientation = NO_COLLISION;
		h_inter = get_h_inter(data, nor_angle(data->ray->angle_rd));
		v_inter = get_v_inter(data, nor_angle(data->ray->angle_rd));
		if (v_inter <= h_inter)
		{
			data->ray->length = v_inter;
			data->ray->wall_collision_orientation = VERTICAL;
		}
		else
		{
			data->ray->length = h_inter; // get the distance
			data->ray->wall_collision_orientation = HORIZONTAL;
		}
		update_ray(data);
		render_wall(data);
		render_floor_ceiling(data);
		data->ray->screen_x++;
		// next pixel/ray
		data->ray->angle_rd += (data->player->fov_rd / WINDOW_WIDTH);
		// next angle
	}
}
