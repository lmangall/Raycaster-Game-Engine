
#include"cub3d.h"

void my_mlx_pixel_put(t_mlx *mlx, int y, int color) // put the pixel
{
 if (y < 0) // check the y position
  return ;
 else if (y >= S_H)
  return ;
 mlx_put_pixel(mlx->img, mlx->ray->screen_x, y, color); // put the pixel
}

float nor_angle(float angle) // normalize the angle
{
 if (angle < 0)
  angle += (2 * M_PI);
 if (angle > (2 * M_PI))
  angle -= (2 * M_PI);
 return (angle);
}

void render_floor_ceiling(t_mlx *mlx, int t_pix, int b_pix) // draw the floor and the ceiling
{
 int  i;
 int  c;

 (void)c;

 i = b_pix;
 while (i < S_H)
  my_mlx_pixel_put(mlx, i++, 0xB99470FF); // floor
 i = 0;
 while (i < t_pix)
  my_mlx_pixel_put(mlx, i++, 0x89CFF3FF); // ceiling
}



// int get_color(t_mlx *mlx, int is_wall) // get the color of the wall
// {
//  mlx->ray->ray_ngl = nor_angle(mlx->ray->ray_ngl); // normalize the angle
//  if (is_wall == 0)
//  {
//   if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
//    return (0xB5B5B5FF); // west wall
//   else
//    return (0xB5B5B5FF); // east wall
//  }
//  else
//  {
//   if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
//    return (0xF5F5F5FF); // south wall
//   else
//    return (0xF5F5F5FF); // north wall
//  }
// }


int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}



uint32_t	pixel_color(mlx_texture_t *texture, t_mlx *mlx, int t_pix)
{
    double x_pixel_coordinate;
	double y_pixel_coordinate;
	double factor;
	uint32_t *pixel_array;
	uint32_t color;

    if (mlx->ray->is_wall)
        x_pixel_coordinate = (int)fmodf((mlx->ray->horizontal_x * (texture->width / TILE_SIZE)), texture->width);
    else
        x_pixel_coordinate = (int)fmodf((mlx->ray->vertical_y * (texture->width / TILE_SIZE)), texture->width);

	pixel_array = (uint32_t *)texture->pixels;

	factor = (double)texture->height / mlx->ray->wall_h;
	y_pixel_coordinate = (t_pix - (S_H / 2) + (mlx->ray->wall_h / 2)) * factor;
	if (y_pixel_coordinate < 0)
		y_pixel_coordinate = 0;

color = pixel_array[(int)y_pixel_coordinate * texture->width + (int)x_pixel_coordinate];
color = reverse_bytes(color);

    return (color);
}


void	render_wall(t_mlx *mlx, int t_pix)
{
	uint32_t		color;
	mlx_texture_t *texture = mlx->ray->current_texture;

	while (t_pix < mlx->ray->b_pix)
	{
		color = pixel_color(texture, mlx, t_pix); 
		my_mlx_pixel_put(mlx, t_pix, color);
		t_pix++;
	}
}

void render_line(t_mlx *mlx) // render the wall
{
 double wall_h;
 double b_pix;
 double t_pix;

 mlx->ray->distance *= cos(nor_angle(mlx->ray->angle - mlx->ply->angle)); // fix the fisheye
 wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2)); // get the wall height
 b_pix = (S_H / 2) + (wall_h / 2); // get the bottom pixel
 t_pix = (S_H / 2) - (wall_h / 2); // get the top pixel
 if (b_pix > S_H) // check the bottom pixel
  b_pix = S_H;
 if (t_pix < 0) // check the top pixel
  t_pix = 0;


mlx->ray->current_texture = mlx->textures->no;
mlx->ray->wall_h = wall_h;
mlx->ray->t_pix = t_pix;
mlx->ray->b_pix = b_pix;
 render_wall(mlx, t_pix); // draw the wall
 render_floor_ceiling(mlx, t_pix, b_pix); // draw the floor and the ceiling
}
