/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:07:45 by ygille            #+#    #+#             */
/*   Updated: 2025/04/28 19:44:13 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char	get_file_type(char *file);

void	ft_nm(char *file)
{
	t_context	ctx;

	ctx.filetype = get_file_type(file);
	switch (ctx.filetype)
	{
		case	ELFCLASS32:
		case	ELFCLASS64:
			process(&ctx, file);
			break;
		default:
			return ((void)ft_printf("nm: %s: file format not recognized\n", file));
	}
}

static char	get_file_type(char *file)
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
