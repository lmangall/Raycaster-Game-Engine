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

void ft_exit(t_mlx *mlx) // exit the game
{
  int i = 0;
  while (mlx->dt->map2d[i])
    free(mlx->dt->map2d[i++]); // free the map line by line
  free(mlx->dt->map2d);        // free the map
  free(mlx->dt);               // free the data structure
  free(mlx->ply);              // free the player structure
  free(mlx->ray);              // free the ray structure
  //  free_textures(mlx->textures); // free the textures
  mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
  mlx_close_window(mlx->mlx_p);           // close the window
  mlx_terminate(mlx->mlx_p);              // terminate the mlx pointer
  printf("Game closed\n");                // print the message
  exit(0);                                // exit the game
}

// ################################################################################//
// ############################## THE MOUVEMENT CODE
// ##############################//
// ################################################################################//

void ft_reles(mlx_key_data_t keydata, t_mlx *mlx) // release the key
{
  if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
    mlx->ply->lateral_move = L_NONE;
  else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
    mlx->ply->lateral_move = L_NONE;
  else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
    mlx->ply->longitudinal_move = NONE;
  else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
    mlx->ply->longitudinal_move = NONE;
  else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
    mlx->ply->rotation = R_NONE;
  else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
    mlx->ply->rotation = R_NONE;
}

void mlx_key(mlx_key_data_t keydata, void *ml) // key press
{
  t_mlx *mlx;

  mlx = ml;
  if (keydata.key == MLX_KEY_ESCAPE &&
      (keydata.action == MLX_PRESS ||
       keydata.action == MLX_REPEAT)) // exit the game
    ft_exit(mlx);
  else if (keydata.key == MLX_KEY_A &&
           (keydata.action == MLX_PRESS)) // move left
    mlx->ply->lateral_move = L_LEFT;
  else if (keydata.key == MLX_KEY_D &&
           (keydata.action == MLX_PRESS)) // move right
    mlx->ply->lateral_move = L_RIGHT;
  else if (keydata.key == MLX_KEY_S &&
           (keydata.action == MLX_PRESS)) // move down
    mlx->ply->longitudinal_move = BACKWARD;
  else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
    mlx->ply->longitudinal_move = FORWARD;
  else if (keydata.key == MLX_KEY_LEFT &&
           keydata.action == MLX_PRESS) // rotate left
    mlx->ply->rotation = R_LEFT;
  else if (keydata.key == MLX_KEY_RIGHT &&
           keydata.action == MLX_PRESS) // rotate right
    mlx->ply->rotation = R_RIGHT;
  ft_reles(keydata, mlx); // release the key
}

void rotate_player(t_mlx *mlx, int i) // rotate the player
{
  if (i == 1) {
    mlx->ply->orientation_angle_rd += PLAYER_ROTATION_SPEED; // rotate right
    if (mlx->ply->orientation_angle_rd > 2 * M_PI)
      mlx->ply->orientation_angle_rd -= 2 * M_PI;
  } else {
    mlx->ply->orientation_angle_rd -= PLAYER_ROTATION_SPEED; // rotate left
    if (mlx->ply->orientation_angle_rd < 0)
      mlx->ply->orientation_angle_rd += 2 * M_PI;
  }
}

void move_player(t_mlx *mlx, double move_x, double move_y) // move the player
{
  int map_grid_y;
  int map_grid_x;
  int new_x;
  int new_y;

  new_x = roundf(mlx->ply->x_pos_px + move_x); // get the new x position
  new_y = roundf(mlx->ply->y_pos_px + move_y); // get the new y position
  map_grid_x = (new_x / TILE_SIZE);            // get the x position in the map
  map_grid_y = (new_y / TILE_SIZE);            // get the y position in the map
  if (mlx->dt->map2d[map_grid_y][map_grid_x] != '1' &&
      (mlx->dt->map2d[map_grid_y][mlx->ply->x_pos_px / TILE_SIZE] != '1' &&
       mlx->dt->map2d[mlx->ply->y_pos_px / TILE_SIZE][map_grid_x] !=
           '1')) // check the wall hit and the diagonal wall hit
  {
    mlx->ply->x_pos_px = new_x; // move the player
    mlx->ply->y_pos_px = new_y; // move the player
  }
}

