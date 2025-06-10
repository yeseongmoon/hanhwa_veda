  .data
statement: .asscii "Multiple of 3\n"
num: .word 0
  .text
  .global	main

main:
  @ args = 0, pretend = 0, frame = 16
  @ frame_needed = 1, uses_anonymous_args = 0
  sub  sp, sp, #16
  add  r7, sp, #0
  movs r3, #0
  str r3, [r7, #4]
  b .Loop
.L1:
  ldr r3, [r7, #4]
  cmp r3, #100
  bgt .Loop

  ldr r3, =statement
  mov r0, r3
  bl printf(PLT)

  ldr r3, [r7, #4]
  adds r3, r3, #1
  str r3, [r7, #4]

  b .Loop
.Loop:
  ldr r3, [r7, #4]
  cmp r3, #100
  ble .L1

  .size main, .-main
