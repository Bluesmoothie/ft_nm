/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:43:29 by ygille            #+#    #+#             */
/*   Updated: 2025/05/01 14:43:43 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "libft.h"
#include "ft_printf.h"

#define PSTR	"ft_nm"

typedef struct s_elf32
{
	Elf32_Ehdr	*file_header;
	Elf32_Shdr	*section_header;
}	t_elf32;

typedef struct s_elf64
{
	Elf64_Ehdr	*file_header;
	Elf64_Shdr	*section_header;
}	t_elf64;

typedef struct s_context
{
	void	*file;
	off_t	filesize;
	char	filetype;
	t_elf32	elf32;
	t_elf64	elf64;
}	t_context;

typedef struct s_symbol
{
	size_t	value;
	char	type;
	char	*name;
}	t_symbol;

//	main.c
int		pexit(char *msg);

//	ft_nm.c
void	ft_nm(char *file);

//	utils.c
int		open_helper(char *file);
void	*mmap_helper(size_t len, int fd);
void	munmap_helper(void *addr, size_t len);

//	->symbols

//	bind_global.c
char	global_symbol(t_context *ctx, void *sym);

//	bind_local.c
char	local_symbol(t_context *ctx, void *sym);

//	bind_weak.c
char	weak_symbol(t_context *ctx, void *sym);

//	symbol_name.c
char	*get_symbol_name(t_context *ctx, void *sym, t_symbol *symbol);

//	symbol_type.c
char	get_symbol_type(t_context *ctx, void *sym);

//	symbol_value.c
size_t	get_symbol_value(t_context *ctx, void *sym, t_symbol *symbol);

//	symbol.c
void	process_symbol_sections(t_context *ctx);