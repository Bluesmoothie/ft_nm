/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:36 by ygille            #+#    #+#             */
/*   Updated: 2025/04/29 20:35:58 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	get_section_header(t_context *ctx);
static void	get_symbol_sections(t_context *ctx);

void	process(t_context *ctx)
{
	get_section_header(ctx);
	get_symbol_sections(ctx);
}

static void	get_section_header(t_context *ctx)
{
	const Elf32_Ehdr	*header32 = ctx->file;
	const Elf64_Ehdr	*header64 = ctx->file;
	
	if (ctx->filetype == ELFCLASS32)
	{
		ctx->sh_offset = header32->e_shoff;
		ctx->sh_num = header32->e_shnum;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		ctx->sh_offset = header64->e_shoff;
		ctx->sh_num = header64->e_shnum;
	}
}

static void	get_symbol_sections(t_context *ctx)
{
	const Elf32_Shdr	*section32 = ctx->file + ctx->sh_offset;
	const Elf64_Shdr	*section64 = ctx->file + ctx->sh_offset;

	if (ctx->filetype == ELFCLASS32)
	{
		for (size_t i = 0;i < ctx->sh_num;i++)
		{
			if (section32->sh_type == SHT_SYMTAB)
				printf("Found sym table at %u\n", section32->sh_offset);
			else if (section32->sh_type == SHT_DYNSYM)
				printf("Found dyn sym table at %u\n", section32->sh_offset);
			section32++;
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		for (size_t i = 0;i < ctx->sh_num;i++)
		{
			if (section64->sh_type == SHT_SYMTAB)
				printf("Found sym table at %lu\n", section64->sh_offset);
			else if (section64->sh_type == SHT_DYNSYM)
				printf("Found dyn sym table at %lu\n", section64->sh_offset);
			section64++;
		}
	}
}
