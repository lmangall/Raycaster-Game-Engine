
#include "../include/cub3d.h"

#define RIGHT 10
#define LEFT 9
#define UP 8
#define DOWN 7

static int	ray_direction(float angle, char plane)
{
	if (plane == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (DOWN);
		else
			return (UP);
	}
	else if (plane == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (RIGHT);
		else
			return (LEFT);
	}
	return (0);
}

int	update_steps_direction(float angle, float *step, char plane)
{
	if (plane == 'x')
	{
		if (ray_direction(angle, plane) == DOWN)
		{
			if (*step < 0)
				*step *= -1;
		}
		else if (*step > 0)
			*step *= -1;
	}
	else if (plane == 'y')
	{
		if (ray_direction(angle, plane) == RIGHT)
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

int	check_collision_adjust_step(float angle, float *inter, float *step,
		char plane)
{
	if (plane == 'y')
	{
		if (ray_direction(angle, 'x') == DOWN)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (ray_direction(angle, 'y') == LEFT)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}
