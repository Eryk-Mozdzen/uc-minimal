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
	ldr r0, =0x40023830
    ldr r1, [r0]
	ldr r2, =0x01
    orr r1, r1, r2
    str r1, [r0]

	ldr r0, =0x40020000
    ldr r1, [r0]
	ldr r2, =0x400
    orr r1, r1, r2
    str r1, [r0]

main_loop:
	ldr r0, =0x40020018
    ldr r1, [r0]
	ldr r2, =0x20
    orr r1, r1, r2
    str r1, [r0]

	ldr r0, =1000000
	bl delay

	ldr r0, =0x40020018
    ldr r1, [r0]
	ldr r2, =0x200000
    orr r1, r1, r2
    str r1, [r0]

	ldr r0, =1000000
	bl delay

    b main_loop

delay:
    push {lr}
delay_loop:
    sub r0, #1
	cmp r0, #0
    bne delay_loop
    pop {pc}
