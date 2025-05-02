/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:36 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 15:06:25 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		list_symbols(t_context *ctx, size_t index);
static void		print_symbol(t_context *ctx, void *sym, size_t link);
static t_symbol	get_symbol_infos(t_context *ctx, void *sym, size_t link);
static t_symbol	get_symbol_base_infos(t_context *ctx, void *sym);

void	process_symbol_sections(t_context *ctx)
{
	if (ctx->filetype == ELFCLASS32)
	{
		for (size_t i = 0;i < ctx->elfX.elf32.file_header->e_shnum;i++)
			if (ctx->elfX.elf32.section_header[i].sh_type == SHT_SYMTAB || ctx->elfX.elf32.section_header[i].sh_type == SHT_DYNSYM)
				list_symbols(ctx, i);
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		for (size_t i = 0;i < ctx->elfX.elf64.file_header->e_shnum;i++)
			if (ctx->elfX.elf64.section_header[i].sh_type == SHT_SYMTAB || ctx->elfX.elf64.section_header[i].sh_type == SHT_DYNSYM)
				list_symbols(ctx, i);
	}
}

static void	list_symbols(t_context *ctx, size_t index)
{
	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Sym	*symX;

		symX = ctx->file + ctx->elfX.elf32.section_header[index].sh_offset;
		for (size_t i = 0;i < ctx->elfX.elf32.section_header[index].sh_size;symX++)
		{
			print_symbol(ctx, symX, ctx->elfX.elf32.section_header[index].sh_link);
			i += sizeof(Elf32_Sym);
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Sym	*symX;

		symX = ctx->file + ctx->elfX.elf64.section_header[index].sh_offset;
		for (size_t i = 0;i < ctx->elfX.elf64.section_header[index].sh_size;symX++)
		{
			print_symbol(ctx, symX, ctx->elfX.elf64.section_header[index].sh_link);
			i += sizeof(Elf64_Sym);
		}
	}
}

static void	print_symbol(t_context *ctx, void *sym, size_t link)
{
	const t_symbol	symbol = get_symbol_infos(ctx, sym, link);

	if (symbol.id == '?' || symbol.id == 'n' || symbol.id == 'N')
		return ;
	printf("%s %c %s\n", symbol.strvalue, symbol.id, symbol.name);
}

static t_symbol	get_symbol_infos(t_context *ctx, void *sym, size_t link)
{
	t_symbol	symbol;

	symbol = get_symbol_base_infos(ctx, sym);
	symbol.id = get_symbol_type(ctx, sym);
	symbol.name = get_symbol_name(ctx, sym, &symbol, link);
	symbol.value = get_symbol_value(ctx, sym, &symbol);
	get_str_value(&symbol);
	return (symbol);
}

static t_symbol	get_symbol_base_infos(t_context *ctx, void *sym)
{
	t_symbol	symbol;

	ft_bzero(&symbol, sizeof(t_symbol));
	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Sym		*symX;

		symX = sym;
		symbol.bind = ELF32_ST_BIND(symX->st_info);
		symbol.type = ELF32_ST_TYPE(symX->st_info);
		symbol.shndx = symX->st_shndx;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Sym		*symX;

		symX = sym;
		symbol.bind = ELF64_ST_BIND(symX->st_info);
		symbol.type = ELF64_ST_TYPE(symX->st_info);
		symbol.shndx = symX->st_shndx;
	}
	return (symbol);
}
