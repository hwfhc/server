#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid,err;
    time_t date = time(0);
    char t_str[128];

    char buf[1024];

    int serv_sock,cli_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;

    /* init server socket */
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    err = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(err < 0){
        printf("bind error\n");
        return -1;
    }

    err = listen(serv_sock, 10);
    if(err < 0){
        printf("listen error\n");
        return -1;
    }

    /* accept client request */
    for(;;)	{
        socklen_t addrlen = sizeof(struct sockaddr);

        cli_sock = accept(serv_sock, (struct sockaddr*)&cli_addr, &addrlen);

        if(cli_sock < 0)
            continue;

        pid = fork();
        if(pid != 0){
            // in child process
            strftime(t_str,sizeof(t_str),"%Y-%m-%d %H:%M:%S",localtime(&date));

            strcpy(buf,t_str);

            write(cli_sock,buf,sizeof(buf));
            close(cli_sock);
            return 0;
        }
    }
}
