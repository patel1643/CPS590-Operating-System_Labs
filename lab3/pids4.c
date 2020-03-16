#define _GNU_SOURCE  //for Ubuntu
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*
Name: Parth Patel
Student ID: 500893723
Course: CPS590
Lab 3 Solution
*/


/*
Answer 2: When you execute pids2.c file, the child process often thinks its parent’s 
PID is something other than what was printed by the parent. It is because the parent 
process is finished before the child processes exits (i.e because of sleep function) or a signal is received.
*/

/*
Answer 3: When you execute pids3.c file, it usually behaves like pids1 (child gets correct parent PID), 
but sometimes it behaves like pids2 (child thinks its parent's PID is something else). 
It is because parent process is still in execution after the child process exits and sometimes it is finished early before the child processes exits. 
*/


/* 
To avoid this we can use wait() function, which blocks the parents process until the child process is still in execution.
*/

int main (void)
{
   int pid, fpid, ppid;

   fpid = fork ();

   printf ("fpid is is %d\n", fpid);
   wait();
   if (fpid > 0) {
       pid  = getpid();
       ppid = getppid();
       printf ("\nThis is Parent. My pid %d. My parent's pid %d\n", pid, ppid);
   }
   else if (fpid == 0) {
       pid  = getpid();
       ppid = getppid();
       printf ("\nThis is Child. My pid %d. My parent's pid %d\n", pid, ppid);
   }
   else {
       printf ("fork failed\n");
   }

   return (0);
}

