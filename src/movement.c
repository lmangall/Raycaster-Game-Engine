
#include "../include/cub3d.h"
#include <math.h>

void	key_pressed(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		free_exit(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player->longitudinal_move = FORWARD;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player->longitudinal_move = BACKWARD;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player->lateral_move = L_LEFT;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player->lateral_move = L_RIGHT;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->rotation = R_LEFT;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->rotation = R_RIGHT;
}

void key_released(t_data *data)
{
	if (!mlx_is_key_down(data->mlx, MLX_KEY_W) && !mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player->longitudinal_move = NONE;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_A) && !mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player->lateral_move = L_NONE;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->rotation = R_NONE;
}

void	key_hook(void *tmp) // key press
{
	t_data *data;

	data = (t_data *)tmp;

	key_pressed(data);
	key_released(data);
}



void	rotate_player(t_data *data, int i) // rotate the player
{
	if (i == 1)
	{
		data->player->orientation_angle_rd += PLAYER_ROTATION_SPEED;
		// rotate right
		if (data->player->orientation_angle_rd > 2 * M_PI)
			data->player->orientation_angle_rd -= 2 * M_PI;
	}
	else
	{
		data->player->orientation_angle_rd -= PLAYER_ROTATION_SPEED;
		// rotate left
		if (data->player->orientation_angle_rd < 0)
			data->player->orientation_angle_rd += 2 * M_PI;
	}
}

void	move_player(t_data *data, double move_x, double move_y)
// move the player
{
	int map_grid_y;
	int map_grid_x;
	int new_x;
	int new_y;

	new_x = roundf(data->player->x_pos_px + move_x);
	// get the new x position
	new_y = roundf(data->player->y_pos_px + move_y);
	// get the new y position
	map_grid_x = (new_x / TILE_SIZE);
	// get the x position in the map
	map_grid_y = (new_y / TILE_SIZE);
	// get the y position in the map
	if (data->map->grid[map_grid_y][map_grid_x] != '1'
		&& (data->map->grid[map_grid_y][data->player->x_pos_px
			/ TILE_SIZE] != '1' && data->map->grid[data->player->y_pos_px
			/ TILE_SIZE][map_grid_x] != '1'))
	// check the wall hit and the diagonal wall hit
	{
		data->player->x_pos_px = new_x; // move the player
		data->player->y_pos_px = new_y; // move the player
	}
}

void	movement_hook(t_data *data, double move_x, double move_y)
{
	if (data->player->rotation == R_RIGHT)
		rotate_player(data, 1);
	if (data->player->rotation == R_LEFT)
		rotate_player(data, 0);
	if (data->player->lateral_move == L_RIGHT) // move right
	{
		move_x = -sin(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
		move_y = cos(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
	}
	if (data->player->lateral_move == L_LEFT) // move left
	{
		move_x = sin(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
		move_y = -cos(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
	}
	if (data->player->longitudinal_move == FORWARD) // move up
	{
		move_x = cos(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
		move_y = sin(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
	}
	if (data->player->longitudinal_move == BACKWARD) // move down
	{
		move_x = -cos(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
		move_y = -sin(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
	}
	move_player(data, move_x, move_y); // move the player
}
// void	key_loop(void *data_pointer)
// {
// 	t_data *data;

// 	data = (t_data *)data_pointer;
// 	key_pressed(data);
// 	key_released(data);
// }

// //get rid of this line, should be from math lib
// #define M_PI 3.14159265358979323846

// void	ft_reles(mlx_key_data_t keydata, t_data *data) // release the key
// {
// 	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
// 		data->player->lateral_move = L_NONE;
// 	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
// 		data->player->lateral_move = L_NONE;
// 	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
// 		data->player->longitudinal_move = NONE;
// 	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
// 		data->player->longitudinal_move = NONE;
// 	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
// 		data->player->rotation = R_NONE;
// 	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
// 		data->player->rotation = R_NONE;
// }