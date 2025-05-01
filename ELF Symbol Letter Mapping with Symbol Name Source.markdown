| Bind (`ELF64_ST_BIND`) | Type (`ELF64_ST_TYPE`) | `st_shndx` Value | Letter | Description | Source of Symbol Name |
|------------------------|------------------------|------------------|--------|-------------|-----------------------|
| `STB_LOCAL` (0)        | `STT_NOTYPE` (0)       | `SHN_UNDEF` (0)  | `u`    | Local undefined symbol (rare, debugging) | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_NOTYPE`           | Section index (`.text`) | `t` | Local symbol in `.text` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_NOTYPE`           | Section index (`.data`) | `d` | Local symbol in `.data` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_NOTYPE`           | Section index (`.bss`) | `b` | Local symbol in `.bss` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_NOTYPE`           | Section index (other, e.g., `.rodata`) | `r` | Local symbol in read-only section | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_OBJECT` (1)       | Section index (`.data`) | `d` | Local data object in `.data` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_OBJECT`           | Section index (`.bss`) | `b` | Local data object in `.bss` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_OBJECT`           | Section index (other) | `r` | Local data object in other section | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_FUNC` (2)         | Section index (`.text`) | `t` | Local function in `.text` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_LOCAL`            | `STT_SECTION` (3)      | Section index    | `n`    | Section symbol | Section name from section header string table (`.shstrtab`), offset by `Elf64_Shdr.sh_name` for the section at `st_shndx` |
| `STB_LOCAL`            | `STT_FILE` (4)         | `SHN_ABS`        | `n`    | Source file name | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`), via `sh_link` |
| `STB_LOCAL`            | `STT_NOTYPE`/`STT_OBJECT` | `SHN_ABS`     | `a`    | Local absolute symbol | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL` (1)       | `STT_NOTYPE`           | `SHN_UNDEF`      | `U`    | Undefined global symbol | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_NOTYPE`           | `SHN_COMMON`     | `C`    | Common symbol (unallocated) | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_OBJECT`           | Section index (`.data`) | `D` | Global data object in `.data` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_OBJECT`           | Section index (`.bss`) | `B` | Global data object in `.bss` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_OBJECT`           | Section index (`.rodata`) | `R` | Global data in read-only section | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_FUNC`             | Section index (`.text`) | `T` | Global function in `.text` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_NOTYPE`           | Section index (`.text`) | `T` | Global symbol in `.text` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_NOTYPE`           | Section index (`.data`) | `D` | Global symbol in `.data` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_NOTYPE`           | Section index (`.bss`) | `B` | Global symbol in `.bss` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_NOTYPE`           | Section index (other, e.g., `.eh_frame_hdr`) | `R` | Global symbol in other section | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_GLOBAL`           | `STT_NOTYPE`/`STT_OBJECT` | `SHN_ABS`     | `A`    | Global absolute symbol | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_WEAK` (2)         | `STT_NOTYPE`/`STT_OBJECT` | `SHN_UNDEF` | `w`    | Weak undefined symbol | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_WEAK`             | `STT_OBJECT`           | Section index (`.data`) | `W` | Weak data object in `.data` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_WEAK`             | `STT_OBJECT`           | Section index (`.bss`) | `W` | Weak data object in `.bss` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_WEAK`             | `STT_FUNC`             | Section index (`.text`) | `W` | Weak function in `.text` | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_WEAK`             | `STT_NOTYPE`           | `SHN_COMMON`     | `C`    | Weak common symbol | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |
| `STB_WEAK`             | `STT_NOTYPE`/`STT_OBJECT` | `SHN_ABS`     | `W`    | Weak absolute symbol | `.strtab` section, offset by `Elf64_Sym.st_name` (for `SHT_SYMTAB`) or `.dynstr` (for `SHT_DYNSYM`), via `sh_link` |

### Notes
- **Symbol Name Retrieval**:
  - For `SHT_SYMTAB` (static symbol table):
    - The symbol table’s section header (`Elf64_Shdr`) has a `sh_link` field pointing to the index of the `.strtab` section.
    - Use `Elf64_Sym.st_name` as an offset into the `.strtab` section’s data (accessed via `shdr[sh_link].sh_offset` in the file).
    - Example: `char *name = file_data + shdr[sh_link].sh_offset + sym->st_name`.
  - For `SHT_DYNSYM` (dynamic symbol table):
    - The `sh_link` field points to the `.dynstr` section.
    - Use `Elf64_Sym.st_name` as an offset into `.dynstr`.
  - The resulting string is null-terminated.
- **Special Case for `STT_SECTION`**:
  - The name is the section name, retrieved from the section header string table (`.shstrtab`), using `Elf64_Shdr.sh_name` for the section at `st_shndx`.
  - Access `.shstrtab` via `ehdr->e_shstrndx` to get the section header string table’s index, then use `shdr[ehdr->e_shstrndx].sh_offset + shdr[sym->st_shndx].sh_name`.
- **Special Case for `STT_FILE`**:
  - The name is typically a source file name, stored in `.strtab` (for `SHT_SYMTAB`), accessed via `Elf64_Sym.st_name`.
- **Versioned Symbols**:
  - For symbols like `free@GLIBC_2.2.5`, the base name (e.g., `free`) is in `.strtab` or `.dynstr`. Version information comes from the `.gnu.version` section, indexed by the symbol’s position in the symbol table.
  - To include version info, check the `.gnu.version` section (type `SHT_GNU_verneed` or `SHT_GNU_versym`) and append the version string (e.g., `@GLIBC_2.2.5`).
- **Invalid Symbols**:
  - If `st_name == 0`, the symbol has no name (skip it to avoid empty entries like `U` in your output).
  - Ensure `st_shndx` is valid (e.g., not out-of-bounds) when accessing section names.
- **Section-Based Letters**:
  - Letters (`t`, `d`, `b`, `r`, etc.) depend on the section type, determined by mapping `st_shndx` to a section name via `shdr[st_shndx].sh_name` in `.shstrtab`.
  - Common sections: `.text` (`t`/`T`), `.data` (`d`/`D`), `.bss` (`b`/`B`), `.rodata` or `.eh_frame_hdr` (`r`/`R`).

