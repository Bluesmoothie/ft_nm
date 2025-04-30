/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:36 by ygille            #+#    #+#             */
/*   Updated: 2025/04/30 17:10:01 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	get_file_headers(t_context *ctx);
static void	process_symbol_sections(t_context *ctx);
static void	list_symbols(t_context *ctx, size_t index);
static void	print_symbol(t_context *ctx, size_t link, void *sym);
static char	get_symbol_type(t_context *ctx, void *sym);

void	process(t_context *ctx)
{
	get_file_headers(ctx);
	process_symbol_sections(ctx);
}

static void	get_file_headers(t_context *ctx)
{
	if (ctx->filetype == ELFCLASS32)
	{
		ctx->elf32.file_header = ctx->file;
		ctx->elf32.section_header = ctx->file + ctx->elf32.file_header->e_shoff;
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		ctx->elf64.file_header = ctx->file;
		ctx->elf64.section_header = ctx->file + ctx->elf64.file_header->e_shoff;
	}
}

static void	process_symbol_sections(t_context *ctx)
{
	if (ctx->filetype == ELFCLASS32)
	{
		for (size_t i = 0;i < ctx->elf32.file_header->e_shnum;i++)
			if (ctx->elf32.section_header[i].sh_type == SHT_SYMTAB || ctx->elf32.section_header[i].sh_type == SHT_DYNSYM)
				list_symbols(ctx, i);
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		for (size_t i = 0;i < ctx->elf64.file_header->e_shnum;i++)
			if (ctx->elf64.section_header[i].sh_type == SHT_SYMTAB || ctx->elf64.section_header[i].sh_type == SHT_DYNSYM)
				list_symbols(ctx, i);
	}
}

static void	list_symbols(t_context *ctx, size_t index)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;

	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = ctx->file + ctx->elf32.section_header[index].sh_offset;
		for (size_t i = 0;i < ctx->elf32.section_header[index].sh_size;sym32++)
		{
			print_symbol(ctx, ctx->elf32.section_header[index].sh_link, sym32);
			i += sizeof(Elf32_Sym);
		}
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = ctx->file + ctx->elf64.section_header[index].sh_offset;
		for (size_t i = 0;i < ctx->elf64.section_header[index].sh_size;sym64++)
		{
			print_symbol(ctx, ctx->elf64.section_header[index].sh_link, sym64);
			i += sizeof(Elf64_Sym);
		}
	}
}

static void	print_symbol(t_context *ctx, size_t link, void *sym)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;
	char		*strtab;
	const char	type = get_symbol_type(ctx, sym);

	if (type == 'E')
		return ;
	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		strtab = ctx->file + ctx->elf32.section_header[link].sh_offset;
		if (type == 'U' || type == 'w')
			ft_printf("                 ");
		else
			ft_printf("000000000000%x ", sym32->st_value);
		ft_printf("%c %s\n", type, &strtab[sym32->st_name]);
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		strtab = ctx->file + ctx->elf64.section_header[link].sh_offset;
		if (type == 'U' || type == 'w')
			ft_printf("                 ");
		else
			ft_printf("000000000000%x ", sym64->st_value);
		ft_printf("%c %s\n", type, &strtab[sym64->st_name]);
	}
}

static char	get_symbol_type(t_context *ctx, void *sym)
{
	Elf32_Sym	*sym32;
	Elf64_Sym	*sym64;
	char		type;

	type = 'E';
	if (ctx->filetype == ELFCLASS32)
	{
		sym32 = sym;
		if (ELF32_ST_BIND(sym32->st_info) == STB_WEAK)
			type = 'w';
		else if (sym32->st_shndx == SHN_UNDEF)
			type = 'U';
		else if (ELF32_ST_TYPE(sym32->st_info) == STT_FUNC)
			type = 't';
		else if (ELF32_ST_TYPE(sym32->st_info) == STT_OBJECT)
		{
			if (ctx->elf32.section_header[sym32->st_shndx].sh_type == SHT_NOBITS)
				type = 'b';
			else
				type = 'd';
		}
		if (ELF32_ST_BIND(sym32->st_info) == STB_GLOBAL)
			type = ft_toupper(type);
	}
	else if (ctx->filetype == ELFCLASS64)
	{
		sym64 = sym;
		if (ELF64_ST_BIND(sym64->st_info) == STB_WEAK)
			type = 'w';
		else if (sym64->st_shndx == SHN_UNDEF)
			type = 'U';
		else if (ELF64_ST_TYPE(sym64->st_info) == STT_FUNC)
			type = 't';
		else if (ELF64_ST_TYPE(sym64->st_info) == STT_OBJECT)
		{
			if (ctx->elf64.section_header[sym64->st_shndx].sh_type == SHT_NOBITS)
				type = 'b';
			else
				type = 'd';
		}
		if (ELF64_ST_BIND(sym64->st_info) == STB_GLOBAL)
			type = ft_toupper(type);
	}
	return (type);
}
