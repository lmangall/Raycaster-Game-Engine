
#include"cub3d.h"


//------------------------former main from leonard/textures branch------------------------//



//##############################################################################//
//############################## THE EXITING CODE ##############################//
//##############################################################################//

// static void free_textures(t_textures *textures)
// {
//     if (textures != NULL)
//     {
//         // Free individual texture paths
//         mlx_delete_texture(textures->no);
//         mlx_delete_texture(textures->so);
//         mlx_delete_texture(textures->we);
//         mlx_delete_texture(textures->ea);
//         mlx_delete_texture(textures->f);
//         mlx_delete_texture(textures->c);

//         // Free the t_textures structure
//         free(textures);
//     }
// }


void ft_exit(t_mlx *mlx)   // exit the game
{
 int i = 0;
 while (mlx->dt->map2d[i])
free(mlx->dt->map2d[i++]); // free the map line by line
 free(mlx->dt->map2d); // free the map
 free(mlx->dt); // free the data structure
 free(mlx->ply); // free the player structure
 free(mlx->ray); // free the ray structure
//  free_textures(mlx->textures); // free the textures
 mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
 mlx_close_window(mlx->mlx_p); // close the window
 mlx_terminate(mlx->mlx_p); // terminate the mlx pointer
 printf("Game closed\n"); // print the message
 exit(0); // exit the game
}


//################################################################################//
//############################## THE MOUVEMENT CODE ##############################//
//################################################################################//

void ft_reles(mlx_key_data_t keydata, t_mlx *mlx) // release the key
{
 if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
  mlx->ply->l_r = 0;
 else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
  mlx->ply->l_r = 0;
 else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
  mlx->ply->u_d = 0;
 else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
  mlx->ply->u_d = 0;
 else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
  mlx->ply->rot = 0;
 else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
  mlx->ply->rot = 0;
}

void mlx_key(mlx_key_data_t keydata, void *ml) // key press
{
 t_mlx *mlx;

 mlx = ml;
 if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
  ft_exit(mlx);
 else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
  mlx->ply->l_r = -1;
 else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
  mlx->ply->l_r = 1;
 else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
  mlx->ply->u_d = -1;
 else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
  mlx->ply->u_d = 1;
 else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
  mlx->ply->rot = -1;
 else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
  mlx->ply->rot = 1;
 ft_reles(keydata, mlx); // release the key
}

void rotate_player(t_mlx *mlx, int i) // rotate the player
{
 if (i == 1)
 {
  mlx->ply->angle += ROTATION_SPEED; // rotate right
  if (mlx->ply->angle > 2 * M_PI)
   mlx->ply->angle -= 2 * M_PI;
 }
 else
 {
  mlx->ply->angle -= ROTATION_SPEED; // rotate left
  if (mlx->ply->angle < 0)
   mlx->ply->angle += 2 * M_PI;
 }
}

void move_player(t_mlx *mlx, double move_x, double move_y) // move the player
{
 int  map_grid_y;
 int  map_grid_x;
 int  new_x;
 int  new_y;

 new_x = roundf(mlx->ply->plyr_x + move_x); // get the new x position
 new_y = roundf(mlx->ply->plyr_y + move_y); // get the new y position
 map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
 map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
 if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' && \
 (mlx->dt->map2d[map_grid_y][mlx->ply->plyr_x / TILE_SIZE] != '1' && \
 mlx->dt->map2d[mlx->ply->plyr_y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
 {
  mlx->ply->plyr_x = new_x; // move the player
  mlx->ply->plyr_y = new_y; // move the player
 }
}

