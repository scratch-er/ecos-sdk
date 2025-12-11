.section entry
.global _start
_start:
    # Initialize stack pointer
    la sp, _stack_pointer

    # Clear BSS section
    la t0, _bss_start
    la t1, _end
    bge t0, t1, 2f
1:
    sw zero, 0(t0)
    addi t0, t0, 4
    blt t0, t1, 1b
2:

    # Call main
    call main
loop:
    j loop
    