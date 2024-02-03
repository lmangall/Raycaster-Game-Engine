/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:27:34 by slombard          #+#    #+#             */
/*   Updated: 2023/02/13 18:27:45 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list			args;
	int				count;

	va_start(args, format);
	count = 0;
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ft_parse_specifier(&args, &count, *format);
			format++;
		}
		else
		{
			ft_putchar(*format, &count);
			format++;
		}
	}
	va_end(args);
	return (count);
}

void	ft_parse_specifier(va_list *args, int *count, char c)
{
	if (c == 'c')
		ft_parse_char(va_arg(*args, int), count);
	else if (c == 's')
		ft_parse_str(va_arg(*args, char *), count);
	else if (c == 'p')
		ft_parse_ptr(va_arg(*args, void *), count);
	else if (c == 'd' || c == 'i')
		ft_parse_int(va_arg(*args, int), count);
	else if (c == 'u')
		ft_parse_uint(va_arg(*args, unsigned int), count);
	else if (c == 'x')
		ft_parse_hex(va_arg(*args, int), count, c);
	else if (c == 'X')
		ft_parse_hex(va_arg(*args, int), count, c);
	else
		ft_putchar('%', count);
}

/*
int main(void)
{
	int *ptr;
	int i;
	i = 42;

	ptr = &i;
	ft_printf("Hello Pointer to %d\t%p\n", i, ptr);
	printf   ("Hello Pointer to %d\t%p\n", i, ptr);
	printf 		 ("Hello %c!\n", 'c');
	ft_printf  ("Hello %c!\n", 'c');
	printf  	 ("Hello %s!\n", "string");
	ft_printf  ("Hello %s!\n", "string");
	printf  	 ("Hello %d!\n", 42);
	ft_printf  ("Hello %d!\n", 42);
	printf  	 ("Hello %c!\n", '0');
	ft_printf  ("Hello %c!\n", '0');
	printf  	 ("Hello %c!\n", '1');
	ft_printf  ("Hello %c!\n", '1');
	printf  	 ("Hello %u!\n", -42);
	ft_printf  ("Hello %u!\n", -42);
	printf  	 ("Hello %u!\n", -1);
	ft_printf  ("Hello %u!\n", -1);
	printf  	 ("Hello %x!\n", -42);
	ft_printf  ("Hello %x!\n", -42);
	printf  	 ("Hello %X!\n", -4242);
	ft_printf  ("Hello %X!\n", -4242);
	printf  	 ("Hello %x!\n", 42);
	ft_printf  ("Hello %x!\n", 42);
	printf  	 ("Hello %X!\n", 4242);
	ft_printf  ("Hello %x!\n", 4242);
	printf  	 ("Hello %%!\n");
	ft_printf  ("Hello %%!\n");
 	printf		("NULL: %s!\n", (char *) NULL);
 	ft_printf	("NULL: %s!\n", NULL);


	return (0);
}
*/