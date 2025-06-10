/*shell.c*/
#include <xos.h>

// const struct cmdtlb cmd[] = {
//     {"help", sh_help}
// };

char command_history[MAX_HISTORY][SHELL_LEN];
int history_size = 0;       // number of stored commands
int history_index = 0;      // index to navigate history (set when Up is pressed)


process shell_init(void) {
    char line[SHELL_LEN];

    terminal_writestring(SHELL_STRTMESG);
    terminal_putchar('\n');


    while (TRUE) {
        terminal_writestring(SHELL_PROMPT); // Show prompt

        read_line(line, SHELL_LEN);         // Wait for input

        if (strlen(line) > 0 && (history_size == 0 || strcmp(line, command_history[history_size - 1]) != 0)) {
            if (history_size < MAX_HISTORY) {
                strcpy(command_history[history_size++], line);
            } else {
                // Optional: shift up if buffer full
                for (int i = 1; i < MAX_HISTORY; i++) {
                    strcpy(command_history[i - 1], command_history[i]);
                }
                strcpy(command_history[MAX_HISTORY - 1], line);
            }
        }
        history_index = history_size;
        
        // debug
        // char buf[16];
        // itoa(history_index, buf);
        // terminal_writestring(" [HistoryIndex: ");
        // terminal_writestring(buf);
        // terminal_writestring("]\n");


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
