#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>


#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
                __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

int main(int argc, char *argv[])
{
        int fd = open("/dev/mem", O_RDWR);
        void *map_base = mmap(NULL, 4096, PROT_READ|PROT_WRITE,
                        MAP_SHARED, fd, target & ~MAP_MASK);

        if (map_base == (void *)-1)
                FATAL;

}
