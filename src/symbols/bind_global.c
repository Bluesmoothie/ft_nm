/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:44:20 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 16:01:07 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	global_symbol(t_context *ctx, void *sym)
{
	return (ft_toupper(local_symbol(ctx, sym)));
}
