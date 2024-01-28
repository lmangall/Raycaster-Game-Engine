// before you start, you need to install the mlx library and you need to install
// the glfw library you need to incude the mlx library in your file for
// compiling the code you need to include the required frameworks and the
// libmlx.a amd link the glfw library the flag (-O3 -ffast-math) is for
// optimization the flag (-framework) is for the required frameworks the flag
// (-lglfw) is for linking the glfw library the flag (-L) is for the path to the
// glfw library the flag (-o) is for the name of the executable file to run the
// program (./cub)

// example:
// cc -O3 -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw
// (path to libmlx42.a) -L(path to glfw library) cub3d.c -o cub

#include "cub3d.h"

// ##############################################################################//
// ############################## THE EXITING CODE
// ##############################//
// ##############################################################################//

// static void free_textures(t_textures *textures)
// {
//     if (textures != NULL)
//     {
//         // Free individual texture paths
//         mlx_delete_texture(textures->north);
//         mlx_delete_texture(textures->south);
//         mlx_delete_texture(textures->west);
//         mlx_delete_texture(textures->east);
//         mlx_delete_texture(textures->floor);
//         mlx_delete_texture(textures->ceiling);

//         // Free the t_textures structure
//         free(textures);
//     }
// }

void ft_exit(t_data *data) // exit the game
{
  int i = 0;
  while (data->map->grid[i])
    free(data->map->grid[i++]); // free the map line by line
  free(data->map->grid);        // free the map
  free(data->map);              // free the data structure
  free(data->player);           // free the player structure
  free(data->ray);              // free the ray structure
  //  free_textures(data->textures); // free the textures
  mlx_delete_image(data->mlx, data->img); // delete the image
  mlx_close_window(data->mlx);            // close the window
  mlx_terminate(data->mlx);               // terminate the mlx pointer
  printf("Game closed\n");                // print the message
  exit(0);                                // exit the game
}

// ################################################################################//
// ############################## THE MOUVEMENT CODE
// ##############################//
// ################################################################################//

void ft_reles(mlx_key_data_t keydata, t_data *data) // release the key
{
  if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
    data->player->lateral_move = L_NONE;
  else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
    data->player->lateral_move = L_NONE;
  else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
    data->player->longitudinal_move = NONE;
  else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
    data->player->longitudinal_move = NONE;
  else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
    data->player->rotation = R_NONE;
  else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
    data->player->rotation = R_NONE;
}

void mlx_key(mlx_key_data_t keydata, void *ml) // key press
{
  t_data *data;

  data = ml;
  if (keydata.key == MLX_KEY_ESCAPE &&
      (keydata.action == MLX_PRESS ||
       keydata.action == MLX_REPEAT)) // exit the game
    ft_exit(data);
  else if (keydata.key == MLX_KEY_A &&
           (keydata.action == MLX_PRESS)) // move left
    data->player->lateral_move = L_LEFT;
  else if (keydata.key == MLX_KEY_D &&
           (keydata.action == MLX_PRESS)) // move right
    data->player->lateral_move = L_RIGHT;
  else if (keydata.key == MLX_KEY_S &&
           (keydata.action == MLX_PRESS)) // move down
    data->player->longitudinal_move = BACKWARD;
  else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
    data->player->longitudinal_move = FORWARD;
  else if (keydata.key == MLX_KEY_LEFT &&
           keydata.action == MLX_PRESS) // rotate left
    data->player->rotation = R_LEFT;
  else if (keydata.key == MLX_KEY_RIGHT &&
           keydata.action == MLX_PRESS) // rotate right
    data->player->rotation = R_RIGHT;
  ft_reles(keydata, data); // release the key
}

void rotate_player(t_data *data, int i) // rotate the player
{
  if (i == 1) {
    data->player->orientation_angle_rd += PLAYER_ROTATION_SPEED; // rotate right
    if (data->player->orientation_angle_rd > 2 * M_PI)
      data->player->orientation_angle_rd -= 2 * M_PI;
  } else {
    data->player->orientation_angle_rd -= PLAYER_ROTATION_SPEED; // rotate left
    if (data->player->orientation_angle_rd < 0)
      data->player->orientation_angle_rd += 2 * M_PI;
  }
}

