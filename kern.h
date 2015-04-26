/*
 * MCOS - Combining an OS and a website in one
 * Copyright (C) 2015 Christopher P. Sacchi and Andersen A.G. Graham
 *
 * MCOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MCOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MCOS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
