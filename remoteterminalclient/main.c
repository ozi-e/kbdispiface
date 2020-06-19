#include "zhelpers.h"
#include <unistd.h>
#include <string.h>
#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    /*Connection initialization to Benthernet Broker*/
    void *context = zmq_ctx_new ();
    void *pusher = zmq_socket (context, ZMQ_PUSH);
    void *sub = zmq_socket(context, ZMQ_SUB);

    zmq_connect(pusher, "tcp://benternet.pxl-ea-ict.be:24041");
    zmq_connect(sub, "tcp://benternet.pxl-ea-ict.be:24042");

    char subTopic[] = "INTERFACE!>Ozi>";
    char pubTopic[] = "INTERFACE?>Ozi>";
    char buffer[256];
    char scanVar[256];
    char *bf;

    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, subTopic, strlen(buffer));

    int state = 1;

    while(1)
    {
        char buffer[256] = "";
        //zmq_recv(sub, buffer, 255, 0);
        //printf("%s\r\n", buffer);

        //zmq_send(pusher,)
        //strncpy(buffer, pubTopic, 22);
        //scanf("%s", scanVar);
        //strncat(buffer, scanVar , 250);
        //s_send(pusher, buffer);

        if (state == 0)
        {
            bf = s_recv(sub);
            if (strncmp(bf, "INTERFACE!>Ozi>Done", strlen(subTopic) + 4) == 0)
            {
                state = 1;
            }
            else if (strncmp(bf, "INTERFACE!>Ozi>", strlen(subTopic)) == 0)
            {
                memmove(bf, bf + strlen(subTopic), strlen(bf));
                printf("%s", bf);
            }
        }
        else if (state == 1)
        {
            strncpy(buffer, pubTopic, 22);
            scanf("%[^\n]%*c", scanVar); //apparently reads newline
            strncat(buffer, scanVar , 250);
            s_send(pusher, buffer);
            state = 0;
        }

    }
    return 0;
}
