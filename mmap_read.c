/*read.c*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAPLEN 0x1000

struct STU
{
    int id;
    char name[20];
    char sex;
};

void sys_err(char *str, int exitno)
{
    perror(str);
    exit(exitno);
}

int main(int argc, char *argv[])
{
    struct STU *pm;
    int fd, i = 0;
    if (argc < 2) {
        printf("args error\n");
        exit(1);
    }

    fd = open(argv[1], O_RDWR);
    if (fd < 0){
        sys_err("open", 1); 
    }

    pm = mmap(NULL, MAPLEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(pm == MAP_FAILED){
        sys_err("mmap", 2);
    }
    /*关闭文件*/
    close(fd);
    /*删除文件*/
    unlink(argv[1]);
    /*在内存中读数据*/
    while(1){
        printf("%d\n", pm->id);
        printf("%s\n", pm->name);
        printf("%c\n", pm->sex);
        sleep(1);
    }
    munmap(pm, MAPLEN);

    return 0;
}