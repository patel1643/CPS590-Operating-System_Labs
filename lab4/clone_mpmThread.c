/*
  Name: Parth Patel
  Student#: 500893723
  CPS 590 - Lab04

  Answer for this lab:

  In this program we make a child process (heavyweight process) by using clone, but not setting 
  any flags (which is what fork does). The child would get a copy of parents memory, file descs, 
  etc, but any changes in child would be only for the child



  For making a child thread (lightweight process) see cloneThread.c
*/

#define _GNU_SOURCE  //for Ubuntu
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int fd;
int x,y;

int do_something() 
{
	x = 7;
	printf ("\nThis is process(thread) %d. \n", getpid());
	printf("x + y = %d\n", x + y);
	_exit(0);
}

int main(int argc, char *argv[]) 
{
        const int STACK_SIZE = 65536;  // note stack grows down
        char *stack, *stackTop, tempch;
        int cret;

	x = 0;
	y = 1;
        stack = malloc(STACK_SIZE);
        if (stack == NULL) {
                perror("malloc");
                exit(1);
        }
        stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */
         pid_t pid, ppid;

       	pid  = getpid();

	printf ("\nThis is process(thread) %d.\n", pid);
        printf("x + y = %d\n", x + y);

	cret = clone(do_something, stackTop, CLONE_VM|CLONE_FILES, NULL);
	if (cret == -1)	{
		perror("clone"); 
		exit(0); 
	}
	 
	return 0;
}
