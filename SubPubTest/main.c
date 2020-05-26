#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  void *context = zmq_init(1);
  void *socket = zmq_socket(context, ZMQ_PUB);
  zmq_connect(socket, "tcp://benternet.pxl-ea-ict.be:24041");
  sleep(1);
  char message[1000] = "testing\n";
  while(1) {
    zmq_msg_t out_msg;
    zmq_msg_init_size(&out_msg, strlen(message));
    memcpy(zmq_msg_data(&out_msg), message, strlen(message));
    zmq_send(socket, &out_msg, 1000, 0);
    zmq_msg_close(&out_msg);
    sleep(1);
  }
}


/*//  Pubsub envelope publisher
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

    char pushtask[] = "CONSOLE>task?>a>";
    //char pushanswer[]= "CONSOLE>answer?>a>";
    char pushanswer_h[]= "CONSOLE>answer?>a>\"test>\"";
    char subtask[] = "CONSOLE>task?>a>";
    char subanswer[]= "CONSOLE>answer?>a>";
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
*/