void hook(t_mlx *mlx, double move_x, double move_y) // hook the player
{
 if (mlx->ply->rot == 1) //rotate right
  rotate_player(mlx, 1);
 if (mlx->ply->rot == -1) //rotate left
  rotate_player(mlx, 0);
 if (mlx->ply->l_r == 1) //move right
 {
  move_x = -sin(mlx->ply->angle) * PLAYER_SPEED;
  move_y = cos(mlx->ply->angle) * PLAYER_SPEED;
 }
 if (mlx->ply->l_r == -1) //move left
 {
  move_x = sin(mlx->ply->angle) * PLAYER_SPEED;
  move_y = -cos(mlx->ply->angle) * PLAYER_SPEED;
 }
 if (mlx->ply->u_d == 1) //move up
 {
  move_x = cos(mlx->ply->angle) * PLAYER_SPEED;
  move_y = sin(mlx->ply->angle) * PLAYER_SPEED;
 }
 if (mlx->ply->u_d == -1) //move down
 {
  move_x = -cos(mlx->ply->angle) * PLAYER_SPEED;
  move_y = -sin(mlx->ply->angle) * PLAYER_SPEED;
 }
 move_player(mlx, move_x, move_y); // move the player
}

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

int unit_circle(float angle, char c) // check the unit circle
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

int inter_check(float angle, float *inter, float *step, int is_horizon) // check the intersection
{
 if (is_horizon)
 {
  if (angle > 0 && angle < M_PI)//if we look down on the map (behind the player)
    {
    *inter += TILE_SIZE;
    return (-1);
    }
  *step *= -1;
 }
 else
 {
    if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) //if we look right on the map
    {
    *inter += TILE_SIZE;
    return (-1);
    }
  *step *= -1;
 }
 return (1);
}

int wall_hit(float x, float y, t_mlx *mlx) // check the wall hit
{
 int  x_m;
 int  y_m;

 if (x < 0 || y < 0)
  return (0);
 x_m = floor (x / TILE_SIZE); // get the x position in the map
 y_m = floor (y / TILE_SIZE); // get the y position in the map
 if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
  return (0);
 if (mlx->dt->map2d[y_m] && x_m <= (int)strlen(mlx->dt->map2d[y_m]))
  if (mlx->dt->map2d[y_m][x_m] == '1')
   return (0);
 return (1);
}

