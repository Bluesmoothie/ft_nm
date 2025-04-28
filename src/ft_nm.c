/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:07:45 by ygille            #+#    #+#             */
/*   Updated: 2025/04/28 15:56:00 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_nm(char *file)
{
	t_context	ctx;

	ctx.filetype = get_file_type(file);
	switch (ctx.filetype)
	{
		case	1:
			break;
		case	2:
			break;
		default:
			return ((void)ft_printf("nm: %s: file format not recognized\n", file));
	}
}

char	get_file_type(char *file)
{
	const int	fd = open_helper(file);
	char		class;
	Elf64_Ehdr	header;


	class = 0;
	if (read(fd, &header, sizeof(header)) != sizeof(header))
	{
		close(fd);
		exit(-1);
	}
	if (!ft_memcmp(header.e_ident, ELFMAG, SELFMAG))
		class = header.e_ident[EI_CLASS];
	close(fd);
	return(class);
}
