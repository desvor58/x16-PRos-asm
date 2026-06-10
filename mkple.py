from elftools.elf.elffile import ELFFile
import struct
import math

ple_version = 1

discardable_sections = [
    ".symtab",
    ".strtab",
    ".shstrtab"
]

elf_file = "bin/prasm.elf"
ple_file = "bin/prasm.ple"
description = "Simple assembler"
author = "Desvor"

def human_format(num):
    magnitude = 0
    while abs(num) >= 1024:
        magnitude += 1
        num //= 1024
    return f'{num}{['', 'K', 'M', 'G'][magnitude]}'

with open(elf_file, "rb") as f:
    elf = ELFFile(f)

    entry = elf.header["e_entry"]

    ple_sections: list[dict] = []
    current_file_offset = 0x1040
    common_size = 0
    for section in elf.iter_sections():
        if section.name != '' and not section.name in discardable_sections:
            ple_sections.append({
                "name": section.name,
                "size": section["sh_size"],
                "file_offset": current_file_offset + (0x10 - current_file_offset % 0x10)
            })
            common_size += section["sh_size"]
            current_file_offset += section["sh_size"]

    for sec in ple_sections:
        print(f"{sec["name"]}:\n    size:{hex(sec["size"])}\n    file_offset:{hex(sec["file_offset"])}")
    
    with open(ple_file, "wb") as ple:
        # ple header
        ple.write(struct.pack(
            "<4sHHHHHH32s16s",
            b"PLE\x00",
            ple_version,
            0,                       # entry rel-seg id
            entry & 0xFFFF,          # entry offset
            0,                       # stack rel-seg id
            0x1040,                  # stack sp
            1,                       # load-table entry count
            description.encode("ascii")[:32].ljust(32, b'\x00'),
            author.encode('ascii')[:16].ljust(16, b'\x00')
        ))
        ple.write(b"\0" * 0x1000)
        ple.write(struct.pack(
            "<HIH",
            0,
            0x1050,
            common_size
        ))
        ple.write(b"\0" * 0x8)
        for sec in ple_sections:
            ple.write(elf.get_section_by_name(sec["name"]).data())

        ple.seek(0, 2)
        print(f"PLE size: {human_format(ple.tell())} ({ple.tell()} bytes)")

        