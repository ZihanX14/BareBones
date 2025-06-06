.global gdt_flush
gdt_flush:
    movl 4(%esp), %eax
    lgdt (%eax)
    
    mov $0x10, %ax        # 0x10 = offset of data segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    jmp $0x08, $flush     # 0x08 = offset of code segment descriptor
flush:
    ret