void move_player(t_data *data, double move_x, double move_y) // move the player
{
  int map_grid_y;
  int map_grid_x;
  int new_x;
  int new_y;

  new_x = roundf(data->player->x_pos_px + move_x); // get the new x position
  new_y = roundf(data->player->y_pos_px + move_y); // get the new y position
  map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
  map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
  if (data->map->grid[map_grid_y][map_grid_x] != '1' &&
      (data->map->grid[map_grid_y][data->player->x_pos_px / TILE_SIZE] != '1' &&
       data->map->grid[data->player->y_pos_px / TILE_SIZE][map_grid_x] !=
           '1')) // check the wall hit and the diagonal wall hit
  {
    data->player->x_pos_px = new_x; // move the player
    data->player->y_pos_px = new_y; // move the player
  }
}

void hook(t_data *data, double move_x, double move_y) // hook the player
{
  if (data->player->rotation == R_RIGHT)
    rotate_player(data, 1);
  if (data->player->rotation == R_LEFT)
    rotate_player(data, 0);
  if (data->player->lateral_move == L_RIGHT) // move right
  {
    move_x =
        -sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y = cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
  }
  if (data->player->lateral_move == L_LEFT) // move left
  {
    move_x = sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y =
        -cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
  }
  if (data->player->longitudinal_move == FORWARD) // move up
  {
    move_x = cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y = sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
  }
  if (data->player->longitudinal_move == BACKWARD) // move down
  {
    move_x =
        -cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y =
        -sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
  }
  move_player(data, move_x, move_y); // move the player
}

// #####################################################################################//
// ############################## THE WALL RENDERING CODE
// ##############################//
// #####################################################################################//

void my_mlx_pixel_put(t_data *data, int x, int y, int color) // put the pixel
{
  if (x < 0) // check the x position
    return;
  else if (x >= WINDOW_WIDTH)
    return;
  if (y < 0) // check the y position
    return;
  else if (y >= WINDOW_HEIGHT)
    return;
  mlx_put_pixel(data->img, x, y, color); // put the pixel
}

float nor_angle(float angle) // normalize the angle
{
  if (angle < 0)
    angle += (2 * M_PI);
  if (angle > (2 * M_PI))
    angle -= (2 * M_PI);
  return (angle);
}

void draw_floor_ceiling(t_data *data, int ray, int t_pix,
                        int b_pix) // draw the floor and the ceiling
{
  int i;
  int c;

  (void)c;

  i = b_pix;
  while (i < WINDOW_HEIGHT)
    my_mlx_pixel_put(data, ray, i++, 0xB99470FF); // floor
  i = 0;
  while (i < t_pix)
    my_mlx_pixel_put(data, ray, i++, 0x89CFF3FF); // ceiling
}

int get_color(t_data *data,
              int collision_orientation) // get the color of the wall
{
  data->ray->angle_rd = nor_angle(data->ray->angle_rd); // normalize the angle
  if (collision_orientation == VERTICAL) {
    if (data->ray->angle_rd > M_PI / 2 && data->ray->angle_rd < 3 * (M_PI / 2))
      return (0xB5B5B5FF); // west wall
    else
      return (0xB5B5B5FF); // east wall
  } else {
    if (data->ray->angle_rd > 0 && data->ray->angle_rd < M_PI)
      return (0xF5F5F5FF); // south wall
    else
      return (0xF5F5F5FF); // north wall
  }
}

void draw_wall(t_data *data, int ray, int t_pix, int b_pix) // draw the wall
{
  int color;

  color = get_color(data, data->ray->wall_collision_orientation);
  while (t_pix < b_pix)
    my_mlx_pixel_put(data, ray, t_pix++, color);
}

