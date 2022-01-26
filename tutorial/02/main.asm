mov ah, 0x0e ; tty mode to write
mov al, 'H'
int 0x10 ; interrrupt to display

mov al, 'e'
int 0x10

mov al, 'l'
int 0x10

mov al, 'l'
int 0x10

mov al, 'o'
int 0x10

mov al, ' '
int 0x10
mov al, 'D'
int 0x10
mov al, 'i'
int 0x10
mov al, 'p'
int 0x10
mov al, 'a'
int 0x10
mov al, 'n'
int 0x10
mov al, 'k'
int 0x10
mov al, 'a'
int 0x10
mov al, 'r'
int 0x10

jmp $ ; jump to current address=infinite loop

times 510 - ($-$$) db 0
dw 0xaa55