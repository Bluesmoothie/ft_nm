/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:43:29 by ygille            #+#    #+#             */
/*   Updated: 2025/04/30 15:58:11 by ygille           ###   ########.fr       */
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

//	main.c
int		pexit(char *msg);

//	ft_nm.c
void	ft_nm(char *file);

//	process.c
void	process(t_context *ctx);

//	utils.c
int		open_helper(char *file);
void	*mmap_helper(size_t len, int fd);
void	munmap_helper(void *addr, size_t len);