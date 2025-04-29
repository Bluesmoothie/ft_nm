/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:07:59 by ygille            #+#    #+#             */
/*   Updated: 2025/04/29 20:02:45 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	open_helper(char *file)
{
	const int	fd = open(file, O_RDONLY);

	if (fd < 1)
		pexit(PSTR);
	return (fd);
}

void	*mmap_helper(size_t len, int fd)
{
	void	*ptr;

	ptr = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd , 0);
	if (ptr == MAP_FAILED)
		pexit(PSTR);
	return (ptr);
}

void	munmap_helper(void *addr, size_t len)
{
	if(munmap(addr, len) == -1)
		pexit(PSTR);
}
