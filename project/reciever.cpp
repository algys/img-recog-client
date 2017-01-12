#include "reciever.h"

Data *recog;
std::mutex recog_mutex;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

Reciever::Reciever(Mat frame)
{
    std::thread thr(recognize, frame);
    thr.detach();
}

int Reciever::set_frame(Mat frame){
    if(!recog_mutex.try_lock()){
        return -1;
    }
    else {
        recog = NULL;
        std::thread thr(recognize, frame);
        thr.detach();
        return 0;
    }
}

bool Reciever::is_free(){
    if(recog_mutex.try_lock()){
        if(recog == NULL){
            recog_mutex.unlock();
            return true;
        }
        recog_mutex.unlock();
    }
    return false;
}

void recognize(Mat frame){
    std::cout<<recog_mutex.try_lock();

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    portno = 8081;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    printf("Please enter the message: ");
    bzero(buffer,256);
 //   bcopy(reinterpret_cast<void*>(&frame), reinterpret_cast<void*>(buffer), sizeof(frame));

    n = write(sockfd,reinterpret_cast<void*>(&frame),sizeof(frame));

    if (n < 0)
        error("ERROR writing to socket");
    bzero(buffer,256);

    recog = new Data;
    n = read(sockfd,reinterpret_cast<void*>(&recog),12400);
    if (n < 0)
        error("ERROR reading from socket");

    close(sockfd);
    recog_mutex.unlock();
}

Data* Reciever::tryget(){
    if(!recog_mutex.try_lock()){
        return NULL;
    }
    else {
        recog_mutex.unlock();
        Data *tmp = recog;
        recog = NULL;
        return tmp;
    }
}
