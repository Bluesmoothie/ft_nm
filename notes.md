## Elf32_Ehdr // Elf64_Ehdr
>Elf file header
>At the very beginning of the file

### .e_ident	
>strcmp(.e_ident, "\177ELF":ELFMAG, 4:SELFMAG) to verif if it's a valid ELF file

.e_ident[EI_CLASS]
>1:ELFCLASS32: 32bit
>2:ELFCLASS64: 64bit

.e_ident[EI_DATA]
>1:ELFDATA2LSB: little endian
>2:ELFDATA2MSB: big endian

.e_ident[EI_VERSION]
OS ABI ID

.e_ident[EI_ABIVERSION]
ABI Version

.e_type
>1:ET_REL: .o
>2:ET_EXEC: Executable
>3:ET_DYN: .so
>4:ET_CORE: core file

.e_machine
Architecture

.e_version
Normally 1:EV_CURRENT

.e_shoff
section header offset

.e_shentsize
section header table size

.e_shnum
number of entry in section header table

.e_shstrndx
section header string table index

## Elf32_Shdr // Elf64_Shdr
>Section Header

.sh_type
>SHT_SYMTAB:2: Symbol table
>SHT_DYNSYM:11: Dynamic symbol table

### Progs headers

.e_phoff
prog header offset

.e_phentsize
prog header table size

.e_phnum
number of entry in prog header table

## Elf32_Sym // Elf64_Sym
>Symbol table entry

.st_name	name
.st_value	value
.st_size	size
.st_info	type & binding
.st_other	visibility
.st_shndx	index



Lire le header -> verifier le type -> lire les sections a partir de .e_shoff (nombre de section dans .e_shnum) si .sh_type 2 ou 11 -> parcourir pour obtenir les symboles