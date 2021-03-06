/*
* MudStorm OS LittleHacker
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <stddef.h>
#include <timer.h>
#include <io.h>
#include <intr/irq.h>

int delay = 0;
volatile bool done = false;
bool uninstall = true;

void PIC_handler(struct regs *r)
/// Callback from ISR 0
{
	if ((!done) && (delay > 0))
	{
		delay--;
	}
	else if (delay == 0)
	{
		done = true;
	}
}

void delay_ms(int ms)
/// Hold the system until specified time is reached
{
	if (!uninstall)
	{
		done = false;
		delay = ms;	
		while(!done);
	}
}


void delay_s(int s)
{
	delay_ms((s * 1000));
}

void timer_install()
/// Sets up the system clock by installing the timer handler into IRQ0
{
    uint32_t hz = 1000; // 1 tick / mSec
    asm volatile ("cli"); // Stop interrupts
    uint32_t divisor = 119318 / hz; // Find the divisor
    outportb(0x43, 0x36); // Tell PIC we're setting it's frequency
    uint8_t l = (uint8_t)(divisor & 0xFF); // Bitmap Low byte
    uint8_t h = (uint8_t)(divisor >> 8) & 0xFF; // Bitmap High byte
    outportb(0x40, l); // Send Low Byte!
    outportb(0x40, h); // Send High Byte!
    irq_install_handler(0, PIC_handler); // Install Pointer to the ISRS Table
    asm volatile ("sti"); // Restore interrupts
}

void timer_uninstall()
{
	asm volatile ("cli");
	irq_uninstall_handler(0);
	uninstall = true;
	asm volatile ("sti");
}
