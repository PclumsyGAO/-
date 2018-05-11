#nclude<stdio.h>                                                                                                                                                                            #include<sys/types.h>                                                                                                                                                                        #include<unistd.h>                                                                                                                                                                           #include<errno.h>                                                                                                                                                                            #include<string.h>                                                                                                                                                                           #include<stdlib.h>                                                                                                                                                                           int read_pipe(int fd)                                                                                                                                                                        {                                                                                                                                                                                                char buf[600]={0};                                                                                                                                                                           read(fd,buf,sizeof(buf));                                                                                                                                                                    printf("read %lu bytes:%s.\n",strlen(buf),buf);                                                                                                                                              return 0;                                                                                                                                                                                }                                                                                                                                                                                            int write_pipe(int fd,const char* msg)                                                                                                                                                       {                                                                                                                                                                                                return write(fd,msg,strlen(msg));                                                                                                                                                        }                                                                                                                                                                                                                                                                                                                                                                                         int main()                                                                                                                                                                                   {                                                                                                                                                                                                int pid;                                                                                                                                                                                     int fd[2];                                                                                                                                                                                   if(pipe(fd))                                                                                                                                                                                 {                                                                                                                                                                                                perror("fail to pipe");                                                                                                                                                                      exit(EXIT_FAILURE);                                                                                                                                                                      }                                                                                                                                                                                            if((pid=fork())<0)                                                                                                                                                                           {                                                                                                                                                                                                perror("fail to fork");                                                                                                                                                                      exit(EXIT_FAILURE);                                                                                                                                                                      }                                                                                                                                                                                            else if(pid==0)                                                                                                                                                                              {                                                                                                                                                                                                close(fd[0]);                                                                                                                                                                            char *mes="Child process 1 is sending a message! ";                                                                                                                                              write_pipe(fd[1],mes);                                                                                                                                                                   }                                                                                                                                                                                            else                                                                                                                                                                                         {                                                                                                                                                                                                if((pid=fork())<0)                                                                                                                                                                           {                                                                                                                                                                                                perror("fail to fork");                                                                                                                                                                      exit(EXIT_FAILURE);                                                                                                                                                                      }                                                                                                                                                                                            else if(pid==0)                                                                                                                                                                              {                                                                                                                                                                                                close(fd[0]);                                                                                                                                                                            char *mes="Child process 2 is sending a message! "; include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
int read_pipe(int fd)
{
    char buf[600]={0};
    read(fd,buf,sizeof(buf));
    printf("read %lu bytes:%s.\n",strlen(buf),buf);
    return 0;
}
int write_pipe(int fd,const char* msg)
{
    return write(fd,msg,strlen(msg));
}

int main()
{
    int pid;
    int fd[2];
    if(pipe(fd))
    {
        perror("fail to pipe");
        exit(EXIT_FAILURE);
    }
    if((pid=fork())<0)
    {
        perror("fail to fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {
        close(fd[0]);
	char *mes="Child process 1 is sending a message! ";
        write_pipe(fd[1],mes);
    }
    else
    {
    	if((pid=fork())<0)
    	{
        	perror("fail to fork");
        	exit(EXIT_FAILURE);
    	}
    	else if(pid==0)
    	{
        	close(fd[0]);
		char *mes="Child process 2 is sending a message! ";
        	write_pipe(fd[1],mes);
        
    	}
	else{
		close(fd[1]);
        	read_pipe(fd[0]);
        	read_pipe(fd[0]);
	}
    }
}
