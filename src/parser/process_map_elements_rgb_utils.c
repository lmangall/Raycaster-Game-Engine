#include "cub3d.h"
#include "parser.h"

int	char_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (SUCCESS);
	else
		return (FAILURE);
}

int	str_isdigit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!char_isdigit(str[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}