void render_wall(t_data *data, int ray) // render the wall
{
  double wall_h;
  double b_pix;
  double t_pix;

  data->ray->length *=
      cos(nor_angle(data->ray->angle_rd -
                    data->player->orientation_angle_rd)); // fix the fisheye
  wall_h = (TILE_SIZE / data->ray->length) *
           ((WINDOW_WIDTH / 2) /
            tan(data->player->fov_rd / 2));   // get the wall height
  b_pix = (WINDOW_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
  t_pix = (WINDOW_HEIGHT / 2) - (wall_h / 2); // get the top pixel
  if (b_pix > WINDOW_HEIGHT)                  // check the bottom pixel
    b_pix = WINDOW_HEIGHT;
  if (t_pix < 0) // check the top pixel
    t_pix = 0;
  draw_wall(data, ray, t_pix, b_pix);          // draw the wall
  draw_floor_ceiling(data, ray, t_pix, b_pix); // draw the floor and the ceiling
}

// #################################################################################//
// ############################## THE RAYCASTING CODE
// ##############################//
// #################################################################################//

int unit_circle(float angle, char c) // check the unit circle
{
  if (c == 'x') {
    if (angle > 0 && angle < M_PI)
      return (1);
  } else if (c == 'y') {
    if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
      return (1);
  }
  return (0);
}

int inter_check(float angle, float *inter, float *step,
                int is_horizon) // check the intersection
{
  if (is_horizon) {
    if (angle > 0 &&
        angle < M_PI) // if we look down on the map (behind the player)
    {
      *inter += TILE_SIZE;
      return (-1);
    }
    *step *= -1;
  } else {
    if (!(angle > M_PI / 2 &&
          angle < 3 * M_PI / 2)) // if we look right on the map
    {
      *inter += TILE_SIZE;
      return (-1);
    }
    *step *= -1;
  }
  return (1);
}

int wall_hit(float x, float y, t_data *data) // check the wall hit
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

float get_h_inter(t_data *data, float angl) // get the horizontal intersection
{
  float h_x;
  float h_y; // y-coordinate of the horizontal intersection point of the ray
             // with a wall.
  float x_step;
  float y_step;
  int pixel;

  y_step = TILE_SIZE;
  x_step = TILE_SIZE / tan(angl);
  // calculates the y-coordinate of the bottom edge of the grid cell in which
  // the player is currently located, effectively aligning the intersection
  // point with the horizontal grid lines in the game world
  h_y = floor(data->player->y_pos_px / TILE_SIZE) * TILE_SIZE;
  pixel = inter_check(angl, &h_y, &y_step, 1);
  h_x = data->player->x_pos_px + (h_y - data->player->y_pos_px) / tan(angl);
  if ((unit_circle(angl, 'y') && x_step > 0) ||
      (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
    x_step *= -1;
  while (wall_hit(h_x, h_y - pixel,
                  data)) // check the wall hit whit the pixel value
  {
    h_x += x_step;
    h_y += y_step;
  }
  return (sqrt(pow(h_x - data->player->x_pos_px, 2) +
               pow(h_y - data->player->y_pos_px, 2))); // get the distance
}

float get_v_inter(t_data *data, float angl) // get the vertical intersection
{
  float v_x;
  float v_y;
  float x_step;
  float y_step;
  int pixel;

  x_step = TILE_SIZE;
  y_step = TILE_SIZE * tan(angl);
  v_x = floor(data->player->x_pos_px / TILE_SIZE) * TILE_SIZE;
  pixel = inter_check(angl, &v_x, &x_step,
                      0); // check the intersection and get the pixel value
  v_y = data->player->y_pos_px + (v_x - data->player->x_pos_px) * tan(angl);
  if ((unit_circle(angl, 'x') && y_step < 0) ||
      (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
    y_step *= -1;
  while (wall_hit(v_x - pixel, v_y,
                  data)) // check the wall hit whit the pixel value
  {
    v_x += x_step;
    v_y += y_step;
  }
  return (sqrt(pow(v_x - data->player->x_pos_px, 2) +
               pow(v_y - data->player->y_pos_px, 2))); // get the distance
}

void cast_rays(t_data *data) // cast the rays
{
  double h_inter;
  double v_inter;
  int ray;

  ray = 0;
  data->ray->angle_rd = data->player->orientation_angle_rd -
                        (data->player->fov_rd / 2); // the start angle
  while (ray < WINDOW_WIDTH)                        // loop for the rays
  {
    data->ray->wall_collision_orientation = VERTICAL;
    h_inter = get_h_inter(
        data,
        nor_angle(data->ray->angle_rd)); // get the horizontal intersection
    v_inter = get_v_inter(
        data, nor_angle(data->ray->angle_rd)); // get the vertical intersection
    if (v_inter <= h_inter)                    // check the distance
      data->ray->length = v_inter;             // get the distance
    else {
      data->ray->length = h_inter; // get the distance
      data->ray->wall_collision_orientation = HORIZONTAL;
    }
    render_wall(data, ray); // render the wall
    ray++;                  // next ray
    data->ray->angle_rd += (data->player->fov_rd / WINDOW_WIDTH); // next angle
  }
}

// ##############################################################################################//
// ############################## START THE GAME AND THE GAME LOOP
// ##############################//
// ##############################################################################################//

void game_loop(void *ml) // game loop
{
  t_data *data;

  data = ml;                              // cast to the data structure
  mlx_delete_image(data->mlx, data->img); // delete the image
  data->img = mlx_new_image(data->mlx, WINDOW_WIDTH,
                            WINDOW_HEIGHT); // create new image
  hook(data, 0, 0);                         // hook the player
  cast_rays(data);                          // cast the rays
  mlx_image_to_window(data->mlx, data->img, 0,
                      0); // put the image to the window
}

void init_the_player(t_data data) // init the player structure
{
  data.player->x_pos_px =
      data.map->p_x * TILE_SIZE +
      TILE_SIZE / 2; // player x position in pixels in the center of the tile
  data.player->y_pos_px =
      data.map->p_y * TILE_SIZE +
      TILE_SIZE / 2; // player y position in pixels in the center of the tile
  data.player->fov_rd = (FOV * M_PI) / 180; // field of view in radians
  data.player->orientation_angle_rd = M_PI; // player angle
  // the rest of the variables are initialized to zero by calloc
}

void start_the_game(t_map *map, char *map_argv) // start the game
{
  t_data data;

  (void)map_argv;
  // load_textures(&data, map_argv);

  data.map = map; // init the data structure
  data.player =
      calloc(1, sizeof(t_player)); // init the player structure i'm using calloc
                                   // to initialize the variables to zero
  data.ray = calloc(1, sizeof(t_ray)); // init the ray structure
  data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D",
                      0);                     // init the data pointer
  init_the_player(data);                      // init the player structure
  mlx_loop_hook(data.mlx, &game_loop, &data); // game loop
  mlx_key_hook(data.mlx, &mlx_key, &data);    // key press and release
  mlx_loop(data.mlx);                         // data loop
  ft_exit(&data);                             // exit the game
}

// ################################################################################################//
// ############################## THE MAIN FUNCTION AND INIT THE MAP
// ##############################//
// ################################################################################################//

t_map *init_argumet() // init the data structure
{
  t_map *map = calloc(1, sizeof(t_map));              // init the data structure
  map->grid = calloc(10, sizeof(char *));             // init the map
  map->grid[0] = strdup("1111111111111111111111111"); // fill the map
  map->grid[1] = strdup("1000000000000000000100001");
  map->grid[2] = strdup("1001000000000P00000000001");
  map->grid[3] = strdup("1001000000000000001000001");
  map->grid[4] = strdup("1001000000000000001000001");
  map->grid[5] = strdup("1001000000100000001000001");
  map->grid[6] = strdup("1001000000000000001000001");
  map->grid[7] = strdup("1001000000001000001000001");
  map->grid[8] = strdup("1111111111111111111111111");
  map->grid[9] = NULL;
  map->p_y = 3;    // player y position in the map
  map->p_x = 14;   // player x position in the map
  map->w_map = 25; // map width
  map->h_map = 9;  // map height
  return (map);    // return the data structure
}

void v() { system("leaks mini_cub3D"); }

int main(int argc, char **argv) {
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