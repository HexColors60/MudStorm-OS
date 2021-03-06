/*
 * MudStorm OS LittleHacker
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <speaker.h>
#include <io.h>
#include <timer.h>

/* Speaker port enable I/O register. */
#define SPEAKER_PORT_GATE	0x61

/* Speaker port enable bits. */
#define SPEAKER_GATE_ENABLE	0x03

void sound(int frequency)
{
	uint32_t div;
	uint8_t tmp;

	div = 1193180 / frequency;
	outportb(0x43, 0xb6);
	outportb(0x42, (uint8_t)(div));
	outportb(0x42, (uint8_t)(div >> 8));

	tmp = inportb(0x61);
	if (tmp != (tmp | 3))
		outportb(0x61, tmp | 3);
}


void nosound()
{
	uint8_t tmp = (inportb(0x61) & 0xFC);
	
	outportb(0x61, tmp);
}

void beep()
{
	sound(440);
	delay_s(2);
	nosound();
}
