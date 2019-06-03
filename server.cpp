#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <zmq.h>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char const *argv[]) {

  void* context = zmq_ctx_new();
  void* respond = zmq_socket(context, ZMQ_REP);
  zmq_bind(respond, "tcp://*:4040");
  printf("Starting...\n");
  for(;;) {
      zmq_msg_t request;
      zmq_msg_init(&request);
      zmq_msg_recv(&request, respond, 0);
      printf("%s\n",(char*)  zmq_msg_data(&request));
      zmq_msg_close(&request);

      char server_reply[50];
      char msg[80] = "Server's response : ";
      printf("%s", "Enter server reply :");
      cin.getline(server_reply,50);
      strcat(msg,server_reply);
      strcat(msg,"          ");
      zmq_msg_t reply;
      zmq_msg_init_size(&reply, strlen(msg));
      memcpy(zmq_msg_data(&reply), msg, strlen(msg));
      zmq_msg_send(&reply, respond, 0);
      zmq_msg_close(&reply);

  }
  zmq_close(respond);
  zmq_ctx_destroy(context);
  return 0;
}
