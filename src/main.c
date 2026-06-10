#include <prstd.h>
#include <assembler.h>

#define ARGS_BUF_SIZE     128
#define MAX_FILE_NAME     12
#define OUTBUF_SIZE       (16 * 1024U)
#define MAX_SYMBOL_SIZE   32
#define MAX_LABEL_NAME    24
#define MAX_OPERAND_SIZE  48
#define LABELS_BUF_SIZE   256
#define MAX_MNEMONIC_SIZE 8
#define MAX_STR_CONST_SIZE 128

// #pragma GCC section bss(".outbuf_section")
// u8 outbuf[OUTBUF_SIZE];
// #pragma GCC section bss("")

// char outfile_name[MAX_FILE_NAME + 1];
// char infile_name[MAX_FILE_NAME + 1];

// #pragma GCC section bss(".intext_section")
// char intext[(64 * 1024U)];
// #pragma GCC section bss("")

// int parse_args()
// {
//     char *arg = args;
    
//     while (*arg == ' ') arg++;
//     if (*arg < ' ') {
//         return -1;
//     }

//     int i = 0;
//     while ((u8)*arg > ' ') {
//         if (i >= MAX_FILE_NAME) return 1;
//         infile_name[i++] = *arg++;
//     }
//     infile_name[i] = 0;

//     while (*arg == ' ') arg++;
//     if (*arg < ' ') {
//         return -2;
//     }

//     i = 0;
//     while ((u8)*arg > ' ') {
//         if (i >= MAX_FILE_NAME) return 2;
//         outfile_name[i++] = *arg++;
//     }
//     outfile_name[i] = 0;
//     return 0;
// }

u8 outbuf[16*1024U];

void main()
{
    // args = "hello.asm hello.bin";


    // puts(args);
    // int parse_args_ok = parse_args();
    // switch (parse_args_ok) {
    //     case 1:
    //         puts("Error: input file name to big");
    //         return;
    //     case 2:
    //         puts("Error: output file name to big");
    //         return;
    //     case -1:
    //         puts("Error: input file name expected");
    //         return;
    //     case -2:
    //         puts("Error: output file name expected");
    //         return;
    //     default: break;
    // }
    // far_puts(outfile_name);

    // int infile_open_ok = load_huge_file(FP_SEG(intext), FP_OFF(intext), FP_OFF(infile_name));
    // if (!infile_open_ok) {
    //     puts("Error: input file not be opened");
    //     return;
    // }

    assembler_init();
    char *text = "ret\nret";
    assembly_err_t asm_err = assembly_text(outbuf, text, strlen(text));

    switch (asm_err) {
        case AE_EXPECTED_MNEMONIC:
            puts("Expected_mnemonic");
            break;

        default: break;
    }

    char buf[5];
    for (size_t i = 0; i < outbuf_size; i++) {
        u8to_far_s_hex(outbuf[i], buf);
        puts(buf);
    }
}
