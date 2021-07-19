.set ALIGN,     1 << 0
.set MEMINFO,   1 << 1
.set VIDINFO,   1 << 2
.set FLAGS,     ALIGN | MEMINFO | VIDINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0
.long 0
.long 0
.long 0
.long 0

.long 0
.long 1024
.long 768
.long 32

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:

	movl $stack_top, %esp

        pushl $0
        popf

        pushl %ebx
        pushl %eax

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kmain

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
