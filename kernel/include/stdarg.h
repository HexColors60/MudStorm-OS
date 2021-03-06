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

#ifndef _STDARG_H_
#define _STDARG_H_

#include "stddef.h"

typedef uint8_t *va_list;

#define STACKITEM int

#define va_start(AP,LASTARG)                                  \
  ( AP = (( va_list ) & ( LASTARG ) + VA_SIZE( LASTARG )))

#define va_arg(AP,TYPE)                                       \
  (AP+=__va_rounded_size(TYPE),*((TYPE *)(AP-__va_rounded_size(TYPE))))

#define __va_rounded_size(TYPE)                               \
  (((sizeof(TYPE)+sizeof(int)-1)/sizeof(int))*sizeof(int))

#define VA_SIZE(TYPE)                                         \
  ((sizeof(TYPE)+sizeof(STACKITEM)-1)&~(sizeof(STACKITEM)-1))

#define va_end(AP) \
   ( AP = (void *)(0) )

#endif
