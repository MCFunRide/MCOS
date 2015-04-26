.global boot
.extern kmain

MBOOT_MAGIC = 0x1BADB002
MBOOT_FLAGS = 0x03
MBOOT_CHECKSUM = -(MBOOT_MAGIC + MBOOT_FLAGS)

.section .text

.align 4
mboot:
	.long MBOOT_MAGIC
	.long MBOOT_FLAGS
	.long MBOOT_CHECKSUM

boot:
	cli

	lgdt (GDT_desc)
	lcall *(0x28)

	hlt

.section .data

GDT:
	GDT_null: .quad 0

	GDT_code_CPL0:
		.word 0xFFFF
		.word 0
		.byte 0
		.byte 0x9A
		.byte 0xCF
		.byte 0
	GDT_data_CPL0:
		.word 0xFFFF
		.word 0
		.byte 0
		.byte 0x92
		.byte 0xCF
		.byte 0
	GDT_code_CPL3:
		.word 0xFFFF
		.word 0
		.byte 0
		.byte 0xFA
		.byte 0xCF
		.byte 0
	GDT_data_CPL3:
		.word 0xFFFF
		.word 0
		.byte 0
		.byte 0xF2
		.byte 0xCF
		.byte 0
	GDT_TSS:
		.word 0xFFFF
		.word TSS
		.byte 0
		.byte 0x89
		.byte 0xCF
		.byte 0
	GDT_LDT:
		.word 0xFFFF
		.word LDT
		.byte 0
		.byte 0x82
		.byte 0xCF
		.byte 0
GDT_end:
GDT_desc:
	.word GDT_end - GDT - 1
	.long GDT

TSS:
	.word 0x28
	.word 0

	.long 0x200000

	.word 0x10
	.word 0

	.long 0x200000

	.word 0x10
	.word 0

	.long 0x200000

	.word 0x10
	.word 0

	.long 0
	.long kmain
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0x200000
	.long 0
	.long 0
	.long 0

	.word 0x10
	.word 0

	.word 0x08
	.word 0

	.word 0x10
	.word 0

	.word 0x10
	.word 0

	.word 0x10
	.word 0

	.word 0x10
	.word 0

	.word 0x30
	.word 0

	.long 0

LDT:
LDT_end:
LDT_desc:
	.word LDT_end - LDT - 1
	.long LDT
