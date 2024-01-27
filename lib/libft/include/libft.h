/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:54:17 by lmangall          #+#    #+#             */
/*   Updated: 2023/06/11 11:22:48 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

//the following is for GNL
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

/**
* @brief Checks for an alphabetic character.
* @param arg to check
* @return 0	If the parameter isn't an alphabet
* "NonZero"	If the parameter is an alphabet.
*/
int		ft_isalpha(int argument);

/**
* @brief Checks whether a character is numeric (0-9).
* @param arg to check
* @return 0 if not a numeric character
* "NonZero"	if numeric.
*/
int		ft_isdigit(int arg);

/**
* @brief Checks whether the argument is an alphanumeric character 
* @param arg to check
* @return Returns 0 if argument is neither an alphabet nor a digit.
* Returns "NonZero" if argument is an alphanumeric character.
*/
int		ft_isalnum(int arg);

/**
* @brief Checks whether arg fits into the ASCII character set.
* @param arg to check
* @return non-zero value if passed value is an ascii character
* otherwise zero.
*/
int		ft_isascii(int arg);

/**
* @brief Checks whether a character is a printable character.
* @param arg to check
* @return returns non-zero int for printable, returns 0 for unprintable.
*/
int		ft_isprint(int argument);

/**
* @brief Calculates  the  length of the string pointed to by s
* excluding the terminating  null byte ('\0').
* @return The number of bytes in the string pointed to by s.
*/
size_t	ft_strlen(const char *arg);

/**
* @brief Convert lowercase letters to uppercase
* @param char letter to convert
* @return Converted letter or arg if not possible
*/
int		ft_toupper(int arg);

/**
* @brief Convert luppercase letters to lowercase
* @param char letter to convert
* @return Converted letter or arg if not possible
*/
int		ft_tolower(int arg);

/**
* @brief Returns a pointer to the first occurrence of the character c 
*in the string s. 
* @param str - String to be scanned.
* @param c Character to be searched in str
* @return return a pointer to the matched character 
*or NULL if the character is not found
*/
char	*ft_strchr(const char *str, int c);

/**
* @brief Returns a pointer to the last occurrence of the character c 
*in the string s. 
* @param str - String to be scanned.
* @param c Character to be searched in str
* @return return a pointer to the matched character 
*or NULL if the character is not found
*/
char	*ft_strrchr(char *str, int c);

/**
* @brief Compares the two strings s1 and s2. 
 * @param str1 String 1
 * @param str2 String 2
* @return It returns an integer less than, equal to, or greater than zero 
*if s1 is found, respectively, to be less than, to match, 
*or be greater than s2. */
int		ft_strcmp(const char *str1, const char *str2);

/**
* @brief Compares the first (at most) n bytes of s1 and s2. 
* @param str1 − This is the first string to be compared.
* @param str2 − This is the second string to be compared.
* @param n − The maximum number of characters to be compared.
* @return It returns an integer less than, equal to, or greater than zero 
*if s1 is found, respectively, to be less than, to match, 
*or be greater than s2. 
*/
int		ft_strncmp(const char *str1, const char *str2, size_t n);

/**
* @brief Fills the first n bytes of the memory area 
*pointed to by s with the constant byte c.
* @param str: Starting address of memory to be filled
* @param Val to be filled
* @param len of bytes to be filled starting
* @return void
*/
void	*ft_memset(void *s, int c, size_t n);

/**
* @brief Erases the data in the n bytes of the memory starting 
*at the location pointed to by s by writing zeros ('\0')
* @param str: str that you want to fill with zeros
* @param len: The number of bytes to fill
* @return void
*/
void	ft_bzero(void *str, size_t len);

/**
* @brief Copies n characters from memory area src to memory area dest.
* @param dst − Pointer to the destination array where the
* content is to be copied, type-casted to a pointer of type void*.
* @param src − Pointer to the source of data to be copied, type-casted
* to a pointer of type void*
* @param n − This is the number of bytes to be copied.
* @return void
*/
void	*ft_memcpy(void *dst, const void *src, size_t n);

/**
* @brief copies n characters from str2 to str1
*The memory areas may overlap:
*the bytes in src are first copied into a temporary array 
*that does not overlap src or dest
* @param dst − Pointer to the destination array where the
* content is to be copied, type-casted to a pointer of type void*.
* @param src − Pointer to the source of data to be copied,
* type-casted to a pointer of type void*.
* @param len − This is the number of bytes to be copied
* @return void
*/
void	*ft_memmove(void *dst, void *src, size_t len);

/**
* @brief takes the full size of the buffer, not only the length,
* and terminates the result with NUL as long as size is greater than 0.
* Include a byte for the NUL in your size value.
* @param des - Pointer to the destination area of memory
* @param src - Pointer to the source area of memory
* @param len - Buffer size in bytes
* @return Total length of the string that would have been copied if
* there was unlimited space.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t len);

/**
* @brief Appends the NULL-terminated string src to the end of dst. It will
* append at most size - strlen(dst) - 1 bytes, NUL-terminating the result.
* @param dst - Pointer to the destination area of memory
* @param src - Pointer to the source area of memory
* @param len - Buffer size in bytes
* @return Total length of the string that would have been copied if
* there was unlimited space.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t len);

/**
* @brief locates the first occurrence of the null-terminated
* string little in the null-terminated string big.
* @param haystack - String to be searched by `little`
* @param needle - String to search in `big`
* @param len - Number of bytes to search
* @return If little is an empty string, big is returned; if little occurs
* nowhere * in big, NULL is returned; otherwise a pointer to the first
* character of the first occurrence of little is returned.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/**
* @brief searches for the first occurrence of the character c (an unsigned
* char) in the first n bytes of the string pointed to, by the argument str.
* @param str Pointer to the block of memory where the search is performed.
* @param val - Value to be located. The value is passed as an int, but the
* function performs a byte per byte search using the unsigned char
* conversion of this value.
* @param len - Number of bytes to be analyzed. size_t is an unsigned
* integral type.
* @return This function returns a pointer to the matching byte or NULL
* if the character does not occur in the given memory area.
*/
void	*ft_memchr(const void *s, int c, size_t n);

