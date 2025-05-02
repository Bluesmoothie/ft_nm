/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:06:54 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 15:31:49 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_symbol_type(t_context *ctx, void *sym, t_symbol *symbol)
{
	switch (symbol->bind)
	{
		case	STB_LOCAL:
			return (local_symbol(ctx, sym, symbol));
			break;
		case	STB_GLOBAL:
			return (global_symbol(ctx, sym, symbol));
			break;
		case	STB_WEAK:
			return (weak_symbol(ctx, sym, symbol));
			break;
		default:
			return (ERR_SYM_ID);
			break;
	}
}
