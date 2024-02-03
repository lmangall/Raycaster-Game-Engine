
#include "../include/cub3d.h"

void	rotate_player(double *orientation_angle_rd, enum e_rotation direction)
{
	if (direction == R_RIGHT)
	{
		*orientation_angle_rd += PLAYER_ROTATION_SPEED;
		if (*orientation_angle_rd > 2 * M_PI)
			*orientation_angle_rd -= 2 * M_PI;
	}
	else if (direction == R_LEFT)
	{
		*orientation_angle_rd -= PLAYER_ROTATION_SPEED;
		if (*orientation_angle_rd < 0)
			*orientation_angle_rd += 2 * M_PI;
	}
}

int	is_wall(t_data *data, double x, double y)
{
	int	map_grid_y;
	int	map_grid_x;

	map_grid_x = (x / TILE_SIZE);
	map_grid_y = (y / TILE_SIZE);
	if (data->map->grid[map_grid_y][map_grid_x] == '1'
		|| (data->map->grid[map_grid_y][data->player->x_pos_px
			/ TILE_SIZE] == '1' || data->map->grid[data->player->y_pos_px
			/ TILE_SIZE][map_grid_x] == '1'))
		return (1);
	return (0);
}

// void	move_player(t_data *data, double move_x, double move_y)
// {
// 	int	new_x_position;
// 	int	new_y_position;

// 	new_x_position = roundf(data->player->x_pos_px + move_x);
// 	new_y_position = roundf(data->player->y_pos_px + move_y);
// 	if (!is_wall(data, new_x_position, new_y_position))
// 	{
// 		data->player->x_pos_px = new_x_position;
// 		data->player->y_pos_px = new_y_position;
// 	}
// }


static void move_player_forward(t_data *data, double move_x, double move_y)
{
    move_x = cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y = sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;


    if (!is_wall(data, (move_x + data->player->x_pos_px), (move_y + data->player->y_pos_px)))
    {
        data->player->x_pos_px = roundf(data->player->x_pos_px + move_x);
        data->player->y_pos_px = roundf(data->player->y_pos_px + move_y);
    }
}
static void move_player_backward(t_data *data, double move_x, double move_y)
{
    move_x = -cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y = -sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;

    if (!is_wall(data, (move_x + data->player->x_pos_px), (move_y + data->player->y_pos_px)))
    {
        data->player->x_pos_px = roundf(data->player->x_pos_px + move_x);
        data->player->y_pos_px = roundf(data->player->y_pos_px + move_y);
    }
}

static void move_player_lateral(t_data *data, double move_x, double move_y)
{
    if (data->player->lateral_move == L_LEFT)
    {
        move_x = sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
        move_y = -cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    }
    else if (data->player->lateral_move == L_RIGHT)
    {
        move_x = -sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
        move_y = cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    }
    
    if (!is_wall(data, (move_x + data->player->x_pos_px), (move_y + data->player->y_pos_px)))
    {
        data->player->x_pos_px = roundf(data->player->x_pos_px + move_x);
        data->player->y_pos_px = roundf(data->player->y_pos_px + move_y);
    }
}




void	apply_movement(t_data *data, double move_x, double move_y)
{
    if (data->player->rotation == R_RIGHT)
        rotate_player(&data->player->orientation_angle_rd, R_RIGHT);
    else if (data->player->rotation == R_LEFT)
        rotate_player(&data->player->orientation_angle_rd, R_LEFT);

    if (data->player->lateral_move == L_RIGHT)
        move_player_lateral(data, move_x, move_y);
    else if (data->player->lateral_move == L_LEFT)
        move_player_lateral(data, move_x, move_y);
    else if (data->player->longitudinal_move == FORWARD)
        move_player_forward(data, move_x, move_y);
    else if (data->player->longitudinal_move == BACKWARD)
        move_player_backward(data, move_x, move_y);
}








// void	apply_movement(t_data *data, double move_x, double move_y)
// {
// 	if (data->player->rotation == R_RIGHT)
// 		rotate_player(&data->player->orientation_angle_rd, R_RIGHT);
// 	if (data->player->rotation == R_LEFT)
// 		rotate_player(&data->player->orientation_angle_rd, R_LEFT);
// 	if (data->player->lateral_move == L_RIGHT)
// 	{
// 		move_x = -sin(data->player->orientation_angle_rd)
// 			* PLAYER_TRANSLATION_SPEED;
// 		move_y = cos(data->player->orientation_angle_rd)
// 			* PLAYER_TRANSLATION_SPEED;
// 	}
// 	if (data->player->lateral_move == L_LEFT)
// 	{
// 		move_x = sin(data->player->orientation_angle_rd)
// 			* PLAYER_TRANSLATION_SPEED;
// 		move_y = -cos(data->player->orientation_angle_rd)
// 			* PLAYER_TRANSLATION_SPEED;
// 	}
// 	if (data->player->longitudinal_move == FORWARD)
// 	{
// 		move_x = cos(data->player->orientation_angle_rd)
// 			* PLAYER_TRANSLATION_SPEED;
// 		move_y = sin(data->player->orientation_angle_rd)
// 			* PLAYER_TRANSLATION_SPEED;
// 	}
// 	if (data->player->longitudinal_move == BACKWARD)
// 	{
// 		move_x = -cos(data->player->orientation_angle_rd)
// 			* PLAYER_TRANSLATION_SPEED;
// 		move_y = -sin(data->player->orientation_angle_rd)
// 			* PLAYER_TRANSLATION_SPEED;
// 	}
// 	move_player(data, move_x, move_y);
// }