/**
* @brief Compares the first n bytes of memory area str1 and memory area str2
* @param str1 − This is the pointer to a block of memory.
* @param str2 − This is the pointer to a block of memory.
* @param len − This is the number of bytes to be compared.
* @return if Return value < 0 then it indicates str1 is less than str2.
*if Return value > 0 then it indicates str2 is less than str1.
*if Return value = 0 then it indicates str1 is equal to str2.
*/
int		ft_memcmp(const void *str1, const void *str2, size_t len);

/**
* @brief converts the string argument str to an integer (type int).
* @param str − This is the string representation of an integral number.
* @return This function returns the converted integral number as an int
* value. If no valid conversion could be performed, it returns zero.
*/
int		ft_atoi(const char *str);

/**
* @brief allocates the requested memory and returns a pointer to it.
* The difference in malloc and calloc is that malloc does not set the
* memory to zero where as calloc sets allocated memory to zero.
* @param nitems − This is the number of elements to be allocated.
* @param len - This is the size of elements.
* @return void
*/
void	*ft_calloc(size_t nitems, size_t len);

/**
* @brief Allocates with malloc and returns a string
* representing the integer received as an argument.
* Negative numbers must be handled.
* Is used to convert int data type to string data type in C.
* @param n: the integer to convert
* @return The string representing the integer.
* NULL if the allocation fails.
*/
char	*ft_itoa(int n);

/**
* @brief Duplicate String
* @param Pointer to start of the string to be copied
* @return A pointer to a new string
*/
char	*ft_strdup(const char *src);

/**
* @brief Allocates (with malloc(3)) and returns a substring
*from the string ’s’. The substring begins at index ’start’
*and is of maximum size ’len’.
* @param s: The string from which to create the substring.
* @param start: The start index of the substring in the string ’s’.
* @param len: The maximum length of the substring.
* @return The substring. NULL if the allocation fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
* @brief Allocates with malloc and returns a new string, 
* which is the result of the concatenation of ’s1’ and ’s2’.
* @param s1: The prefix string.
* @param s2: The suffix string.
* @return The new string.NULL if the allocation fails.
*/
char	*ft_strjoin(const char *s1, const char *s2);

/**
* @brief Allocates with malloc and returns a copy of
*’s1’ with the characters specified in ’set’ removed
*from the beginning and the end of the string.
* @param s1: The string to be trimmed.
* @param set: The reference set of characters to trim.
* @return The trimmed string.
* NULL if the allocation fails.
*/
char	*ft_strtrim(char const *s1, char const *set);

/**
* @brief Allocates (with malloc(3)) and returns an array
*of strings obtained by splitting ’s’ using the
*character ’c’ as a delimiter. The array must end
*with a NULL pointer.
* @param str: The string to be split.
* @param c: The delimiter character.
* @return The array of new strings resulting from the split.
* NULL if the allocation fails.
*/
char	**ft_split(char const *str, char c);

/**
* @brief Applies the function ’f’ to each character of the
* string ’s’, and passing its index as first argument
* to create a new string with malloc resulting
* from successive applications of ’f’.
* @param s: The string on which to iterate.
* @param f: The function to apply to each character.
* @return The string created from the successive applications
* of ’f’. *Returns NULL if the allocation fails.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
* @brief Applies the function ’f’ on each character of
* the string passed as argument, passing its index
* as first argument. Each character is passed by
* address to ’f’ to be modified if necessary.
* @param s: The string on which to iterate.
* @param f: The function to apply to each character.
* @return void
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
* @brief Outputs the character ’c’ to the given file
* descriptor.
* @param c: The character to output.
* @param fd: The file descriptor on which to write.
* @return void
*/
int		ft_putchar_fd(char c, int fd);

/**
* @brief Outputs the string ’s’ to the given file
* descriptor.
* @param s: The string to output.
* @param fd: The file descriptor on which to write.
* @return number of chars printed (1)
*/
int		ft_putstr_fd(char *s, int fd);

/**
* @brief Outputs the string ’s’ to the given file descriptor
* followed by a newline.
* @param s: The string to output.
* @param fd: The file descriptor on which to write.
* @return number of chars printed
*/
void	ft_putendl_fd(char *s, int fd);

/**
* @brief Outputs the integer ’n’ to the given file descriptor.
* @param n: The integer to output.
* @param fd: The file descriptor on which to write.
* @return number of chars printed (1)
*/
int		ft_putnbr_fd(int n, int fd);

/**
 * @brief Verify in string if there is any space or similar char
 * @param c
 * @return int. (0) if not space
 */
int		ft_isspace(int c);

// size_t	ft_strlen(char *s);
// char	*ft_strchr(char *s, int c);
// char	*ft_strjoin(char *stored_s, char *buff);

//extra for GNL:
char	*stored_s_to_str(char *stored_s);
char	*new_stored_s(char	*stored_s);
char	*get_next_line(int fd);
char	*read_to_stored_s(int fd, char *stored_s);

//extra for ft_printf:
int		putnbr_with_itoa(int nbr);
int		putunbr_with_itoa(unsigned int nbr);

#endif