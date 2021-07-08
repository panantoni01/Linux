[bits 16]
[org 0x7C00]

cli
; get drive number
mov  [BOOT_DRIVE], dl
; print menu
mov si, opt1
call print_string
mov si, newline
call print_string
mov si, opt2
call print_string
mov si, newline,
call print_string
; load MIT license from 2nd disk sector
call disk_load
; get char from user
getchar:
    mov ah, 0x00
    int 0x16
    cmp al, '1'
    je license
    cmp al, '2'
    je reboot
    jmp getchar

license:
    mov si, 0x1000
    call print_string
    jmp getchar
reboot:
    jmp 0xffff:0000

print_string:
    mov ah, 0x0e
.while:
    lodsb
    or  al, al
    jz .done
    int 0x10
    jmp .while
.done:
    ret 

disk_load:
    mov bx, 0x1000
    mov dl, [BOOT_DRIVE]
    mov ch, 0x00 ; 0 cylinder
    mov dh, 0x00 ; 0 head
    mov cl, 0x02 ; 2 sector offset
    mov di, 3
try:
    mov ah, 0x02 ; arg to int 0x13 
    mov al, 0x01 ; only 1 sector to read
    int 0x13
    jc retry
    jmp ready
retry:
    mov  ah, 0x00 ; reset disk system
    int  0x13
    dec  di
    jnz try
    jmp disk_error
ready:
    ret

disk_error:
    mov si, disk_error_msg
    call print_string
    hlt


BOOT_DRIVE     db 0
opt1   db  "1) License", 0
opt2   db  "2) Reboot", 0
disk_error_msg db "Disk read error!", 0
newline dw 0x0d0a 
 
times   510-($-$$) db 0
dw 0xaa55
