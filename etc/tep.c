/* TEP tools
   Tokai University, Japan */

#include <string.h>

static char rcsid[] = "$Id: tep.c,v 1.9 1997/05/27 23:03:40 drh Exp $";

#ifndef LCCDIR
#define LCCDIR "/usr/local/lib/lcc/"
#endif
#ifndef TEPASMDIR
#define TEPASMDIR "/usr/local/bin/"
#endif
#ifndef GCCLIB
#define GCCLIB "/usr/local/lib/"
#endif

char *suffixes[] = { ".c", ".i", ".s", ".o", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { LCCDIR "cpp",
	"-D__STDC__=1", "-Dtep", "-D__tep__", "-Dtokai", "-D__tokai__", "-Dunix",
	"$1", "$2", "$3", 0 };
char *include[] = { "-I" LCCDIR "include", "-I/usr/local/include",
	"-I" GCCLIB "include", "-I/usr/include", 0 };
char *com[] = { LCCDIR "rcc", "-target=tep",
	"$1", "$2", "$3", 0 };
char *as[] = { TEPASMDIR "tepasm", "-f", "-o", "$3", "$1", "$2", 0 };
char *ld[] = { TEPASMDIR "ld", "-o", "$3", "$1",
	GCCLIB "crti.o", GCCLIB "crt1.o",
	GCCLIB "crtbegin.o", "$2", "", "", "-L" LCCDIR, "-llcc",
	"-L" GCCLIB, "-lgcc", "-lm", "-lc", "",
	GCCLIB "crtend.o", GCCLIB "crtn.o", 0 };

extern char *concat(char *, char *);

int option(char *arg) {
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		cpp[0] = concat(&arg[8], "/cpp");
		include[0] = concat("-I", concat(&arg[8], "/include"));
		ld[10] = concat("-L", &arg[8]);
		com[0] = concat(&arg[8], "/rcc");
	} else if (strcmp(arg, "-g") == 0)
		;
	else if (strcmp(arg, "-pg") == 0) {
		ld[8] = GCCLIB "gmon.o";
	} else if (strcmp(arg, "-b") == 0)
		;
	else
		return 0;
	return 1;
}
