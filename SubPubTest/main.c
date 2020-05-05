//  Pubsub envelope publisher
//  Note that the zhelpers.h file also provides s_sendmore

#include "zhelpers.h"
#include <unistd.h>
#include <string.h>

int main (void)
{
    void *context = zmq_ctx_new ();
    void *pusher = zmq_socket (context, ZMQ_PUSH);
    void *sub = zmq_socket(context, ZMQ_SUB);

    zmq_connect(pusher, "tcp://benternet.pxl-ea-ict.be:24041");
    zmq_connect(sub, "tcp://benternet.pxl-ea-ict.be:24042");

    char pushtask[] = "example>task?>Ozi>";
    //char pushanswer[]= "example>answer?>Ozi>";
    char pushanswer_h[]= "example>answer?>Ozi>\"CORONA-FREE-CHANNEL>f89531b36e7bdf954975a88c498abbd5622224d4>*HATSJU*>\"";
    char subtask[] = "example>task!>Ozi>";
    char subanswer[]= "example>answer!>Ozi>";
    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, subtask, strlen(subtask));

    printf("Sending [%u]...\r\n", 1);
    s_send(pusher, pushtask);
    sleep (1);

    char buffer[256];
    zmq_recv(sub, buffer, 256, 0);
    printf("Received %s\r\n", buffer);

    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, subanswer, strlen(subanswer));

    printf("Sending [%u]...\r\n", 2);
    s_send(pusher, pushanswer_h);
    sleep (1);

    char buffer2[512];
    zmq_recv(sub, buffer2, 512, 0);
    printf("Received %s\r\n", buffer2);

    puts("");
    printf("Closing publisher...\r\n");
    zmq_close (pusher);
    printf("Closing subscriber...\r\n");
    zmq_close (sub);
    printf("Destroying socket...\r\n");
    zmq_ctx_destroy (context);
    printf("Done!\r\n");
    return 0;
}
//
