/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:36 by ygille            #+#    #+#             */
/*   Updated: 2025/04/28 20:02:06 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	get_section_header(t_context *ctx, int fd);
static void	get_symbol_sections(t_context *ctx, int fd);

void	process(t_context *ctx, char *file)
{
	const int	fd = open_helper(file);
	
	get_section_header(ctx, fd);
	get_symbol_sections(ctx, fd);
	close(fd);
}

static void	get_section_header(t_context *ctx, int fd)
{
	Elf32_Ehdr	header32;
	Elf64_Ehdr	header64;
	
	if (ctx->filetype == ELFCLASS32)
	{
		if (read(fd, &header32, sizeof(header32)) != sizeof(header32))
		{
			close(fd);
			exit(-1);
		}
		else
		{
			ctx->sh_offset = header32.e_shoff;
			ctx->sh_num = header32.e_shnum;
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		if (read(fd, &header64, sizeof(header64)) != sizeof(header64))
		{
			close(fd);
			exit(-1);
		}
		else
		{
			ctx->sh_offset = header64.e_shoff;
			ctx->sh_num = header64.e_shnum;
		}
	}
}

static void	get_symbol_sections(t_context *ctx, int fd)
{
	Elf32_Shdr	*section32;
	Elf64_Shdr	*section64;

	if (ctx->filetype == ELFCLASS32)
	{
		for (size_t i = 0;i < ctx->sh_num;i++)
		{
			section32 = mmap(NULL, sizeof(Elf32_Shdr), PROT_READ, MAP_PRIVATE, fd, ctx->sh_offset + i * sizeof(Elf32_Shdr));
			printf("sh_type = %d\n", section32->sh_type);
			munmap(section32, sizeof(Elf32_Shdr));
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		for (size_t i = 0;i < ctx->sh_num;i++)
		{
			section64 = mmap(NULL, sizeof(Elf64_Shdr), PROT_READ, MAP_PRIVATE, fd, ctx->sh_offset + i * sizeof(Elf64_Shdr));
			perror(NULL);
			printf("%p\n", section64);
			printf("sh_type = %d\n", section64->sh_type);
			munmap(section64, sizeof(Elf64_Shdr));
		}
	}
}
