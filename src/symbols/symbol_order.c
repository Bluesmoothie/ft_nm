/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:09:01 by ygille            #+#    #+#             */
/*   Updated: 2025/05/06 12:44:54 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static bool	order_check(t_symbol *sym1, t_symbol *sym2);

void	order_symbols(t_context *ctx)
{
	t_list	*l1 = NULL;
	t_list	*l2 = ctx->symbols;
	t_list	*l3 = ctx->symbols->next;

	while (l3)
	{
		if (!order_check(l2->content, l3->content))
		{
			if (l1)
				l1->next = l3;
			else
				ctx->symbols = l3;
			l2->next = l3->next;
			l3->next = l2;
			l1 = NULL;
			l2 = ctx->symbols;
			l3 = ctx->symbols->next;
		}
		else
		{
			l1 = l2;
			l2 = l3;
			l3 = l3->next;
		}
	}
}

static bool	order_check(t_symbol *sym1, t_symbol *sym2)
{
	const char		*s1 = sym1->name;
	const char		*s2 = sym2->name;
	size_t			i = 0;
	size_t			j = 0;

	if (!s1 || !s2)
		return (true);
	while (s1[i] && s2[j])
	{
		while (s1[i] && ft_isalnum(s1[i]))
			i++;
		while (s2[i] && ft_isalnum(s2[i]))
			i++;
		if (ft_tolower(s1[i]) <= ft_tolower(s2[j]))
			return (false);
		if (!(s1[i] || s2[j]))
			break ;
		i++;
		j++;
	}
	return (true);
}
