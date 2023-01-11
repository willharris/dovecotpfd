/*
// ================================================================================

   dovecotpfd-setuid (http://code.google.com/p/dovecotpfd/)

   Simple C wrapper to allow running chgdovecotpw as a specific user. This wrapper is necessary as linux
   prevents scripts from changing uid themselves (see: https://bugs.php.net/bug.php?id=22890)

   Copyright (c) 2011 Charlie Orford

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use,
   copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
   the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
   OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   $v 1.1 (2011-09-08)

// ================================================================================


INSTRUCTIONS FOR COMPILATION:
Place dovecotpfd-setuid.c in roundcubedir/plugins/password/drivers and issue the following commands:

gcc -o dovecotpfd-setuid dovecotpfd-setuid.c
strip dovecotpfd-setuid
chown root:www-data dovecotpfd-setuid
chmod 4750 dovecotpfd-setuid

*/

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

// Set the UID this script will change user to (defaults to nobody).
// For security reasons DO NOT set this to 0 (i.e. root). Instead, create a new user, specify the uid of this new user here
// and then make this user the owner of the dovecot passwd/userdb file and the chgdovecotpw script. This user should be the
// only one who can execute the chgdovecotpw script and write to the dovecot passwd/userdb file.
//#define UID 65534
#define UID 5001

// Set path to chgdovecotpw (which you would normally place in /usr/sbin)
#define CMD "/usr/sbin/chgdovecotpw"

#define LOGFILE "/tmp/suidlog.txt"

int main(int argc, char *argv[]) {
    int i;
    FILE *fd;

    argv[0] = CMD;

    fd = fopen(LOGFILE,"w");
    if (!fd) {
        fprintf(stderr, "Unable to create %s", LOGFILE);
    }

    for (i = 0; i < argc - 1; i++) {
        fprintf(fd, "%d: %s\n", i, argv[i]);
    }

    if (setuid(UID) == 0) { 
        if (execv(CMD, argv + 1) != 0) {
            fprintf(fd, "Error executing %s\n", CMD);
            return 1;
        }
    } else {
        fprintf(fd, "Error on setuid: %d\n", errno);
        return 1;
    }

    fprintf(fd, "Success!\n");

    fclose(fd);

    return 0;

}
