#ifndef ANIMATIONS_H
# define ANIMATIONS_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../lib/libft/include/libft.h"
# include "utils.h"
# include <math.h>
# include <stdio.h>

enum					fig_type
{
	CIRCLE,
	RECT
};

typedef struct s_frame
{
	int					x;
	int					y;
	int					color;
	int					figure_size;
}						t_frame;

typedef struct s_animation
{
	t_list				*frames;
	enum fig_type		fig_type;
	t_frame current_frame; // The configuration of the current frame
	int delay;             // How many fps it takes to change animation frams
	int _tmp_delay;        // Delay Iterator
	int current_frame_num; // Which frame is selected
	long int fps;          // Frames per second, this could be delayed
	long int last_updated; // When was the last update
	long int frame_count;  // The frame count
}						t_animation;

typedef struct s_rect
{
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	size_w;
	unsigned short int	size_h;
	int					color;
}						t_rect;

typedef struct s_circle
{
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	radius;
	int					color;
}						t_circle;

typedef struct s_win
{
	mlx_t				*mlx_ptr;
	int					height;
	int					width;
	t_rect				background;
}						t_win;

typedef struct s_animator
{
	t_list				*animations;
	t_win				*win;
	//   t_img *img;
	mlx_image_t			*img;
}						t_animator;
typedef struct s_img
{
	t_win				win;
	void				*img_ptr;
	char				*addr;
	int					h;
	int					w;
	int					bpp;
	int					endian;
	int					line_len;
}						t_img;

/*Window and Images*/
t_win					new_window(int w, int h, char *str);
t_img					new_img(int w, int h, t_win window);
void					put_pixel_img(t_img img, int x, int y, int color);

void					draw_rect(t_rect rect, mlx_image_t *img);
void					draw_circle(t_circle circle, mlx_image_t *img);

void					update(void *param);
t_animation				*rect_animation(int delay, int fps);
t_animation				*rect_animation_pulga(int delay, int fps);
t_animation				*ball_animation(int delay, int fps);
t_animation				*ball_animation_pulga(int delay, int fps);
t_animation				*orbit(int delay, int fps);
t_animation				*semaphore(int delay, int fps);
void					destroy_animation(void *ptr);
int						destroy_animator(t_animator *a);
// LIBFT
void					ft_lstiter_param(t_list *lst, void (*f)(void *, void *),
							void *ptr);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_back(t_list **alst, t_list *new);
t_list					*ft_lstget(t_list *lst, int index);
void					ft_lstiter(t_list *lst, void (*f)(void *));
int						ft_lstsize(t_list *lst);
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstdelone(t_list *lst, void (*del)(void *));
#endif // ANIMATIONS_H