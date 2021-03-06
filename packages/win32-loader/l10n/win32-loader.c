/*
 *  win32-loader.c -- l10n support
 *  Copyright (C) 2007,2008,2009  Robert Millan <rmh@aybabtu.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <locale.h>
#include <libintl.h>
#define _(str) gettext(str)
#include <stdio.h>

int
main (int argc, char **argv)
{
  char *nsis_lang;

  setlocale (LC_ALL, "");
  textdomain ("win32-loader");
  bindtextdomain ("win32-loader", TEXTDOMAINDIR);

/*
  translate:
  This must be a valid string recognised by Nsis.  If your
  language is not yet supported by Nsis, please translate the
  missing Nsis part first.
 */
  nsis_lang = _("LANG_ENGLISH");

  auto void langstring (char *code, char *p);
  void langstring (char *code, char *p)
  {
    printf ("LangString %s ${%s} \"", code, nsis_lang);
    for (; *p ; p++)
      switch (*p)
      {
	case '\n':
	  printf ("$\\n");
	  break;
	case '\\':
	  printf ("$\\");
	  break;
	case '"':
	  printf ("$\\\"");
	  break;
	default:
	  putchar (*p);
      }
    printf ("\"\n");
  }

/*
  translate:
  The nlf file for your language should be found in
  /usr/share/nsis/Contrib/Language files/
 */
  printf ("LoadLanguageFile \"${NSISDIR}\\Contrib\\Language files\\%s\"\n", _("English.nlf"));

/*
  translate:
  This is the program name, that appears in the installer windows captions and in the Windows Uninstaller dialog.
  Ampersands (&) are _forbidden_ in that string.
 */
  langstring ("program_name",			_("Debian-Installer loader"));
  langstring ("error_missing_ini",		_("Cannot find win32-loader.ini."));
  langstring ("error_incomplete_ini",		_("win32-loader.ini is incomplete.  Contact the provider of this medium."));
  langstring ("detected_keyboard_is",		_("This program has detected that your keyboard type is \"$0\".  Is this correct?"));
  langstring ("keyboard_bug_report",		_("Please send a bug report with the following information:\n\n - Version of Windows.\n - Country settings.\n - Real keyboard type.\n - Detected keyboard type.\n\nThank you."));
  langstring ("not_enough_space_for_debian",	_("There doesn't seem to be enough free disk space in drive $c.  For a complete desktop install, it is recommended to have at least 3 GB.  If there is already a separate disk or partition for this install, or if you plan to replace Windows completely, you can safely ignore this warning."));
  langstring ("not_enough_space_for_loader",	_("Error: not enough free disk space.  Aborting install."));
  langstring ("unsupported_version_of_windows",	_("This program doesn't support Windows $windows_version yet."));
  langstring ("amd64_on_i386",			_("The system version you're trying to install is designed to run on modern, 64-bit computers.  However, your computer is incapable of running 64-bit programs.\n\nUse the 32-bit (\"i386\") version, or the Multi-arch version which is able to install either of them.\n\nThis installer will abort now."));
  langstring ("i386_on_amd64",			_("Your computer is capable of running modern, 64-bit operating systems.  However, the system version you're trying to install is designed to run on older, 32-bit hardware.\n\nYou may still proceed with this install, but in order to take the most advantage of your computer, we recommend that you use the 64-bit (\"amd64\") version instead, or the Multi-arch version which is able to install either of them.\n\nWould you like to abort now?"));
/*
  translate:
  "system partition" and "boot partition" are defined by Microsoft to mean the opposite of what a
  normal person would expect they mean, so please keep the quotes, and translate them as literally
  as possible.  Also, I suggest you use the same term used in http://support.microsoft.com/kb/314470
  if that is available for your language.
 */
  langstring ("cant_find_system_partition",	_("Unable to find \"system partition\", assuming it is the same as the \"boot partition\" ($c)."));
  langstring ("expert1",			_("Select install mode:"));
  langstring ("expert2",			_("Normal mode.  Recommended for most users."));
  langstring ("expert3",			_("Expert mode.  Recommended for expert users who want full control of the install process."));
  langstring ("expert4",			_("PXE mode: install a PXE loader to allow remote kernel loading."));
  langstring ("rescue1",			_("Select action:"));
  langstring ("rescue2",			_("Begin install on this computer."));
  langstring ("rescue3",			_("Repair an installed system (rescue mode)."));
  langstring ("kernel1",			_("Select the kernel:"));
  langstring ("kernel2",			_("GNU/Linux"));
  langstring ("kernel3",			_("GNU/kFreeBSD"));
  langstring ("kernel4",			_("GNU/Hurd"));
  langstring ("graphics1",			_("Select install mode:"));
  langstring ("graphics2",			_("Graphical install"));
  langstring ("graphics3",			_("Text install"));
  langstring ("nsisdl1",			_("Downloading %s"));
  langstring ("nsisdl2",			_("Connecting ..."));
  langstring ("nsisdl3",			_("second"));
  langstring ("nsisdl4",			_("minute"));
  langstring ("nsisdl5",			_("hour"));
