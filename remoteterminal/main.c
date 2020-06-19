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

    char pushtask[] = "INTERFACE?>Ozi>";  //service send commando
   // char pushanswer[]= "INTERFACE>Ozi>";
    char pushanswer_h[]= "INTERFACE!>Ozi>"; //game push answer to service
    char subtask[] = "INTERFACE?>Ozi>";  //get sent command from game
    char subanswer[]= "INTERFACE!>Ozi>";   //Channel to get from
    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, subtask, strlen(subtask));

    char cmdpath[] = "C:/WINDOWS/system32/cmd.exe";
    char temppath[1035];
    //char path[] = "E:/eJ3/NP/kbdispiface/build-remoteterminal-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/fop.txt";

    FILE *fp;

    char buffer[256] = "";

    printf("Sending command\r\n");
    //strncpy(buffer, pushanswer_h, 128);
    //strncat(buffer, "Windows Remote Console has been started, please enter your command now.\r\n", 255);
    //s_send(pusher, buffer);

    while(1)
    {
        char *buffer;
        char temppath[255];
        printf("Receiving command\r\n");
        //zmq_recv(sub, buffer, 255, 0);
        buffer = s_recv(sub);
        char *rcvstr = strrchr(buffer, '>');
        printf("first\r\n");
        //char *totalbuf = NULL; //Causes program crashing lmfao
        //char totalbuf[2000];

        //if (strstr(buffer, ".exe") != NULL)
        if (buffer > 0)
        {
            char *pathtoexe;
            //Removed delimiters and removed first char
            //printf("Executed1\r\n");
            //memcpy(pathtoexe, rcvstr, strlen(rcvstr));
            memmove(rcvstr, rcvstr + 1, strlen(rcvstr));
            //printf("Executed2\r\n");
            sprintf(rcvstr, "%s > output.txt 2>&1", rcvstr);
            system(rcvstr); //Runs command
            printf("Executed\r\n");
            fp = fopen("output.txt", "r");
              if (fp == NULL) {
                printf("Failed to run command\n" );
                //exit(1);
              }
              char *tempb;
            // Read the output a line at a time - output it.
            //s_send(pusher, fgets(path, sizeof(path), fp));
            char path[1035];
            char altbuf[1050];
            while ( fgets(path, sizeof(path), fp) != NULL) {
                //sprintf(tempb, "%s", );
                printf("%s", path);
                //strncpy(buffer, pushanswer_h, 128);
                //strncat(totalbuf, path, strlen(path));
                sprintf(altbuf, "INTERFACE!>Ozi>%s", path);
                s_send(pusher, altbuf); //Does absolutely not want to send
                //printf("TEST");
                //printf("doing stuff");
            }
            fclose(fp);
            //printf("%s", totalbuf);
            //s_send(pusher, totalbuf);
            s_send(pusher, "INTERFACE!>Ozi>Done");
        }
        else
        {
            /*strncpy(temppath, cmdpath, 255);
            strncat(temppath, " ", 2);
            char *cch = strrchr(buffer, '>');
            strncpy(buffer, cch++, 1023);
            strncat(temppath, buffer, 255);
            printf("%s\r\n", temppath);
            system(temppath);
            fp = popen(temppath, "r");
              if (fp == NULL) {
                printf("Failed to run command\n" );
                //exit(1);
              }
            // Read the output a line at a time - output it.
            while (fgets(path, sizeof(path), fp) != NULL) {
                printf("%s", path);
                strncpy(buffer, pushanswer_h, 128);
                strncat(buffer, path, 1035);
                s_send(pusher, buffer);
            }
            pclose(fp);*/
        }
    }

    /*printf("Sending [%u]...\r\n", 1);
    s_send(pusher, pushtask);
    sleep (1);

    zmq_recv(sub, buffer, 255, 0);
    printf("Received %s\r\n", buffer);

    zmq_setsockopt(sub, ZMQ_SUBSCRIBE, subanswer, strlen(subanswer));

    printf("Sending [%u]...\r\n", 2);
    s_send(pusher, pushanswer_h);
    sleep (1);

    char buffer2[512];
    zmq_recv(sub, buffer2, 512, 0);
    printf("Received %s\r\n", buffer2);*/



    //puts("");
    printf("Closing publisher...\r\n");
    zmq_close (pusher);
    printf("Closing subscriber...\r\n");
    zmq_close (sub);
    printf("Destroying socket...\r\n");
    zmq_ctx_destroy (context);
    printf("Done!\r\n");
    return 0;
}
