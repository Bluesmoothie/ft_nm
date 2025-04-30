| Bind (`ELF64_ST_BIND`) | Type (`ELF64_ST_TYPE`) | `st_shndx` Value | Letter | Description |
|------------------------|------------------------|------------------|--------|-------------|
| `STB_LOCAL` (0)        | `STT_NOTYPE` (0)       | `SHN_UNDEF` (0)  | `u`    | Local undefined symbol (rare, often debugging). |
| `STB_LOCAL`            | `STT_NOTYPE`           | Section index    | `t` (`.text`), `d` (`.data`), `b` (`.bss`), `r` (others) | Local symbol in a section (type based on section). |
| `STB_LOCAL`            | `STT_OBJECT` (1)       | Section index    | `d` (`.data`), `b` (`.bss`), `r` (others) | Local data object (e.g., variable). |
| `STB_LOCAL`            | `STT_FUNC` (2)         | Section index    | `t`    | Local function (usually in `.text`). |
| `STB_LOCAL`            | `STT_SECTION` (3)      | Section index    | `n`    | Section symbol (e.g., `.text`, `.data`). |
| `STB_LOCAL`            | `STT_FILE` (4)         | `SHN_ABS`        | `n`    | Source file name (not typically printed). |
| `STB_LOCAL`            | `STT_NOTYPE`/`STT_OBJECT` | `SHN_ABS`     | `a`    | Local absolute symbol (e.g., constants). |
| `STB_GLOBAL` (1)       | `STT_NOTYPE`           | `SHN_UNDEF`      | `U`    | Undefined global symbol (external reference). |
| `STB_GLOBAL`           | `STT_NOTYPE`           | `SHN_COMMON`     | `C`    | Common symbol (unallocated data). |
| `STB_GLOBAL`           | `STT_OBJECT`           | Section index    | `D` (`.data`), `B` (`.bss`), `R` (`.rodata`) | Global data object. |
| `STB_GLOBAL`           | `STT_FUNC`             | Section index    | `T`    | Global function (usually in `.text`). |
| `STB_GLOBAL`           | `STT_NOTYPE`           | Section index    | `T` (`.text`), `D` (`.data`), `B` (`.bss`), `R` (others) | Global symbol, type inferred from section. |
| `STB_GLOBAL`           | `STT_NOTYPE`/`STT_OBJECT` | `SHN_ABS`     | `A`    | Global absolute symbol. |
| `STB_WEAK` (2)         | `STT_NOTYPE`/`STT_OBJECT` | `SHN_UNDEF` | `w`    | Weak undefined symbol. |
| `STB_WEAK`             | `STT_OBJECT`           | Section index    | `W`    | Weak data object (e.g., variable). |
| `STB_WEAK`             | `STT_FUNC`             | Section index    | `W`    | Weak function. |
| `STB_WEAK`             | `STT_NOTYPE`           | `SHN_COMMON`     | `C`    | Weak common symbol. |
| `STB_WEAK`             | `STT_NOTYPE`/`STT_OBJECT` | `SHN_ABS`     | `W`    | Weak absolute symbol. |

### Notes
- **Section-Based Letters**: The letter depends on the section type (e.g., `.text` → `t`/`T`, `.data` → `d`/`D`, `.bss` → `b`/`B`, `.rodata` → `r`/`R`). Use the section header table (`Elf64_Shdr`) to map `st_shndx` to a section name (`sh_name`) and determine the section type.
- **Case Sensitivity**: Uppercase letters (e.g., `T`, `D`) are used for global or weak symbols, while lowercase (e.g., `t`, `d`) are used for local symbols.
- **Special Cases**:
  - `SHN_UNDEF` symbols are typically `U` (global) or `u` (local, rare).
  - `SHN_COMMON` symbols (unallocated data) are marked as `C`.
  - `SHN_ABS` symbols (e.g., constants) use `A` (global) or `a` (local).
- **Default for Other Sections**: For sections not explicitly listed (e.g., `.eh_frame_hdr`), use `r` (local) or `R` (global) for read-only data or other custom sections.
- **Empty or Invalid Symbols**: Skip symbols with `st_name == 0` or invalid `st_shndx` to avoid empty `U` entries.
