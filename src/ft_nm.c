/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:07:45 by ygille            #+#    #+#             */
/*   Updated: 2025/05/06 12:48:08 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	open_file(t_context *ctx ,char *file);
static void	get_file_type(t_context *ctx);
static void	get_file_headers(t_context *ctx);

/*
**	Detect file type, print error and abort if incorrect
*/
void	ft_nm(char *file)
{
	t_context	ctx;

	ft_bzero(&ctx, sizeof(t_context));
	open_file(&ctx, file);
	get_file_type(&ctx);
	switch (ctx.filetype)
	{
		case	ELFCLASS32:
		case	ELFCLASS64:
			get_file_headers(&ctx);
			process_symbols_section(&ctx);
			if (ctx.symbols)
			{
				// order_symbols(&ctx);
				print_symbols(&ctx);
			}
			break;
		default:
			ft_printf("nm: %s: file format not recognized\n", file);
			break;
	}
	munmap_helper(ctx.file, ctx.filesize);
	ft_lstclear(&ctx.symbols, free);
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

/*
**	Initialize pointers to importants sections
*/
static void	get_file_headers(t_context *ctx)
{
	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Shdr	*strtab_section;

		ctx->elfX.elf32.file_header = ctx->file;
		ctx->elfX.elf32.section_header = ctx->file + ctx->elfX.elf32.file_header->e_shoff;
		strtab_section = ctx->elfX.elf32.section_header + ctx->elfX.elf32.file_header->e_shstrndx;
		ctx->strtab = ctx->file + strtab_section->sh_offset;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Shdr	*strtab_section;

		ctx->elfX.elf64.file_header = ctx->file;
		ctx->elfX.elf64.section_header = ctx->file + ctx->elfX.elf64.file_header->e_shoff;
		strtab_section = ctx->elfX.elf64.section_header + ctx->elfX.elf64.file_header->e_shstrndx;
		ctx->strtab = ctx->file + strtab_section->sh_offset;
	}
}
