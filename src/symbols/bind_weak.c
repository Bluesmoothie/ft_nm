/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_weak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:44:53 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 15:21:47 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	weak_symbol(t_context *ctx, void *sym)
{
	const char	base_type = global_symbol(ctx, sym);

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
