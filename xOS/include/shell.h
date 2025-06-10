/* shell.h */

#define SHELL_PROMPT    "xsh:$"
#define SHELL_STRTMESG  "Hi this is my shell"
#define SHELL_FIRSTMESG "Press 1 for Hello Shell"

#define SHELL_LEN       129

#define MAX_HISTORY 16
#define SHELL_LEN 128

extern char command_history[MAX_HISTORY][SHELL_LEN];
extern int history_size;       // number of stored commands
extern int history_index;      // index to navigate history (set when Up is pressed)
