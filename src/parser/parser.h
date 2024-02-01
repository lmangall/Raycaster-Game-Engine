typedef enum
{
	NOT_FOUND,
	FOUND
}				e_status;

typedef struct s_map_elements
{
	e_status	no;
	e_status	so;
	e_status	we;
	e_status	ea;
	e_status	c;
	e_status	f;
}				t_map_elements;

void			process_map_elements(char *line, int *i, t_data *data,
					t_map_elements *elements);
void			process_map_content(char **lines_arr, t_data *data,
					int first_line);
void			process_map(char **lines_arr, t_data *data);
void			free_str_arr(char **str_arr);
void			init_elements_status(t_map_elements *elements);
void			init_map(t_map *map);
void			init_textures_paths(t_textures_paths *textures_paths);

int				find_max_width(char **lines_arr, int current_max_width);
int				calculate_height(char **lines_arr, int first_line);