#include <stdint.h>

void idle()
{
	asm("cli");
	asm("hlt");
}

void outb(uint16_t port, uint8_t data)
{
	asm("movb %0, %%al" : : "r"(data) :);
	asm("movw %0, %%dx" : : "r"(port) :);
	asm("outb %al, %dx");
}

void inb(uint8_t data, uint16_t port)
{
	asm("movw %0, %%dx" : : "r"(port) :);
	asm("inb %dx, %al");
	asm("movb %%al, %0" : "=r"(data) : :);
}

void kputs(const char *s)
{
	char *vRAM = (char *)0xB8000;

	while (*s != 0)
	{
		*vRAM++ = *s++;
		*vRAM++ = 0x0F;
	}
}

void panic(const char *s)
{
	kputs("panic: ");
	kputs(s);
	kputs((const char *)0x0A);

	idle();
}

void init()
{
	panic("testing init out with panic()");
}
