/* @file  at-kbd.c
 * @brief Report keyboards present on PC
 *
 * Copyright (C) 2002,2004 Alastair McKinstry, <mckinstry@debian.org>
 * Released under the GPL
 */

#include "config.h"
#include <assert.h>
#include <debian-installer.h>
#include "xmalloc.h"
#include "kbd-chooser.h"


/**
 * @brief list of keyboards present
 */
kbd_t *at_kbd_get (kbd_t *keyboards, const char *subarch)
{
	kbd_t *k = NULL;

#if defined(__powerpc__)
	// On powerpc, only prep and chrp machines have pc keyboards
	if ((strstr(subarch, "prep") == NULL) &&
	    (strstr(subarch, "chrp") == NULL))
		return keyboards;
#endif

	k =  xmalloc (sizeof(kbd_t));	
	k->name = "at"; // This must match the name "at" in console-keymaps-at
	k->deflt = NULL;
	k->data = NULL;
	k->present = UNKNOWN;
	k->next = keyboards;
	keyboards = k;


	// /proc must be mounted by this point
	// assert (check_dir ("/proc") == 1);

	/* In 2.6 series, we can detect keyboard via /proc/bus/input
	 *
	 */
	if (check_dir ("/proc/bus/input")) {
		if ((grep ("/proc/bus/input/devices","AT Set ") > 0) ||
		    (grep ("/proc/bus/input/devices","AT Translated Set") > 0) ||
		    (grep ("/proc/bus/input/devices","AT Raw Set") > 0))
			k->present = TRUE;
		else
			k->present = FALSE;
	}
	return keyboards;
}
