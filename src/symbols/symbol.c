/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:36 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 16:11:45 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		list_symbols(t_context *ctx, size_t index);
static void		print_symbol(t_context *ctx, void *sym, size_t link);
static t_symbol	get_symbol_infos(t_context *ctx, void *sym, size_t link);

void	process_symbol_sections(t_context *ctx)
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
			print_symbol(ctx, sym32, ctx->elf32.section_header[index].sh_link);
			i += sizeof(Elf32_Sym);
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = ctx->file + ctx->elf64.section_header[index].sh_offset;
		for (size_t i = 0;i < ctx->elf64.section_header[index].sh_size;sym64++)
		{
			print_symbol(ctx, sym64, ctx->elf64.section_header[index].sh_link);
			i += sizeof(Elf64_Sym);
		}
	}
}

static void	print_symbol(t_context *ctx, void *sym, size_t link)
{
	const t_symbol	symbol = get_symbol_infos(ctx, sym, link);

	if (symbol.type == '?' || symbol.type == 'n' || symbol.type == 'N')
		return ;
	printf("%s %c %s\n", symbol.strvalue, symbol.type, symbol.name);
}

static t_symbol	get_symbol_infos(t_context *ctx, void *sym, size_t link)
{
	t_symbol	symbol;

	symbol.type = get_symbol_type(ctx, sym);
	symbol.name = get_symbol_name(ctx, sym, &symbol, link);
	symbol.value = get_symbol_value(ctx, sym, &symbol);
	get_str_value(&symbol);
	return (symbol);
}
