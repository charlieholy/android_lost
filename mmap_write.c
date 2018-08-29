/*write.c*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
/*映射内存大小*/
#define MAPLEN 0x100
/*定义一个学生信息结构体*/
struct STU
{
    int id;
    char name[20];
    char sex;
};
/*出错信息统一处理函数*/
void sys_err(char *str, int exitno)
{
    perror(str);
    exit(exitno);
}

int main(int argc, char*argv[])
{
    struct STU *pm;//STU结构体指针
    int fd, i = 0;
    if(argc < 2){
        printf("args error\n");
        exit(1);
    }

    fd = open(argv[1], O_RDWR | O_CREAT, 0777); //打开一文件
    if(fd < 0){
        sys_err("open", 1);
    }

    if(lseek(fd, MAPLEN - 1, SEEK_SET) < 0){//文件偏移至分配的内存地址末端
        sys_err("lseek", 3);
    }

    if(write(fd, "\0", 1) < 0){  //末端赋值为'\0'
        sys_err("write", 4);
    }
    /*将文件映射至进程的地址空间*/
    pm = mmap(NULL, MAPLEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(pm == MAP_FAILED){
        sys_err("mmap", 2);
    }
    /*关闭文件描述符*/
    close(fd);
    /*对文件进行写入操作*/
    while(1){
        pm->id = i;
        sprintf(pm->name, "yu-%d", i);
        if(i % 2 == 0){
            pm->sex = 'm';
        }else{
            pm->sex = 'w';
        }
        i++;
        sleep(1);
    }
    munmap(pm, MAPLEN);

    return 0;
}