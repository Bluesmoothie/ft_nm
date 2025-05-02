/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_id.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:43:59 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 16:32:52 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	_notype_(t_context *ctx,void *sym, t_symbol *symbol);
static char	_notype_default_(t_context *ctx,void *sym);
static char	global_symbol(t_context *ctx, void *sym, t_symbol *symbol);
static char	weak_symbol(t_context *ctx, void *sym, t_symbol *symbol);
static char	local_symbol(t_context *ctx, void *sym, t_symbol *symbol);

/*
**	Determine the symbol char id from its parameters
*/
char	get_symbol_id(t_context *ctx, void *sym, t_symbol *symbol)
{
	switch (symbol->bind)
	{
		case	STB_LOCAL:
			return (local_symbol(ctx, sym, symbol));
			break;
		case	STB_GLOBAL:
			return (global_symbol(ctx, sym, symbol));
			break;
		case	STB_WEAK:
			return (weak_symbol(ctx, sym, symbol));
			break;
		default:
			return (ERR_SYM_ID);
			break;
	}
}

char	global_symbol(t_context *ctx, void *sym, t_symbol *symbol)
{
	return (ft_toupper(local_symbol(ctx, sym, symbol)));
}

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

char	local_symbol(t_context *ctx, void *sym, t_symbol *symbol)
{
	switch (symbol->type)
	{
		case	STT_NOTYPE:	
			return (_notype_(ctx, sym, symbol));
			break;
		case	STT_OBJECT:
			if (symbol->shndx == SHN_ABS)
				return ('a');
			else
				return (_notype_default_(ctx, sym));
			break;
		case	STT_FUNC:
			if (symbol->shndx == SHN_UNDEF)
				return ('u');
			else
				return ('t');
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

static char	_notype_(t_context *ctx,void *sym, t_symbol *symbol)
{
	switch (symbol->shndx)
	{
		case	SHN_UNDEF:
			return ('u');
			break;
		case	SHN_ABS:
			return ('a');
			break;
		case	SHN_COMMON:
			return ('c');
			break;
		default:
			return (_notype_default_(ctx, sym));
			break;
	}
}

static char	_notype_default_(t_context *ctx,void *sym)
{
	char		*section_name;

	if (ctx->filetype == ELFCLASS32)
	{
		Elf32_Sym	*symX = sym;
		Elf32_Shdr	*section = ctx->elfX.elf32.section_header + symX->st_shndx;

		section_name = &ctx->strtab[section->sh_name];
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		Elf64_Sym	*symX = sym;
		Elf64_Shdr	*section = ctx->elfX.elf64.section_header + symX->st_shndx;

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
