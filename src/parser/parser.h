#ifndef PARSER_H
# define PARSER_H




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
int				has_only_valid_chars(char *line);
int				is_surrounded_by_walls(char **lines_arr, int current_line,
					int first_line, int last_line);
int				spaces_are_sourrounded_by_walls(char **lines_arr,
					int current_line, int first_line, int last_line);

#endif