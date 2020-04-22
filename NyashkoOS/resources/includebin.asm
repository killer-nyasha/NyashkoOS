use64
format MS64 COFF

public __wallpaper
public __font
;public memcpy

section '.code' code readable executable

inb 10

;memcpy:
mov         r9,r8
mov         rax,rcx
test        r8,r8
je          __lbl2
sub         rdx,rcx
xchg        ax,ax
__lbl1:
movzx       r8d,byte [rdx+rax]
mov         byte [rax],r8b
lea         rax,[rax+1]
sub         r9,1
jne         __lbl1
mov         rax,rcx
__lbl2:
ret

section '.data' data readable writeable

__wallpaper:
file 'wallpaper.fsi'

__font:
file 'font.fsi'

pseudoHeap
db 2*1024*1024 dup (0)