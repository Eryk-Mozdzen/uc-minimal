.global vtable
.global reset_handler

.type vtable, %object
.size vtable, .-vtable
vtable:
    .word _estack
    .word reset_handler

.type reset_handler, %function
.size reset_handler, .-reset_handler
reset_handler:
    mov r0, #1

main_loop:
    b main_loop
