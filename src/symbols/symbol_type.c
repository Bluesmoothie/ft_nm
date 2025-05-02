/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:06:54 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 14:52:42 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_symbol_type(t_context *ctx, void *sym)
{
	unsigned char	bind;
	char			type;

	type = '?';
	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Sym		*sym32;

		sym32 = sym;
		bind = ELF32_ST_BIND(sym32->st_info);
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Sym		*sym64;
		
		sym64 = sym;
		bind = ELF64_ST_BIND(sym64->st_info);
	}
	else
		return (type);
	switch (bind)
	{
		case	STB_LOCAL:
			type = local_symbol(ctx, sym);
			break;
		case	STB_GLOBAL:
			type = global_symbol(ctx, sym);
			break;
		case	STB_WEAK:
			type = weak_symbol(ctx, sym);
			break;
		default:
			break;
	}
	return (type);
}