/*
  translate:
  This string is appended to "second", "minute" or "hour" to make plurals.
  I know it's quite unfortunate.  An alternate method for translating NSISdl
  has been proposed [1] but in the meantime we'll have to cope with this.
  [1] http://sourceforge.net/tracker/index.php?func=detail&aid=1656076&group_id=22049&atid=373087
 */
  langstring ("nsisdl6",			_("s"));
  langstring ("nsisdl7",			_("%dkB (%d%%) of %dkB at %d.%01dkB/s"));
  langstring ("nsisdl8",			_(" (%d %s%s remaining)"));
  langstring ("di_branch1",			_("Select which version of Debian-Installer to use:"));
  langstring ("di_branch2",			_("Stable release.  This will install Debian \"stable\"."));
  langstring ("di_branch3",			_("Daily build.  This is the development version of Debian-Installer.  It will install Debian \"testing\" by default, and may be capable of installing \"stable\" or \"unstable\" as well."));
/*
  translate:
  You might want to mention that so-called "known issues" page is only available in English.
 */
  langstring ("di_branch4",			_("It is recommended that you check for known issues before using a daily build.  Would you like to do that now?"));
  langstring ("custom1",			_("The following parameters will be used.  Do NOT change any of these unless you know what you're doing."));
  langstring ("custom2",			_("Proxy settings (host:port):"));
  langstring ("custom3",			_("Location of boot.ini:"));
  langstring ("custom5",			_("Base URL for netboot images (linux and initrd.gz):"));
  langstring ("error",				_("Error"));
  langstring ("error_copyfiles",		_("Error: failed to copy $0 to $1."));
/*
  translate:
  $0 will be "Release" (it is a filename).
  */
  langstring ("gpg_checking_release",		_("Checking GPG signature on $0."));
/*
  translate:
  $0 will be "Release" (it is a filename).
  */
  langstring ("unsecure_release",		_("The downloaded $0 file cannot be trusted! Aborting."));
/*
  translate:
  This appears in a MessageBox when the md5 checksum verification failed. $0 is a url; $2 is the filename $1 is the
  computed checksum and $4 is the expected one.
 */
  langstring ("checksum_mismatch",		_("Checksum mismatch for $0/$2. Got $1 when expecting $4. Aborting."));
/*
  translate:
  $2 is a filename
  */
  langstring ("computing_checksum",		_("Computing checksum for $2"));
  langstring ("generating",			_("Generating $0"));
  langstring ("appending_preseeding",		_("Appending preseeding information to $0"));
  langstring ("error_exec",			_("Error: unable to run $0."));
  langstring ("disabling_ntfs_compression",	_("Disabling NTFS compression in bootstrap files"));
  langstring ("registering_ntldr",		_("Registering in NTLDR"));
  langstring ("registering_bootmgr",		_("Registering in BootMgr"));
  langstring ("error_bcdedit_extract_id",	_("Error: failed to parse bcdedit.exe output."));
  langstring ("system_file_not_found",		_("Error: $0 not found.  Is this really Windows $windows_version?"));
  langstring ("warning1",			_("VERY IMPORTANT NOTICE:\\n\\n"));
/*
  translate:
  The following two strings are mutualy exclusive.  win32-loader
  will display one or the other depending on version of Windows.
  Take into account that either option has to make sense in our
  current context (i.e. be careful when using pronouns, etc).
 */
  langstring ("warning2_direct",		_("The second stage of this install process will now be started.  After your confirmation, this program will restart Windows in DOS mode, and automatically load the next part of the install process.\\n\\n"));
  langstring ("warning2_reboot",		_("You need to reboot in order to proceed with the install process.  During your next boot, you will be asked whether you want to start Windows or continue with the install process.\\n\\n"));
  langstring ("warning3",			_("During the install process, you will be offered the possibility of either reducing your Windows partition or completely replacing it.  In both cases, it is STRONGLY RECOMMENDED that you have previously made a backup of your data.  The authors of this software will NOT take ANY RESPONSIBILITY in the event of data loss.\\n\\nOnce your install is complete (and if you have chosen to keep Windows in your disk), you can uninstall this loader through the Windows Add/Remove Programs dialog in Control Panel."));
  langstring ("reboot_now",			_("Do you want to reboot now?"));

  return 0;
}
