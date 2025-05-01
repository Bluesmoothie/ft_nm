/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:22:53 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 16:12:15 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

size_t	get_symbol_value(t_context *ctx, void *sym, t_symbol *symbol)
{
	Elf32_Sym		*sym32;
	Elf64_Sym		*sym64;

	if (symbol->type == 'w' || symbol->type == 'W' || symbol->type == 'u' || symbol->type == 'U')
		return (0);
	else if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		return (sym32->st_value);
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		return (sym64->st_value);
	}
	return (0);
}
