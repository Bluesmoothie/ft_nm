/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:07:59 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 16:08:37 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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

void	get_str_value(t_symbol *symbol)
{
	size_t	val;
	int		i;
	
	symbol->strvalue[16] = '\0';
	if (symbol->type == 'w' || symbol->type == 'W' || symbol->type == 'u' || symbol->type == 'U')
	{
		ft_memset(&symbol->strvalue, ' ', 16);
		return ;
	}
	ft_memset(&symbol->strvalue, '0', 16);
	val = symbol->value;
	i = 15;
	while (val)
	{
		symbol->strvalue[i] = LOW_BASE_HEX[val % 16];
		val /= 16;
		i--;
	}
}
