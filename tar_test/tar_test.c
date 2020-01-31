#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>


int main()
{
        clock_t start, end;

        start = clock();
        system("tar -zcvf /tmp/TEST.cxob /root/TEST.bin");
        sync();
        end = clock();

        printf("s=%lu, e=%lu\n", start, end);
        printf("Used %f sec to compress.\n", (end-start)*1.0);
        return 0;
}
