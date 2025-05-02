/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_weak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:44:53 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 15:31:28 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	weak_symbol(t_context *ctx, void *sym, t_symbol *symbol)
{
	const char	base_type = global_symbol(ctx, sym, symbol);

	switch (base_type)
	{
	case	'C':
		return ('C');
		break;
	case	'U':
		return ('w');
		break;
	default:
		return ('W');
		break;
	}
}
