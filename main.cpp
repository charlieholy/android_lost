#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>    
#include <sys/stat.h> 
#include <fcntl.h>
#define PA_SIZE 12400
const char* property_filename = "/dev/__properties__";
int main(){
   int fd ;
    fd = open(property_filename, O_RDWR | O_CREAT | O_NOFOLLOW | O_CLOEXEC |
            O_EXCL, 0444);

    if (fd < 0) {
        printf("open error\n");
    }

    int ret = fcntl(fd, F_SETFD, FD_CLOEXEC);
    if (ret < 0){
        printf("fcntl error\n");
    }

    if (ftruncate(fd, PA_SIZE) < 0){
        printf("ftruncate error\n");
    }



    printf("open success\n");
    return 0;
}