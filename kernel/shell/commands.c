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

#include <commands.h>
#include <shell.h>
#include <stddef.h>
#include <rtc.h>
#include <version.h>
#include <string.h>
#include <speaker.h>
#include <log.h>
#include <console.h>
#include <video.h>
#include <stdio.h>

char* argv;

void help()
{
	for (int i=0; i<NUM; i++) // Conto fino al valore della variabile NUM(definita nel file shell.h)
	{
		if (i != 4)
			printk("\n %s - %s", shellcmd[i].cmdname, shellcmd[i].cmddesc); 
			// Scrive a schermo: nome del comando - descrizione
	}
	printk("\n"); // Va a capo
}

void clear()
{
	cls(); // Pulisco lo schermo
	logo(); // Stampo a video il logo
}

void uname()
{
	if (!strcmp(argv, "-a"))
	{
		printk("\n%s%s - %s, %s: %s - %s: %s\n%s: %s\n", "MudStormOS", 
		REVISION, NAME, "Kernel", KERNEL, "Shell", SHELL, "Autore", AUTHOR); 
		// Scrive a schermo "MudStormOS-Revisione, Kernel:Versione - Shell:Versione a capo Autore: Autore"
	}
	else if (!strcmp(argv, "-r"))
	{
		printk("\n%s - %s\n", REVISION, NAME); // Scrivo a schermo "MudStormOS-Revisione"
	}
	else if (!strcmp(argv, "-k"))
	{
		printk("\n%s\n", KERNEL); // Scrivo a schermo "Kernel:Versione"
	}
	else if (!strcmp(argv, "-s"))
	{
		printk("\n%s\n", SHELL); // Scrivo a schermo "Shell:Versione"
	}
	else if (!strcmp(argv, "-n"))
	{
		printk("\n%s\n", AUTHOR); // Scrivo a schermo "Autore: Autore"
	}
	else
	{
		printk("\nUsa:\n -a (Vedi tutte le info)\n -r (Vedi numero di revisione e nome in codice)\n -k (Vedi versione kernel)\n -s (Vedi versione shell)\n -n (Vedi nome autore)\n");
	}
}

void eco()
{
	if (!strcmp(argv, NULL)) // Controllo se la stringa in argv
	{
		printk("\n"); // Se è NULL allora scrive solo un "a capo"
	}
	else 
	{
		printk("\n%s\n", argv); // Altrimenti scrive la stringa contenuta
	}
}

void cowsay()
{
	char* say;

	if (!strcmp(argv, NULL))
		say = "Ciao, ti piace MudStormOS?";
	else
		say = argv;

	printk("\n ");

	for(int i=0; i<strlen(say); i++)
		printk("_");
	
	set_color(MAGENTA);
	printk("\n %s \n ", say);
	set_color(WHITE);

	for(int i=0; i<strlen(say); i++)
		printk("-");

	if (!strcmp(argv, NULL))
	{
		printk("\n\t  o \n\t   o\n\t    ^__^\n\t    (oo)\\___________");
		printk("\n\t    (__)\\           )\\/\\/");
		printk("\n\t         |-|------w |");
		printk("\n\t         | |       ||\n");
	}
	else
	{
		printk("\n  o \n   o\n    ^__^\n    (oo)\\___________");
		printk("\n    (__)\\           )\\/\\/");
		printk("\n         |-|------w |");
		printk("\n         | |       ||\n");
	}
}

void date()
{
	read_rtc(); // Leggo dall'RTC

	printk("\n %d:%d:%d - %d/%d/%d\n", hour, minute, second, day, month, year); 
	// Scrivo a schermo "ora:minuti:secondi - giorno/mese/anno"
}

void bee()
{
	beep(); // Richiamo la funzione beep();
}

void logos()
{
	logo(); // Richiamo la funzione logo();
}

void reboot_command(int com)
{
	if (com == 0)
		reboot();
	else
		shutdown();
}

void _reboot()
{	
	if (!strcmp(argv, NULL))
	{
		printk("\nUsa:\n	-r (Riavvia)\n	-s (Spegni)");
	}
	else
	{
		if (!strcmp(argv, "-r"))
			reboot_command(0);
		else if (!strcmp(argv, "-s"))
			reboot_command(1);
		else
			printk("\nStringa non valida!\n");
	}
}