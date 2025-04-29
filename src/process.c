/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:36 by ygille            #+#    #+#             */
/*   Updated: 2025/04/29 21:44:14 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	get_section_header(t_context *ctx);
static void	process_symbol_sections(t_context *ctx);
static void	list_symbols(t_context *ctx, size_t offset, size_t size);
static void	print_symbol(size_t value, unsigned char bind, unsigned char type);

void	process(t_context *ctx)
{
	get_section_header(ctx);
	process_symbol_sections(ctx);
}

static void	get_section_header(t_context *ctx)
{
	Elf32_Ehdr	*header32;
	Elf64_Ehdr	*header64;
	
	if (ctx->filetype == ELFCLASS32)
	{
		header32 = ctx->file;
		ctx->sh_offset = header32->e_shoff;
		ctx->sh_num = header32->e_shnum;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		header64 = ctx->file;
		ctx->sh_offset = header64->e_shoff;
		ctx->sh_num = header64->e_shnum;
	}
}

static void	process_symbol_sections(t_context *ctx)
{
	Elf32_Shdr	*section32;
	Elf64_Shdr	*section64;

	if (ctx->filetype == ELFCLASS32)
	{
		section32 = ctx->file + ctx->sh_offset;
		for (size_t i = 0;i < ctx->sh_num;i++)
		{
			if (section32->sh_type == SHT_SYMTAB || section32->sh_type == SHT_DYNSYM)
				list_symbols(ctx, section32->sh_offset, section32->sh_size);
			section32++;
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		section64 = ctx->file + ctx->sh_offset;
		for (size_t i = 0;i < ctx->sh_num;i++)
		{
			if (section64->sh_type == SHT_SYMTAB || section64->sh_type == SHT_DYNSYM)
				list_symbols(ctx, section64->sh_offset, section64->sh_size);
			section64++;
		}
	}
}

static void	list_symbols(t_context *ctx, size_t offset, size_t size)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;

	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = ctx->file + offset;
		while (size)
		{
			print_symbol(sym32->st_value, ELF32_ST_BIND(sym32->st_info), ELF32_ST_TYPE(sym32->st_info));
			sym32++;
			size -= sizeof(Elf32_Sym);
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = ctx->file + offset;
		while (size)
		{
			print_symbol(sym64->st_value, ELF64_ST_BIND(sym64->st_info), ELF64_ST_TYPE(sym64->st_info));
			sym64++;
			size -= sizeof(Elf64_Sym);
		}
	}
}

static void	print_symbol(size_t value, unsigned char bind, unsigned char type)
{
	char	id;

	switch (type)
	{
	case STT_OBJECT:
		id = 'r';
		break;
	case STT_FUNC:
		id = 't';
		break;
	default:
		id = type + 48;
		break;
	}
	if (bind == STB_GLOBAL)
		id = ft_toupper(id);
	if (!value)
		id = 'U';
	printf("%lx %c %d\n", value, id, bind);
}
