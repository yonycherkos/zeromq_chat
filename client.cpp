#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <zmq.h>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char const *argv[]) {

    void* context = zmq_ctx_new();
    printf("Client Starting....\n");
    void* request = zmq_socket(context, ZMQ_REQ);
    zmq_connect(request, "tcp://localhost:4040");
    for(;;) {
        char client_request[50];
        char msg[70] = "client request : ";
        printf("%s", "Enter client request :");
        cin.getline(client_request,50);
        strcat(msg,client_request);
        strcat(msg,"          ");
        zmq_msg_t req;
        zmq_msg_init_size(&req, strlen(msg));
        memcpy(zmq_msg_data(&req), msg, strlen(msg));
        zmq_msg_send(&req, request, 0);
        zmq_msg_close(&req);

        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, request, 0);
        printf("%s\n", (char*) zmq_msg_data(&reply));
        zmq_msg_close(&reply);
    }

    zmq_close(request);
    zmq_ctx_destroy(context);
    return 0;
}
