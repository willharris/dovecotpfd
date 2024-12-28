# dovecotpfd

Dovecot Password File Driver (dovecotpfd)

Roundcube password plugin driver that adds functionality to change passwords stored in
Dovecot passwd/userdb files (see: http://wiki.dovecot.org/AuthDatabase/PasswdFile)

This repo is a further development of https://code.google.com/archive/p/dovecotpfd/source/default/source, by Charlie Orford.

Updated for running on Ubuntu 18.04 with Roundcube 1.4.13 and PHP 7.2.

## Setup

1. Create a new user named `chgdovecotpw` with group `chgdovecotpw`.
1. Change group of dovecot users file to `chgdovecotpw`.
1. Make the dovecot users file group-writable.
1. Copy `chgdovecotpw` script to /usr/sbin.
1. Edit `dovecotpfd-setuid.c` and set the UID "define" to the id of the user you created above.
1. Compile `dovecotpfd-setuid.c` process according to instructions in that file.
1. Copy the `dovecotpfd-setuid` binary and the `dovecotpfd.php` script to `<roundcube home>/plugins/password/drivers`.
1. Edit the Roundcube password plugin `config.inc.php` file: 
  1. Set `$config['password_driver'] = 'dovecotpfd'` .
  2. Set `$config['password_dovecotpfd_scheme'] = 'SHA512-CRYPT'`, or whatever scheme you use.

## Original description

SCRIPT REQUIREMENTS:

 - PHP 5.3.0 or higher, shell access and the ability to run php scripts from the CLI

 - chgdovecotpw and dovecotpfd-setuid.c (these two files should have been bundled with this driver)

 - dovecotpfd-setuid.c must be compiled and the resulting dovecotpfd-setuid binary placed in the same directory
   as this script (see dovecotpfd-setuid.c source for compilation instructions, security info and options)

 - chgdovecotpw must be placed in a location where dovecotpfd-setuid can access it once it has changed UID (normally /usr/sbin is a good choice)

 - chgdovecotpw should only be executable by the user dovecotpfd-setuid changes UID to

 - the dovecot passwd/userdb file must be accessible and writable by the same user dovecotpfd-setuid changes UID to

 - dovecotpw (usually packaged with dovecot itself and found in /usr/sbin) must be available and executable by chgdovecotpw