void hook(t_mlx *mlx, double move_x, double move_y) // hook the player
{
  if (mlx->ply->rotation == R_RIGHT)
    rotate_player(mlx, 1);
  if (mlx->ply->rotation == R_LEFT)
    rotate_player(mlx, 0);
  if (mlx->ply->lateral_move == L_RIGHT) // move right
  {
    move_x = -sin(mlx->ply->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y = cos(mlx->ply->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
  }
  if (mlx->ply->lateral_move == L_LEFT) // move left
  {
    move_x = sin(mlx->ply->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y = -cos(mlx->ply->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
  }
  if (mlx->ply->longitudinal_move == FORWARD) // move up
  {
    move_x = cos(mlx->ply->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y = sin(mlx->ply->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
  }
  if (mlx->ply->longitudinal_move == BACKWARD) // move down
  {
    move_x = -cos(mlx->ply->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
    move_y = -sin(mlx->ply->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
  }
  move_player(mlx, move_x, move_y); // move the player
}

// #####################################################################################//
// ############################## THE WALL RENDERING CODE
// ##############################//
// #####################################################################################//

void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color) // put the pixel
{
  if (x < 0) // check the x position
    return;
  else if (x >= WINDOW_WIDTH)
    return;
  if (y < 0) // check the y position
    return;
  else if (y >= WINDOW_HEIGHT)
    return;
  mlx_put_pixel(mlx->img, x, y, color); // put the pixel
}

float nor_angle(float angle) // normalize the angle
{
  if (angle < 0)
    angle += (2 * M_PI);
  if (angle > (2 * M_PI))
    angle -= (2 * M_PI);
  return (angle);
}

void draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix,
                        int b_pix) // draw the floor and the ceiling
{
  int i;
  int c;

  (void)c;

  i = b_pix;
  while (i < WINDOW_HEIGHT)
    my_mlx_pixel_put(mlx, ray, i++, 0xB99470FF); // floor
  i = 0;
  while (i < t_pix)
    my_mlx_pixel_put(mlx, ray, i++, 0x89CFF3FF); // ceiling
}

int get_color(t_mlx *mlx, int flag) // get the color of the wall
{
  mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // normalize the angle
  if (flag == 0) {
    if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
      return (0xB5B5B5FF); // west wall
    else
      return (0xB5B5B5FF); // east wall
  } else {
    if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
      return (0xF5F5F5FF); // south wall
    else
      return (0xF5F5F5FF); // north wall
  }
}

void draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix) // draw the wall
{
  int color;

  color = get_color(mlx, mlx->ray->flag);
  while (t_pix < b_pix)
    my_mlx_pixel_put(mlx, ray, t_pix++, color);
}

void render_wall(t_mlx *mlx, int ray) // render the wall
{
  double wall_h;
  double b_pix;
  double t_pix;

  mlx->ray->distance *= cos(nor_angle(
      mlx->ray->ray_ngl - mlx->ply->orientation_angle_rd)); // fix the fisheye
  wall_h =
      (TILE_SIZE / mlx->ray->distance) *
      ((WINDOW_WIDTH / 2) / tan(mlx->ply->fov_rd / 2)); // get the wall height
  b_pix = (WINDOW_HEIGHT / 2) + (wall_h / 2);           // get the bottom pixel
  t_pix = (WINDOW_HEIGHT / 2) - (wall_h / 2);           // get the top pixel
  if (b_pix > WINDOW_HEIGHT) // check the bottom pixel
    b_pix = WINDOW_HEIGHT;
  if (t_pix < 0) // check the top pixel
    t_pix = 0;
  draw_wall(mlx, ray, t_pix, b_pix);          // draw the wall
  draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
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

int wall_hit(float x, float y, t_mlx *mlx) // check the wall hit
{
  int x_m;
  int y_m;

  if (x < 0 || y < 0)
    return (0);
  x_m = floor(x / TILE_SIZE); // get the x position in the map
  y_m = floor(y / TILE_SIZE); // get the y position in the map
  if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
    return (0);
  if (mlx->dt->map2d[y_m] && x_m <= (int)strlen(mlx->dt->map2d[y_m]))
    if (mlx->dt->map2d[y_m][x_m] == '1')
      return (0);
  return (1);
}

float get_h_inter(t_mlx *mlx, float angl) // get the horizontal intersection
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
  h_y = floor(mlx->ply->y_pos_px / TILE_SIZE) * TILE_SIZE;
  pixel = inter_check(angl, &h_y, &y_step, 1);
  h_x = mlx->ply->x_pos_px + (h_y - mlx->ply->y_pos_px) / tan(angl);
  if ((unit_circle(angl, 'y') && x_step > 0) ||
      (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
    x_step *= -1;
  while (wall_hit(h_x, h_y - pixel,
                  mlx)) // check the wall hit whit the pixel value
  {
    h_x += x_step;
    h_y += y_step;
  }
  return (sqrt(pow(h_x - mlx->ply->x_pos_px, 2) +
               pow(h_y - mlx->ply->y_pos_px, 2))); // get the distance
}

float get_v_inter(t_mlx *mlx, float angl) // get the vertical intersection
{
  float v_x;
  float v_y;
  float x_step;
  float y_step;
  int pixel;

  x_step = TILE_SIZE;
  y_step = TILE_SIZE * tan(angl);
  v_x = floor(mlx->ply->x_pos_px / TILE_SIZE) * TILE_SIZE;
  pixel = inter_check(angl, &v_x, &x_step,
                      0); // check the intersection and get the pixel value
  v_y = mlx->ply->y_pos_px + (v_x - mlx->ply->x_pos_px) * tan(angl);
  if ((unit_circle(angl, 'x') && y_step < 0) ||
      (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
    y_step *= -1;
  while (wall_hit(v_x - pixel, v_y,
                  mlx)) // check the wall hit whit the pixel value
  {
    v_x += x_step;
    v_y += y_step;
  }
  return (sqrt(pow(v_x - mlx->ply->x_pos_px, 2) +
               pow(v_y - mlx->ply->y_pos_px, 2))); // get the distance
}

void cast_rays(t_mlx *mlx) // cast the rays
{
  double h_inter;
  double v_inter;
  int ray;

  ray = 0;
  mlx->ray->ray_ngl = mlx->ply->orientation_angle_rd -
                      (mlx->ply->fov_rd / 2); // the start angle
  while (ray < WINDOW_WIDTH)                  // loop for the rays
  {
    mlx->ray->flag = 0; // flag for the wall
    h_inter = get_h_inter(
        mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
    v_inter = get_v_inter(
        mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
    if (v_inter <= h_inter)                 // check the distance
      mlx->ray->distance = v_inter;         // get the distance
    else {
      mlx->ray->distance = h_inter; // get the distance
      mlx->ray->flag = 1;           // flag for the wall
    }
    render_wall(mlx, ray);                                  // render the wall
    ray++;                                                  // next ray
    mlx->ray->ray_ngl += (mlx->ply->fov_rd / WINDOW_WIDTH); // next angle
  }
}

// ##############################################################################################//
// ############################## START THE GAME AND THE GAME LOOP
// ##############################//
// ##############################################################################################//

void game_loop(void *ml) // game loop
{
  t_mlx *mlx;

  mlx = ml;                               // cast to the mlx structure
  mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
  mlx->img = mlx_new_image(mlx->mlx_p, WINDOW_WIDTH,
                           WINDOW_HEIGHT); // create new image
  hook(mlx, 0, 0);                         // hook the player
  cast_rays(mlx);                          // cast the rays
  mlx_image_to_window(mlx->mlx_p, mlx->img, 0,
                      0); // put the image to the window
}

void init_the_player(t_mlx mlx) // init the player structure
{
  mlx.ply->x_pos_px =
      mlx.dt->p_x * TILE_SIZE +
      TILE_SIZE / 2; // player x position in pixels in the center of the tile
  mlx.ply->y_pos_px =
      mlx.dt->p_y * TILE_SIZE +
      TILE_SIZE / 2; // player y position in pixels in the center of the tile
  mlx.ply->fov_rd = (FOV * M_PI) / 180; // field of view in radians
  mlx.ply->orientation_angle_rd = M_PI; // player angle
  // the rest of the variables are initialized to zero by calloc
}

void start_the_game(t_map *dt, char *map_argv) // start the game
{
  t_mlx mlx;

  (void)map_argv;
  // load_textures(&mlx, map_argv);

  mlx.dt = dt; // init the mlx structure
  mlx.ply =
      calloc(1, sizeof(t_player)); // init the player structure i'm using calloc
                                   // to initialize the variables to zero
  mlx.ray = calloc(1, sizeof(t_ray)); // init the ray structure
  mlx.mlx_p =
      mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0); // init the mlx pointer
  init_the_player(mlx);                       // init the player structure
  mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx); // game loop
  mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);    // key press and release
  mlx_loop(mlx.mlx_p);                        // mlx loop
  ft_exit(&mlx);                              // exit the game
}

// ################################################################################################//
// ############################## THE MAIN FUNCTION AND INIT THE MAP
// ##############################//
// ################################################################################################//

t_map *init_argumet() // init the data structure
{
  t_map *dt = calloc(1, sizeof(t_map));               // init the data structure
  dt->map2d = calloc(10, sizeof(char *));             // init the map
  dt->map2d[0] = strdup("1111111111111111111111111"); // fill the map
  dt->map2d[1] = strdup("1000000000000000000100001");
  dt->map2d[2] = strdup("1001000000000P00000000001");
  dt->map2d[3] = strdup("1001000000000000001000001");
  dt->map2d[4] = strdup("1001000000000000001000001");
  dt->map2d[5] = strdup("1001000000100000001000001");
  dt->map2d[6] = strdup("1001000000000000001000001");
  dt->map2d[7] = strdup("1001000000001000001000001");
  dt->map2d[8] = strdup("1111111111111111111111111");
  dt->map2d[9] = NULL;
  dt->p_y = 3;    // player y position in the map
  dt->p_x = 14;   // player x position in the map
  dt->w_map = 25; // map width
  dt->h_map = 9;  // map height
  return (dt);    // return the data structure
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