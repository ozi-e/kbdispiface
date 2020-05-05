#include <stdio.h>
#include <zmq.h>

void * context; //Global context, because you only need one !

int main( int argc, char * argv[] )
{
    context = zmq_ctx_new();

    void * pusher = zmq_socket( context, ZMQ_PUSH );
    zmq_connect( pusher, "tcp://benternet.pxl-ea-ict.be:24041" );

    zmq_send( pusher, "Stuff sent", 10, 0 );
    zmq_close( pusher );
    zmq_ctx_shutdown( context );
    zmq_ctx_term( context );
    return 0;
}
