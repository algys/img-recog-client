#include "reciever.h"

Data *recog;
std::mutex recog_mutex;

void error(const char *msg)
{
    perror(msg);
//    exit(1);
}

void

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


    n = write(sockfd,reinterpret_cast<void*>(frame.data),480*640);

    if (n < 0)
        error("ERROR writing to socket");


    char buf[1024];
    bzero(buf, sizeof(buf));
    n = recv(sockfd,reinterpret_cast<void*>(buf),256,MSG_WAITALL);
    if (n < 0 || n == 1){
        close(sockfd);
        recog_mutex.unlock();
        return;
    }
    recog = new Data;
    recog->author=buf;

    bzero(buf, sizeof(buf));
    n = recv(sockfd,reinterpret_cast<void*>(buf),1024,MSG_WAITALL);
    if (n < 0){
        error("ERROR reading info from socket");
    }
    recog->info=buf;

    bzero(buf, sizeof(buf));
    n = recv(sockfd,reinterpret_cast<void*>(buf),256,MSG_WAITALL);
    if (n < 0){
        error("ERROR reading name from socket");
    }
    recog->name=buf;

    bzero(buf, sizeof(buf));
    n = recv(sockfd,reinterpret_cast<void*>(buf),256,MSG_WAITALL);
    if (n < 0){
        error("ERROR reading path from socket");
    }
    recog->path=buf;

    bzero(buf, sizeof(buf));
    n = recv(sockfd,reinterpret_cast<void*>(buf),256,MSG_WAITALL);
    if (n < 0){
        error("ERROR reading year from socket");
    }
    recog->year=buf;

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
