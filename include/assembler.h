#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <prstd.h>

#define MNEMONIC_BUF_SIZE 5

extern u16 outbuf_size;

typedef enum {
    AE_OK = 0,
    AE_UNEXPECTED_END_OF_FILE,
    AE_EXPECTED_MNEMONIC,
} assembly_err_t;

typedef assembly_err_t (*instr_handler_t)();
typedef struct {
    char mnemonic[MNEMONIC_BUF_SIZE];
    instr_handler_t handler;
} instr_info_t;

void assembler_init();

assembly_err_t assembly_text(u8 __far *_outbuf, char __far *_text, size_t _text_len);

assembly_err_t _ret_handler();

#endif