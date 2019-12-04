solution level3:

-> our main calls the function v

-> v allocates space on the stack, then uses the method fgets to fill a buffer of 512 bytes. We cannot exploit fgets the same way we exploited gets.

-> next, v calls the method printf with the buffer as argument

-> v then gets the value of global variable m, and compares it to the integer 64:
...
0x080484da <+54>:	mov    eax,ds:0x804988c
0x080484df <+59>:	cmp    eax,0x40
...
> (gdb) x/d 0x804988c
> 0x804988c <m>: 0

-> if m equals 64, the function calls system and opens a new shell, else we leave the function

-> the initial value of m being 0, we need to find a way to change it to 64.

-> from the man of printf:
In C printf(), %n is a special format specifier which instead of printing something causes printf() to load the variable pointed by the corresponding argument with a value equal to the number of characters that have been printed by printf() before the occurrence of %n.

-> thus we can change the value of m by using the %n modifier, with the right number of bytes in the buffer:
Our buffer will contain the address of m, which is 4 bytes in size. This will cause the address to be on the stack when printf is called.
For a total of 64, we add 60 padding bytes.
To make sure we are writing on the address of m, we can check its position on the stack with a few tests. We see that it is preceded by 3 other addresses, so we will indicate an argument index of 4 with our %n modifier -> %4$n

> scp -P 2222 Ressources/run.sh level3@127.0.0.1:/tmp/

> bash -x /tmp/run.sh
> cat /tmp/buff - | ./level3
> cat /home/user/level4/.pass
> b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
