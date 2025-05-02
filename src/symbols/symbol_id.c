/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_id.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:43:59 by ygille            #+#    #+#             */
/*   Updated: 2025/05/02 18:46:17 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	_notype_(t_context *ctx,void *sym, t_symbol *symbol);
static char	_notype_default_(t_context *ctx,void *sym);
static char	weak_symbol(char base_id);
static char	symbol_id(t_context *ctx, void *sym, t_symbol *symbol);

/*
**	Determine the symbol char id from its parameters
*/
char	get_symbol_id(t_context *ctx, void *sym, t_symbol *symbol)
{
	switch (symbol->bind)
	{
		case	STB_LOCAL:
			return (symbol_id(ctx, sym, symbol));
			break;
		case	STB_GLOBAL:
			return (ft_toupper(symbol_id(ctx, sym, symbol)));
			break;
		case	STB_WEAK:
			return (weak_symbol(symbol_id(ctx, sym, symbol)));
			break;
		default:
			return (ERR_SYM_ID);
			break;
	}
}

static char	weak_symbol(char base_id)
{
	switch (base_id)
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

static char	symbol_id(t_context *ctx, void *sym, t_symbol *symbol)
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
	if (SECTION_T(section_name))
		return ('t');
	else if (SECTION_D(section_name))
		return ('d');
	else if (SECTION_B(section_name))
		return ('b');
	else if (SECTION_R(section_name))
		return ('r');
	return ('?');
}
