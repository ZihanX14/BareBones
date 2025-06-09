/*shell.c*/
#include <xos.h>

// const struct cmdtlb cmd[] = {
//     {"help", sh_help}
// };

process shell_init(void) {
    char line[SHELL_LEN];

    terminal_writestring(SHELL_STRTMESG);
    terminal_putchar('\n');


    while (TRUE) {
        terminal_writestring(SHELL_PROMPT); // Show prompt

        read_line(line, SHELL_LEN);         // Wait for input

        if (strcmp(line, "1") == 0) {
            terminal_writestring(SHELL_FIRSTMESG);
            terminal_putchar('\n');
        } else {
            terminal_writestring("Unknown command: ");
            terminal_writestring(line);
            terminal_putchar('\n');
        }
    }

    return OK;
}
