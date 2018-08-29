#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>    
#include <sys/stat.h> 
#include <fcntl.h>
#include <sys/mman.h>
#include <new>

class PRO_E{
public:
    char a;
    PRO_E(){
        a = '1';
    }
};

PRO_E* __system_property_area__;

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

    void *const memory_area = mmap(NULL, PA_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (memory_area == MAP_FAILED) {
        printf("map failed\n");
        close(fd);
        return -1;
    }

    PRO_E *pa = new(memory_area)PRO_E();

    /* plug into the lib property services */
    __system_property_area__ = pa;

    printf("open success\n");
    return 0;
}