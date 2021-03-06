#include "psh.h"

/*
 * ln - hardlink or symlink files
 *
 * Usage: ln oldfile newfile
 *        ln -s symlinkcontents symlinkfile
 */


/*
 * Create a symlink with filename PATH that contains text TEXT.
 * When fed to ls -l, this produces something that looks like
 *
 * lrwxrwxrwx  [stuff]   PATH -> TEXT
 */
static
void
dosymlink(const char *text, const char *path)
{
	if (symlink(text, path)) {
		warn("ln - symlink - %s", path);
	}
}

/*
 * Create a hard link such that NEWFILE names the same file as
 * OLDFILE. Since it's a hard link, the two names for the file
 * are equal; both are the "real" file.
 */
static
void
dohardlink(const char *oldfile, const char *newfile)
{
	if (link(oldfile, newfile)) {
		warn("ln - hardlink - %s or %s", oldfile, newfile);
	}
}

int
cmd_ln(int argc, char *argv[])
{
	/*
	 * Just do whatever was asked for.
	 *
	 * We don't allow the Unix model where you can do
	 *    ln [-s] file1 file2 file3 destination-directory
	 */
	if (argc==4 && !strcmp(argv[1], "-s")) {
		dosymlink(argv[2], argv[3]);
	}
	else if (argc==3) {
		dohardlink(argv[1], argv[2]);
	}
	else {
		warnx("Usage: ln oldfile newfile");
		warnx("       ln -s symlinkcontents symlinkfile\n");
	}
	return 0;
}
