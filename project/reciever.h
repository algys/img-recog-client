#ifndef RECIEVER_H
#define RECIEVER_H

#include "core.h"
#include <mutex>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>



class Reciever
{
public:
    Reciever(){}
    Reciever(Mat frame);
    int set_frame(Mat frame);
    Data *tryget();
    bool is_free();
};

void recognize(Mat frame);

#endif // RECIEVER_H
