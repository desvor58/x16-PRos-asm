#include <assembler.h>

u8   __far *outbuf;
u16         outbuf_size;
char __far *text;
size_t      text_len;
size_t      pos;

instr_info_t __far *instr_infos;

void assembler_init()
{
    instr_infos = alloc(2 * sizeof(instr_info_t));
    instr_infos[0] = (instr_info_t){ .mnemonic = "ret", .handler = _ret_handler };
    instr_infos[1] = (instr_info_t){ 0 };
}

static inline void __attribute__((always_inline)) skip_spaces()
{
    while (pos < text_len && text[pos] == ' ') {
        pos++;
    }
}

#define check_non_end()  \
    if (pos >= text_len) return AE_UNEXPECTED_END_OF_FILE;

assembly_err_t assembly_text(u8 __far *_outbuf, char __far *_text, size_t _text_len)
{
    outbuf   = _outbuf;
    text     = _text;
    text_len = _text_len;
    pos      = 0;

    char mnemonic[MNEMONIC_BUF_SIZE] = {0};
    while (pos < text_len) {
        skip_spaces();
        if (pos >= text_len) return AE_EXPECTED_MNEMONIC;
        u8 i = 0;
        while (pos < text_len && is_alpha(text[pos]) && i < MNEMONIC_BUF_SIZE - 1) {
            mnemonic[i] = text[pos];
            pos++;
            i++;
        }
        mnemonic[i] = 0;
        skip_spaces();

        instr_info_t __far *instr_info = instr_infos;
        while (instr_info->mnemonic) {
            if (far_strcmp(instr_info->mnemonic, mnemonic)) {
                assembly_err_t err = instr_info->handler();
                if (err) return err;
            }
        }
    }
    
    return AE_OK;
}

assembly_err_t _ret_handler()
{
    outbuf[outbuf_size++] = 0xC3;
    while (pos < text_len && text[pos] != '\n') pos++;
    pos++;
    return AE_OK;
}
