/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:03:49 by slombard          #+#    #+#             */
/*   Updated: 2024/01/29 12:03:53 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Reallocates a memory block to a new size.
 *
 * @param ptr The pointer to the currently allocated memory block.
 * @param old_size The size of the currently allocated memory block.
 * @param new_size The size of the new memory block to allocate.
 * @return void* A pointer to the newly allocated memory block,
 * or NULL if the allocation fails.
 *

	* This function reallocates the memory block pointed to by `ptr` to be `new_size` bytes while preserving the content

	* that was present in the old memory block up to the minimum of the old and new sizes. It frees the old block of memory.
 * If `new_size` is 0,
	it frees the memory block and returns NULL. If `ptr` is NULL,
	it behaves like malloc.
 */

void	*ft_easy_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
