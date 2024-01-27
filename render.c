
#include"cub3d.h"

void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color) // put the pixel
{
 if (x < 0) // check the x position
  return ;
 else if (x >= S_W)
  return ;
 if (y < 0) // check the y position
  return ;
 else if (y >= S_H)
  return ;
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

void render_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
 int  i;
 int  c;

 (void)c;

 i = b_pix;
 while (i < S_H)
  my_mlx_pixel_put(mlx, ray, i++, 0xB99470FF); // floor
 i = 0;
 while (i < t_pix)
  my_mlx_pixel_put(mlx, ray, i++, 0x89CFF3FF); // ceiling
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

static double	get_pixel(mlx_texture_t	*texture, t_mlx *mlx)
{
	double pixel;

	if (mlx->ray->is_wall)
		pixel = (int)fmodf((mlx->ray->horizontal_x * (texture->width / TILE_SIZE)), texture->width);
	else
		pixel = (int)fmodf((mlx->ray->vertical_y * (texture->width / TILE_SIZE)), texture->width);
	return (pixel);
}


void	render_wall(t_mlx *mlx,  int ray, int t_pix, int b_pix, int wall_h)//, double wall_h)
{
	double			pixel;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;


	texture = mlx->textures->no;//get_texture(mlx, mlx->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = texture->height / wall_h;
	pixel = get_pixel(texture, mlx);
	y_o = (t_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, ray, t_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)pixel]));
		y_o += factor;
		t_pix++;
	}
}

void render_line(t_mlx *mlx, int ray) // render the wall
{
 double wall_h;
 double b_pix;
 double t_pix;

 mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // fix the fisheye
 wall_h = (TILE_SIZE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->ply->fov_rd / 2)); // get the wall height
 b_pix = (S_H / 2) + (wall_h / 2); // get the bottom pixel
 t_pix = (S_H / 2) - (wall_h / 2); // get the top pixel
 if (b_pix > S_H) // check the bottom pixel
  b_pix = S_H;
 if (t_pix < 0) // check the top pixel
  t_pix = 0;
 render_wall(mlx, ray, t_pix, b_pix, wall_h); // draw the wall
 render_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}