float get_h_inter(t_mlx *data, float angl) // get the horizontal intersection
{
 float h_x;
 float h_y; //y-coordinate of the horizontal intersection point of the ray with a wall.
 float x_step;
 float y_step;
 int  pixel;

 y_step = TILE_SIZE;
 x_step = TILE_SIZE / tan(angl);
 //calculates the y-coordinate of the bottom edge of the grid cell in which the player is currently located, effectively aligning the intersection point with the horizontal grid lines in the game world
 h_y = floor(data->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
 pixel = inter_check(angl, &h_y, &y_step, 1);
 h_x = data->ply->plyr_x + (h_y - data->ply->plyr_y) / tan(angl);
 if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
  x_step *= -1;
 while (wall_hit(h_x, h_y - pixel, data)) // check the wall hit whit the pixel value
 {
  h_x += x_step;
  h_y += y_step;
 }
data->ray->horizontal_x = h_x;//h_x: The x-coordinate of the point where the horizontal ray intersects a wall.
data->ray->horizontal_y = h_y;//h_y: The y-coordinate of the point where the horizontal ray intersects a wall.
 return (sqrt(pow(h_x - data->ply->plyr_x, 2) + pow(h_y - data->ply->plyr_y, 2))); // get the distance
}

float get_v_inter(t_mlx *data, float angl) // get the vertical intersection
{
 float v_x;
 float v_y;
 float x_step;
 float y_step;
 int  pixel;

 x_step = TILE_SIZE; 
 y_step = TILE_SIZE * tan(angl);
 v_x = floor(data->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
 pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
 v_y = data->ply->plyr_y + (v_x - data->ply->plyr_x) * tan(angl);
 if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
  y_step *= -1;
 while (wall_hit(v_x - pixel, v_y, data)) // check the wall hit whit the pixel value
 {
  v_x += x_step;
  v_y += y_step;
 }
  data->ray->vertical_x = v_x;
  data->ray->vertical_y = v_y;
 return (sqrt(pow(v_x - data->ply->plyr_x, 2) + pow(v_y - data->ply->plyr_y, 2))); // get the distance
}

void cast_rays(t_data *data) // cast the rays
{
  double h_inter;
  double v_inter;

  data->ray->screen_x = 0;
  data->ray->angle_rd = data->ply->angle_rd - (data->ply->fov_rd / 2); // the start angle
  while (data->ray->screen_x < S_W) // loop for the rays
  {
    data->ray->is_wall = 0; // flag for the wall
    h_inter = get_h_inter(data, nor_angle(data->ray->angle_rd)); // get the horizontal intersection
    v_inter = get_v_inter(data, nor_angle(data->ray->angle_rd)); // get the vertical intersection
    if (v_inter <= h_inter) // check the distance
    data->ray->distance = v_inter; // get the distance
    else
    {
    data->ray->distance = h_inter; // get the distance
    data->ray->is_wall = 1; // flag for the wall
    }
    init_ray(data);
    render_wall(data);
    render_floor_ceiling(data);
    data->ray->screen_x++; // next pixel/ray
    data->ray->angle_rd += (data->ply->fov_rd / S_W); // next angle
  } 
}

//##############################################################################################//
//############################## START THE GAME AND THE GAME LOOP ##############################//
//##############################################################################################//

void game_loop(void *ml) // game loop
{
 t_mlx *mlx;

 mlx = ml; // cast to the mlx structure
 mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
 mlx->img = mlx_new_image(mlx->mlx_p, S_W, S_H); // create new image
 hook(mlx, 0, 0); // hook the player
 cast_rays(mlx); // cast the rays
 mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0); // put the image to the window
}

void init_the_player(t_mlx mlx) // init the player structure
{
 mlx.ply->plyr_x = mlx.dt->p_x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
 mlx.ply->plyr_y = mlx.dt->p_y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
 mlx.ply->fov_rd = (FOV * M_PI) / 180; // field of view in radians
 mlx.ply->angle = M_PI; // player angle
 //the rest of the variables are initialized to zero by calloc
}

void start_the_game(t_map *dt, char *map_argv) // start the game
{
  t_mlx mlx;

(void)map_argv;


char *map_lines;
map_lines = cub_to_str(map_argv);

load_textures(&mlx, map_lines);


 mlx.dt = dt; // init the mlx structure
 mlx.ply = calloc(1, sizeof(t_player)); // init the player structure i'm using calloc to initialize the variables to zero
 mlx.ray = calloc(1, sizeof(t_ray)); // init the ray structure
 mlx.mlx_p = mlx_init(S_W, S_H, "Cub3D", 0); // init the mlx pointer
 init_the_player(mlx); // init the player structure
 mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx); // game loop
 mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx); // key press and release
 mlx_loop(mlx.mlx_p); // mlx loop
 ft_exit(&mlx); // exit the game
}

//################################################################################################//
//############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//
//################################################################################################//

t_map *init_argumet() // init the data structure
{
 t_map *dt = calloc(1, sizeof(t_map)); // init the data structure
 dt->map2d = calloc(10, sizeof(char *)); // init the map
 dt->map2d[0] = strdup("1111111111111111111111111"); //fill the map
 dt->map2d[1] = strdup("1000000000000000000100001");
 dt->map2d[2] = strdup("1001000000000P00000000001");
 dt->map2d[3] = strdup("1001000000000000001000001");
 dt->map2d[4] = strdup("1001000000000000001000001");
 dt->map2d[5] = strdup("1001000000100000001000001");
 dt->map2d[6] = strdup("1001000000000000001000001");
 dt->map2d[7] = strdup("1001000000001000001000001");
 dt->map2d[8] = strdup("1111111111111111111111111");
 dt->map2d[9] = NULL;
 dt->p_y = 3; // player y position in the map
 dt->p_x = 14; // player x position in the map
 dt->w_map = 25; // map width
 dt->h_map = 9; // map height
 return (dt); // return the data structure
}

void v()
{
 system("leaks mini_cub3D");
}

int main(int argc, char **argv)
{
 t_map *data = calloc(1, sizeof(t_map));

  (void)argc;

  // if (argc != 2)
  // {
  //   printf("Error\nWrong number of arguments\n");
  //   return (0);
  // }
 atexit(v);
  parse_map(argv[1], data);




  start_the_game(data, argv[2]); // start the game
 return 0;
}