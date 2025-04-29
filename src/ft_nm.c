/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:07:45 by ygille            #+#    #+#             */
/*   Updated: 2025/04/29 20:30:22 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	open_file(t_context *ctx ,char *file);
static void	get_file_type(t_context *ctx);

void	ft_nm(char *file)
{
	t_context	ctx;

	open_file(&ctx, file);
	get_file_type(&ctx);
	switch (ctx.filetype)
	{
		case	ELFCLASS32:
		case	ELFCLASS64:
			process(&ctx);
			break;
		default:
			ft_printf("nm: %s: file format not recognized\n", file);
			break;
	}
	munmap_helper(ctx.file, ctx.filesize);
}

static void	open_file(t_context *ctx ,char *file)
{
	const int	fd = open_helper(file);
	struct stat	infos;

	fstat(fd, &infos);
	ctx->file = mmap_helper(infos.st_size, fd);
	ctx->filesize = infos.st_size;
	close(fd);
}

static void	get_file_type(t_context *ctx)
{
	Elf32_Ehdr	*header;

	ctx->filetype = ELFCLASSNONE;
	header = ctx->file;
	if (!ft_memcmp(header->e_ident, ELFMAG, SELFMAG))
		ctx->filetype = header->e_ident[EI_CLASS];
}
