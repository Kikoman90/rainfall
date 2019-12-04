solution level4:

-> this program is practically equivalent to the previous one, apart from a few differences

-> our main calls the function n, which allocates space on the stack and fills a buffer with fgets

-> the function then calls the function p, which simply calls printf with the buffer as argument

-> next, the function n compares the value of global variable m with the integer 16930116. If m is equal to that number, n calls the method system to display the level4 flag, otherwise we leave the function

-> we can still exploit the format string vulnerability with the %n modifier, but we cannot write 16930116 characters in our buffer since we are limited by a size of 512 bytes

-> fortunately we don't have to write all the characters we can simply set a number of repetitions
so our final buffer contains:
- the address of m (size is 4 bytes) : 0x08049810 -> \x10\x98\x04\x08
- the number of repetitions : 16930116 - 4 -> %16930112x
- our %n modifier with the correct argument index -> %12$n

> scp -P 2222 Ressources/run.sh level4@127.0.0.1:/tmp/

> bash -x /tmp/run.sh
> cat /tmp/buff | ./level4
> 0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
