solution level8:

-> the main is a loop which waits for user input on stdin with the method fgets, with a buffer of 128 bytes

-> at the beginning of each loop the addresses "auth" and "service" are printed: they are null ("nil") at the start of the program

-> the body of the loop is a series of conditions, more specifically comparisons between the content of our buffer and hard-coded strings: "auth ", "reset", "service", "login"

-> the program contains an instruction that opens a new shell with the method system, but to get we need to validate two conditions:
- first, the buffer needs to match with the "login" string
- then, the 32th byte starting from address "auth" must not be zero

-> to get there, we want auth to be a valid address, which we can do by making our buffer match the "auth " string
once that condition is true, auth is assigned an address on the heap with a call to malloc (4 bytes)
there is also an instruction which calls the strcpy method with auth as destination and the address of our buffer + 5 bytes as source.
However, the condition for that strcpy is that our buffer needs to be less than 30 bytes in length, which prevents us from overflowing to the 32th byte.

at this point the program displays:
0x804a008, (nil)

-> next, if our buffer matches with the "servic" string, the address service is assigned the return value of a call to strdup, with our buffer + 7 bytes as parameter

the program displays:
0x804a008, 0x804a018

-> our addresses auth and service are only 16 bytes apart, so if the rest of the buffer (the bytes following the 7 first) is at least 16 bytes we will be able to write at the address corresponding to auth[32]

-> so to sum up
> ./level8
(nil), (nil)
auth
0x804a008, (nil)
serviceAAAAAAAAAAAAAAAA
0x804a008, 0x804a018
login
$ cat /home/user/level9/.pass
$ c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
