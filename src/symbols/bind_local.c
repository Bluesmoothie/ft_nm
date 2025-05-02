/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_local.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:43:59 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 15:30:32 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	_notype_(t_context *ctx,void *sym);
static char	_notype_default_(t_context *ctx,void *sym);
static char	_object_(t_context *ctx,void *sym);
static char	_func_(t_context *ctx,void *sym);

char	local_symbol(t_context *ctx, void *sym, t_symbol *symbol)
{
	switch (symbol->type)
	{
		case	STT_NOTYPE:	
			return (_notype_(ctx, sym));
			break;
		case	STT_OBJECT:
			return (_object_(ctx, sym));
			break;
		case	STT_FUNC:
			return (_func_(ctx, sym));
			break;
		case	STT_SECTION:
			return ('n');
			break;
		case	STT_FILE:
			return ('n');
			break;
		default:
			return (ERR_SYM_ID);
			break;
	}
}

static char	_notype_(t_context *ctx,void *sym)
{
	Elf32_Sym		*sym32;
	Elf64_Sym		*sym64;
	size_t			st_shndx;
	char			type;

	type = '?';
	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		st_shndx = sym32->st_shndx;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		st_shndx = sym64->st_shndx;
	}
	else
		return (type);
	switch (st_shndx)
	{
		case	SHN_UNDEF:
			type = 'u';
			break;
		case	SHN_ABS:
			type = 'a';
			break;
		case	SHN_COMMON:
			type = 'c';
			break;
		default:
			type = _notype_default_(ctx, sym);
			break;
	}
	return (type);
}

static char	_notype_default_(t_context *ctx,void *sym)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;
	char		*section_name;

	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		Elf32_Shdr	*section = ctx->elfX.elf32.section_header + sym32->st_shndx;

		section_name = &ctx->strtab[section->sh_name];
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		Elf64_Shdr	*section = ctx->elfX.elf64.section_header + sym64->st_shndx;

		section_name = &ctx->strtab[section->sh_name];
	}
	if (!ft_strcmp(section_name, ".text") || !ft_strcmp(section_name, ".plt"))
		return ('t');
	else if (!ft_strcmp(section_name, ".data") || !ft_strcmp(section_name, ".init_array") || !ft_strcmp(section_name, ".fini_array")
			|| !ft_strcmp(section_name, ".data.rel.ro") || !ft_strcmp(section_name, ".got") || !ft_strcmp(section_name, ".got.plt")
			|| !ft_strcmp(section_name, ".dynamic") || !ft_strcmp(section_name, ".ctors") || !ft_strcmp(section_name, ".dtors")
			|| !ft_strcmp(section_name, ".jcr"))
		return ('d');
	else if (!ft_strcmp(section_name, ".bss"))
		return ('b');
	else if (!ft_strcmp(section_name, ".rodata") || !ft_strcmp(section_name, ".rodata1") || !ft_strcmp(section_name, ".eh_frame")
		|| !ft_strcmp(section_name, ".eh_frame_hdr") || !ft_strcmp(section_name, ".note.ABI-tag"))
		return ('r');
	return ('?');
}

static char	_object_(t_context *ctx,void *sym)
{
	Elf32_Sym		*sym32;
	Elf64_Sym		*sym64;
	size_t			st_shndx;
	char			type;

	type = '?';
	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		st_shndx = sym32->st_shndx;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		st_shndx = sym64->st_shndx;
	}
	else
		return (type);
	switch (st_shndx)
	{
		case	SHN_ABS:
			type = 'a';
			break;
		default:
			type = _notype_default_(ctx, sym);
			break;
	}
	return (type);
}

static char	_func_(t_context *ctx,void *sym)
{
	Elf32_Sym		*sym32;
	Elf64_Sym		*sym64;
	size_t			st_shndx;
	char			type;

	type = '?';
	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		st_shndx = sym32->st_shndx;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		st_shndx = sym64->st_shndx;
	}
	else
		return (type);
	switch (st_shndx)
	{
		case	SHN_UNDEF:
			type = 'u';
			break;
		default:
			type = 't';
			break;
	}
	return (type);
}
