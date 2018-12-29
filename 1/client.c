#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int fd;
    struct sockaddr_in serv_addr;
    char buf[16];

    fd = socket(AF_INET, SOCK_STREAM, 0);

    if(fd < 0){
        printf("socket error\n");
        return -1;
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(fd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr));

    read(fd,buf,16);
    write(1,buf,16);

    close(fd);

    return 0;
}
