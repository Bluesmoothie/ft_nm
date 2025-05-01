/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:36 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 14:28:21 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		list_symbols(t_context *ctx, size_t index);
static void		print_symbol(t_context *ctx, size_t link, void *sym);
static t_symbol	get_symbol_infos(t_context *ctx, void *sym);

static void	process_symbol_sections(t_context *ctx)
{
	if (ctx->filetype == ELFCLASS32)
	{
		for (size_t i = 0;i < ctx->elf32.file_header->e_shnum;i++)
			if (ctx->elf32.section_header[i].sh_type == SHT_SYMTAB || ctx->elf32.section_header[i].sh_type == SHT_DYNSYM)
				list_symbols(ctx, i);
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		for (size_t i = 0;i < ctx->elf64.file_header->e_shnum;i++)
			if (ctx->elf64.section_header[i].sh_type == SHT_SYMTAB || ctx->elf64.section_header[i].sh_type == SHT_DYNSYM)
				list_symbols(ctx, i);
	}
}

static void	list_symbols(t_context *ctx, size_t index)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;

	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = ctx->file + ctx->elf32.section_header[index].sh_offset;
		for (size_t i = 0;i < ctx->elf32.section_header[index].sh_size;sym32++)
		{
			print_symbol(ctx, ctx->elf32.section_header[index].sh_link, sym32);
			i += sizeof(Elf32_Sym);
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = ctx->file + ctx->elf64.section_header[index].sh_offset;
		for (size_t i = 0;i < ctx->elf64.section_header[index].sh_size;sym64++)
		{
			print_symbol(ctx, ctx->elf64.section_header[index].sh_link, sym64);
			i += sizeof(Elf64_Sym);
		}
	}
}

static void	print_symbol(t_context *ctx, size_t link, void *sym)
{
	const t_symbol	symbol = get_symbol_infos(ctx, sym);

	if (symbol.type == '?')
		return ;
	if (ctx->filetype == ELFCLASS32)
	{
		
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		
	}
}

static t_symbol	get_symbol_infos(t_context *ctx, void *sym)
{
	t_symbol	symbol;

	symbol.type = get_symbol_type(ctx, sym);
	symbol.name = get_symbol_name(ctx, sym, &symbol);
	symbol.value = get_symbol_value(ctx, sym, &symbol);
}
