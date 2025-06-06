/* shell.c */

/**
 *  Read a command from the user, which becomes the name of the binary to execute plus any command-line arguments (if applicable)
    Tell the kernel to execute the binary
    Read input from the user and send it to the binary
    Read output from the binary and send it to the user
    Repeat steps 3 and 4 until the binary terminates

    A kernel with an API call for executing a binary
    A way to get input from the user (typically, this requires a keyboard driver for the kernel and an API call for reading from the keyboard - may take the form of "standard input")
    A way to send output to the user (typically, this requires a video driver for the kernel and an API call for printing text to the screen - may take the form of "standard output")
 */