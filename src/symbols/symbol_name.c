/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:16:12 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 15:04:56 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	*get_symbol_name(t_context *ctx, void *sym, t_symbol *symbol, size_t link)
{
	char		*symbol_name;

	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Sym	*sym32;

		sym32 = sym;
		Elf32_Shdr	*section_strtab = ctx->elfX.elf32.section_header + link;
		char		*strtab = ctx->file + section_strtab->sh_offset;
		symbol_name = &strtab[sym32->st_name];
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Sym	*sym64;
		
		sym64 = sym;
		Elf64_Shdr	*section_strtab = ctx->elfX.elf64.section_header + link;
		char		*strtab = ctx->file + section_strtab->sh_offset;
		symbol_name = &strtab[sym64->st_name];
	}
	else
		symbol_name = NULL;
	switch(symbol->type)
	{
		default:
			return (symbol_name);
			break;
	}
	return ("");
}
