/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:06:54 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 14:27:20 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	local_symbol(t_context *ctx, void *sym);
static char	global_symbol(t_context *ctx, void *sym);
static char	weak_symbol(t_context *ctx, void *sym);

char	get_symbol_type(t_context *ctx, void *sym)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;
	char		type;

	type = '?';
	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		switch (ELF32_ST_BIND(sym32->st_info))
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
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		switch (ELF64_ST_BIND(sym64->st_info))
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
	}
	return (type);
}

static char	local_symbol(t_context *ctx, void *sym)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;
	char		type;

	type = '?';
	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		switch (ELF32_ST_TYPE(sym32->st_info))
		{

			default:
				break;
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		switch (ELF64_ST_TYPE(sym64->st_info))
		{
			case	STT_NOTYPE:
				
			default:
				break;
		}
	}
	return (type);
}

static char	global_symbol(t_context *ctx, void *sym)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;
	char		type;
}

static char	weak_symbol(t_context *ctx, void *sym)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;
	char		type;
}

