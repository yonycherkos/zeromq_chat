#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <zmq.h>

int main(int argc, char const *argv[]) {

    void* context = zmq_ctx_new();
    printf("Client Starting....\n");
    void* request = zmq_socket(context, ZMQ_REQ);
    zmq_connect(request, "tcp://localhost:4040");
    int count = 0;
    for(;;) {
        char client_request[100];
        printf("%s", "Enter client request :");
        scanf("%s\n", client_request);
        zmq_msg_t req;
        zmq_msg_init_size(&req, strlen(client_request));
        memcpy(zmq_msg_data(&req), client_request, strlen(client_request));
        zmq_msg_send(&req, request, 0);
        zmq_msg_close(&req);

        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, request, 0);
        printf("Received: %s\n", zmq_msg_data(&reply));
        zmq_msg_close(&reply);
        count++;
    }
    // We never get here though.
    zmq_close(request);
    zmq_ctx_destroy(context);
    return 0;
}