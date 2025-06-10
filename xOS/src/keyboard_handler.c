/* keyboard_handler.c - handle keyboard commands PS/2 Keyboard: https://wiki.osdev.org/PS/2_Keyboard*/

/*TODO: Command Queue, state machine, IRQ(interrupt request) handler*/

/** Command Queue:
 * add command to queue, 
 * if queue empty -> send command
 * else -> append command to queue
 * 
 * if receive ACK(0xFA) from keyboard, discard command at the head and send next command
 * if receive Resend(0xFE), resend command at the head of queue
 * 
 *  Make space for the interrupt descriptor table
    Tell the CPU where that space is (see GDT Tutorial: lidt works the very same way as lgdt)
    Tell the PIC that you no longer Qwant to use the BIOS defaults (see Programming the PIC chips)
    Write a couple of ISR handlers (see Interrupt Service Routines) for both IRQs and exceptions
    Put the addresses of the ISR handlers in the appropriate descriptors (in Interrupt Descriptor Table)
    Enable all supported interrupts in the IRQ mask (of the PIC)
 * 
*/

#include <xos.h>


/* TODO: create a buffer to store the input from keyboard till the user press Enter */
// void keyboard_handler() {
//    uint8 scancode = inb(0x60);
//    char ch = keyboard_to_ascii(scancode);
//    if (ch) {
//       terminal_writestring("Keyboard triggered: ");
//       terminal_putchar(ch);
//       terminal_putchar('\n');
//       if (ch == '1'){
//          terminal_writestring("Hello World\n");
//       }
//       toggle_output(); // disable timer display
//    }
//    outb(0x20, 0x20); // EOI
// }

#define ENTER_KEY '\n'
volatile char input_buf[INPUT_BUF_LEN];
volatile int input_len = 0;
volatile int input_ready = 0;
static int extended = 0;

// void keyboard_handler() {
//     terminal_writestring("Keyboard interrupt triggered\n");
//     uint8 scancode = inb(0x60);
//     char ch = keyboard_to_ascii(scancode);

//     if (ch) {
//         // Echo to screen
//         terminal_putchar(ch);

//         // Handle Enter (end of input)
//         if (ch == ENTER_KEY || ch == '\r') {
//             input_buf[input_len] = '\0';  // null terminate
//             input_ready = 1;
//             terminal_putchar('\n');
//         }
//         // Store normal characters
//         else if (input_len < INPUT_BUF_LEN - 1) {
//             input_buf[input_len++] = ch;
//         }
//     }

//     // Send End of Interrupt (EOI) to PIC
//     outb(0x20, 0x20);
// }
__attribute__((section(".text.keyboard_handler")))
__attribute__((used))
void keyboard_handler() {
    uint8 scancode = inb(0x60);
    //terminal_writestring("key");
    // raw debug
    // terminal_writestring("Scancode: 0x");
    // char buf[4];
    // itoa(scancode, buf);
    // terminal_writestring(buf);
    // terminal_putchar('\n');
    if (scancode == 0xE0) {
        extended = 1;
        outb(0x20, 0x20);
        return;
    }

    if (extended){
        if (scancode == 0x48){ /*cursor up in shell gets the last command*/
            //terminal_writestring("up");
            if (history_index > 0) {
                //terminal_writestring("up");
                history_index--;
                const char* prev = command_history[history_index];
                
                /* clear current line*/
                while (input_len > 0) {
                    terminal_backspace();
                    input_len--;
                }

                /* copy and print old command*/
                strcpy((char*)input_buf, prev);
                input_len = strlen(input_buf);
                terminal_writestring(input_buf);
            }
        }
        else if (scancode == 0x50){ /*cursor down in shell gets the newer command*/
            if (history_index < history_size - 1){
                history_index++;
                const char* next = command_history[history_index];

                /* clear current line*/
                while (input_len > 0) {
                    terminal_backspace();
                    input_len--;
                }

                /* copy and print next command*/
                strcpy((char*)input_buf, next);
                input_len = strlen(input_buf);
                terminal_writestring(input_buf);
            }
            else if (history_index == history_size - 1){
                history_index++;
                
                /* clear current line*/
                while (input_len > 0) {
                    terminal_backspace();
                    input_len--;
                }

                /*set current input_buf to empty*/
                input_buf[0]='\0';
                input_len = 0;
            }
        }
        extended = 0;
        outb(0x20, 0x20);
        return;
    }

    if (scancode == 0x0E){
        //terminal_writestring("backspace\n");
        if (input_len > 0) {
            input_len--;
            input_buf[input_len] = '\0';
            terminal_backspace();
        }
    }
    else {
        char ch = keyboard_to_ascii(scancode);
        if (ch) {
            terminal_putchar(ch);
            if (ch == '\n') {
                input_buf[input_len] = '\0';
                input_ready = 1;
            } else if (input_len < INPUT_BUF_LEN - 1) {
                input_buf[input_len++] = ch;
            }
        }
    }
    outb(0x20, 0x20);
}
