
// Parth Patel - 500893723
// Lab - 07 CPS 590


//  3. Kirk and spock ended at the same time and an empty buffer like is sent to the spock.
//  However, spock catches this empty buffer line and throws an error to end the program.

//  4. Spock gives the message "msgget: No such file or directory" because
//  it is trying to recieve a message from the empty queue.
//  As such a negative 1 is returned from the function (msqid = msgget(key, 0644)
//  and an error is thrown.

//  5. Spock wont end because it is only recieving messages from kirk
// and so it doesnt recieve the signal to end.

//  7. kirk.c deletes the message queue using the function msgctl. When a cntrl d
//  is inputted an EOF message is sent so when you use cntrl D kirk doesn't
//  close immediately, rather it stops sending messages to the message queue
//  then it deletes the message queue. However, when a cntrl C is sent, a
//  SIGINT signal is sent to the foreground process which ends the process immediately.
//  This means that the function msgctl was never used to delete the message queue and as
//  such the message queue is still there.

//  8. The spockKey processes output the messages in the order they were run in.
//  To be more specific when a message is sent from kirkKey.c it will send it to the first
//  spockKey process that was run, then the next message sent will be sent to the second
//  spockKey process that was run and so on. This tells us that the process is scheduling
//  each of these processes to recieve input in order. As a process recieves the I/O event
//  it was waiting for it outputs the message and goes back into the queue to wait on an I/O event.

// From: http://beej.us/guide/bgipc/output/html/multipage/mq.html
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

int main(int argc, char *argv[])
{
    struct my_msgbuf buf;
    int msqid;
    int key;

    if(argc >= 1 && atoi(argv[1])){
        key = atoi(argv[1]);
    }else{
        perror("argv[1]");
        exit(1);
    }

    if ((key = ftok("kirk.c", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Enter lines of text, ^D to quit:\n");

    buf.mtype = 1; /* we don't really care in this case */

    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
	{
        int len = strlen(buf.mtext);

        /* ditch newline at end, if it exists */
        if (buf.mtext[len-1] == '\n')
			buf.mtext[len-1] = '\0';

        if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}

