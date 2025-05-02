/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:36 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 18:40:17 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		list_symbols(t_context *ctx, size_t index);
static void		print_symbol(t_context *ctx, void *sym, size_t link);

/*
**	Search for symbols sections in all sections
*/
void	process_symbol_sections(t_context *ctx)
{
	if (ctx->filetype == ELFCLASS32)
	{
		for (size_t i = 0;i < ctx->elfX.elf32.file_header->e_shnum;i++)
			if (ctx->elfX.elf32.section_header[i].sh_type == SHT_SYMTAB)
				return (list_symbols(ctx, i));
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		for (size_t i = 0;i < ctx->elfX.elf64.file_header->e_shnum;i++)
			if (ctx->elfX.elf64.section_header[i].sh_type == SHT_SYMTAB)
				return (list_symbols(ctx, i));
	}
}

/*
**	List all symbols from a symbol section
*/
static void	list_symbols(t_context *ctx, size_t index)
{
	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Sym	*symX = ctx->file + ctx->elfX.elf32.section_header[index].sh_offset;

		for (size_t i = 0;i < ctx->elfX.elf32.section_header[index].sh_size;symX++)
		{
			print_symbol(ctx, symX, ctx->elfX.elf32.section_header[index].sh_link);
			i += sizeof(Elf32_Sym);
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Sym	*symX = ctx->file + ctx->elfX.elf64.section_header[index].sh_offset;

		for (size_t i = 0;i < ctx->elfX.elf64.section_header[index].sh_size;symX++)
		{
			print_symbol(ctx, symX, ctx->elfX.elf64.section_header[index].sh_link);
			i += sizeof(Elf64_Sym);
		}
	}
}

/*
**	Print symbol infos
*/
static void	print_symbol(t_context *ctx, void *sym, size_t link)
{
	const t_symbol	symbol = get_symbol_infos(ctx, sym, link);

	if (symbol.id == ERR_SYM_ID || symbol.id == 'n' || symbol.id == 'N' || NULL_SYMBOL(symbol))
		return ;
	printf("%s %c %s\n", symbol.strvalue, symbol.id, symbol.name);
}
