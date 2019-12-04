solution level0:

-> there is a binary called level0, belonging to user level1, with setuid enabled

-> we use gdb to inspect and disassemble the program

> gdb level0
> (gdb) disassemble main

-> first we can see that our program calls the atoi method on argv[1]
...
0x08048ec9 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
0x08048ecc <+12>:	add    eax,0x4
0x08048ecf <+15>:	mov    eax,DWORD PTR [eax]
0x08048ed1 <+17>:	mov    DWORD PTR [esp],eax
0x08048ed4 <+20>:	call   0x8049710 <atoi> 
...

-> then the program compares the return value of atoi with the integer 423
...
0x08048ed9 <+25>:	cmp    eax,0x1a7
...

-> if the comparison fails, the programs displays a message on the standard error stream

-> else the program calls some methods related to effective uid and gid, but most importantly it calls the execve method to launch a shell (/bin/sh)

-> therefore, all we have to do is to send "423" to our program
this will open a shell with execution rights, from where we can display the flag we need

> ./level0 423
$ cat /home/user/level1/.pass
$ 1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
