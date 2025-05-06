/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:24:17 by ygille            #+#    #+#             */
/*   Updated: 2025/05/06 11:43:19 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_symbols(t_context *ctx)
{
	t_list		*lst = ctx->symbols;
	t_symbol	*sym;

	while (lst)
	{
		sym = lst->content;
		if (!(sym->id == ERR_SYM_ID || sym->id == 'n' || sym->id == 'N' || NULL_SYMBOL(sym)))
			printf("%s %c %s\n", sym->strvalue, sym->id, sym->name);
		lst = lst->next;
	}
}
