#ifndef PARSER_H
#define PARSER_H

void process_map_elements(char *line, int *i, t_data *data,
                          t_map_elements_check *elements);
void process_map_content(char **lines_arr, t_data *data, int first_line);
void process_map(char **lines_arr, t_data *data);
void free_str_arr(char **str_arr);
void init_elements_status(t_map_elements_check *elements);
t_map *init_map(t_map *map);

int find_max_width(char **lines_arr, int current_max_width);
int calculate_height(char **lines_arr, int first_line);
int has_only_valid_chars(char *line);
int is_surrounded_by_walls(char **lines_arr, int current_line, int first_line,
                           int last_line);
int spaces_are_surrounded_by_walls(char **lines_arr, int current_line,
                                   int first_line, int last_line);
void print_lines_arr(char **lines_arr);
void free_lines_arr_and_exit(char **lines_arr, char *error_message);

#endif