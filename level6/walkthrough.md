solution level6:

-> this program uses the heap. We have 2 addresses since the main calls malloc twice: the first allocation is 64 bytes wide and the second one is 4 bytes

-> there are 2 functions: "m" and "n"
"m" only outputs "Nope" while "n" does exactly what we want: it displays the flag by opening a shell with the method system

-> the main stores the address of function "m" in the second heap memory

-> next, main calls method strcpy with the first address as destination, and argv[1] as source

-> finally, after the strcpy operation, main calls the function pointed to by our second memory block

-> from the man of strcpy:
If the destination string of a strcpy() is not large enough, then anything might happen. Overflowing fixed-length string buffers is a favorite cracker technique for taking complete control of the machine.

-> it seems that we might be able to overwrite the second memory space by overflowing with strcpy
Our goal is to change the address in the second memory block, which is "m" (0x08048468), with the address of "n" (0x08048454).

-> by displaying the addresses returned by malloc, we find out there is a 72 bytes gap between them

> scp -P 2222 Ressources/run.sh level6@127.0.0.1:/tmp/

> ./level6 `bash /tmp/run.sh`
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
