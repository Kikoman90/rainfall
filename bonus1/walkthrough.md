solution bonus1:

-> the stack of main holds a buffer of 40 bytes and an integer

-> the main stores the result of a call to atoi with argv[1] as argument in the integer, and checks that it is inferior or equal to 9
if the integer is superior to 9, we leave the main

-> the integer, which can be negative, will be represented using two's complement notation

-> the main then calls memcpy with the buffer as destination, argv[2] as source, and the number of bytes to copy equal to the integer multiplied by 4

-> since memcpy takes a type_t as its 3rd parameter, the result of the multiplication will be interpreted as an unsigned integer (unsigned representation)

-> finally, if the integer is equal to 1464814662, a new shell is open with the execle method

-> the 4 bytes of the integer are right after the 40 byte buffer on the stack, so we would overwrite it with the memcpy method with 44 as the 3rd parameter
argv[1] cannot be "11" because the main checks that the integer is inferior or equal to 9

-> ... find argv[1], prepare payload in /tmp/buff

> scp scp -P 2222 Ressources/run.sh bonus1@127.0.0.1:/tmp

> bash /tmp/run.sh
> ./bonus1 "-1073741813" `cat /tmp/buff`
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245

