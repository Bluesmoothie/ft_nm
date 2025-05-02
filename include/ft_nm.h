/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:43:29 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 18:46:58 by ygille           ###   ########.fr       */
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

#define LOW_BASE_HEX			"0123456789abcdef"
#define PSTR					"ft_nm"
#define	ERR_SYM_ID				'?'

#define NULL_SYMBOL(symbol)		(!symbol.bind && !symbol.type && !symbol.shndx)

#define SECTION_T(name)			(!ft_strcmp(name, ".text") || !ft_strcmp(name, ".plt"))
#define SECTION_D(name)			(!ft_strcmp(name, ".data") || !ft_strcmp(name, ".init_array") || !ft_strcmp(name, ".fini_array")\
								|| !ft_strcmp(name, ".data.rel.ro") || !ft_strcmp(name, ".got") || !ft_strcmp(name, ".got.plt")\
								|| !ft_strcmp(name, ".dynamic") || !ft_strcmp(name, ".ctors") || !ft_strcmp(name, ".dtors")\
								|| !ft_strcmp(name, ".jcr"))
#define SECTION_B(name)			(!ft_strcmp(name, ".bss"))
#define	SECTION_R(name)			(!ft_strcmp(name, ".rodata") || !ft_strcmp(name, ".rodata1") || !ft_strcmp(name, ".eh_frame")\
								|| !ft_strcmp(name, ".eh_frame_hdr") || !ft_strcmp(name, ".note.ABI-tag"))

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

typedef union u_elfX
{
	t_elf32	elf32;
	t_elf64	elf64;
}	t_elfX;

typedef struct s_context
{
	void	*file;
	off_t	filesize;
	char	filetype;
	char	*strtab;
	t_elfX	elfX;
}	t_context;

typedef struct s_symbol
{
	unsigned char	bind;
	unsigned char	type;
	size_t			shndx;
	char			*section_name;
	size_t			value;
	char			id;
	char			*name;
	char			strvalue[17];
}	t_symbol;

//	main.c
int		pexit(char *msg);

//	ft_nm.c
void	ft_nm(char *file);

//	utils.c
int		open_helper(char *file);
void	*mmap_helper(size_t len, int fd);
void	munmap_helper(void *addr, size_t len);
void	get_str_value(t_symbol *symbol);

//	->symbols

//	symbol_id.c
char		get_symbol_id(t_context *ctx, void *sym, t_symbol *symbol);;

//	symbol_infos.c
t_symbol	get_symbol_infos(t_context *ctx, void *sym, size_t link);

//	symbol.c
void		process_symbol_sections(t_context *ctx);