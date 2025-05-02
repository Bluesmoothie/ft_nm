/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:06:54 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 16:26:24 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_symbol	get_symbol_base_infos(t_context *ctx, void *sym);
static char		*get_symbol_name(t_context *ctx, void *sym, size_t link);

t_symbol	get_symbol_infos(t_context *ctx, void *sym, size_t link)
{
	t_symbol	symbol;

	symbol = get_symbol_base_infos(ctx, sym);
	symbol.id = get_symbol_id(ctx, sym, &symbol);
	symbol.name = get_symbol_name(ctx, sym, link);
	get_str_value(&symbol);
	return (symbol);
}

static t_symbol	get_symbol_base_infos(t_context *ctx, void *sym)
{
	t_symbol	symbol;

	ft_bzero(&symbol, sizeof(t_symbol));
	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Sym		*symX = sym;

		symbol.bind = ELF32_ST_BIND(symX->st_info);
		symbol.type = ELF32_ST_TYPE(symX->st_info);
		symbol.value = symX->st_value;
		symbol.shndx = symX->st_shndx;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Sym		*symX = sym;

		symbol.bind = ELF64_ST_BIND(symX->st_info);
		symbol.type = ELF64_ST_TYPE(symX->st_info);
		symbol.value = symX->st_value;
		symbol.shndx = symX->st_shndx;
	}
	return (symbol);
}

static char	*get_symbol_name(t_context *ctx, void *sym, size_t link)
{
	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Sym	*symX = sym;
		Elf32_Shdr	*section_strtab = ctx->elfX.elf32.section_header + link;

		char		*strtab = ctx->file + section_strtab->sh_offset;
		return (&strtab[symX->st_name]);
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Sym	*symX = sym;
		Elf64_Shdr	*section_strtab = ctx->elfX.elf64.section_header + link;

		char		*strtab = ctx->file + section_strtab->sh_offset;
		return (&strtab[symX->st_name]);
	}
	return (NULL);
}
