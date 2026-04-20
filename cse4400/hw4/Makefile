TARGETS=q1 q2
SRCS=q1.c q2.c
CC=gcc
CFLAGS= -Wall -g -Wextra
SFN=secret.txt

all : $(TARGETS)

q1: q1.c

q2: q2.c
	$(CC) $(CFLAGS) -o $@ $<
	sudo chown root $@
	sudo chmod +s $@

sfile: 
	echo "This is a secret" > $(SFN)
	chmod 0600 $(SFN)
	sudo chown root:root $(SFN)

clean: 
	@rm -f $(TARGETS) *.o a.out copied.txt
	@sudo rm $(SFN)

