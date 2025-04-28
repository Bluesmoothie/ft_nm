/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:43:29 by ygille            #+#    #+#             */
/*   Updated: 2025/04/28 19:54:15 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>

#include "libft.h"
#include "ft_printf.h"

typedef struct s_context
{
	char	filetype;
	size_t	sh_offset;
	size_t	sh_num;
}	t_context;

//	ft_nm.c
void	ft_nm(char *file);

//	process.c
void	process(t_context *ctx, char *file);

//	utils.c
int	open_helper(char *file);