
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <netinet/in.h>

#include<sys/mman.h>
#include <signal.h>
#include <exception>
#include <execinfo.h>
#include <setjmp.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#include <libintl.h>
#include <locale.h>
#define SEMLOCK	("/tmp/semlock")

static int semid;
static int unlocksem;
int sem_creat(const char * path)
{
	int semid;
	int flags = 0666;

	flags = IPC_CREAT | IPC_EXCL | flags;
	if ((semid = semget(ftok(path,0),1, flags)) >=0)
	{
		printf("1\n");
		semctl(semid,0,SETVAL,1);
	}
	else if ( errno == EEXIST) //semaphore has create!
	{
		printf("2\n");
		semid = semget(ftok(path,0),1, 0666);
		semctl(semid,0,SETVAL,1);
	}
	else
	{
		printf("3\n");
		printf("create semaphore filad!\n");
		semid = -1;
	}

	return semid;
}

int sem_lock(int semid,short flag)
{
	struct sembuf sem;
	return 0;
	if (semid<0) return EFAULT;

	sem.sem_num = 0; //A single semaphore
	sem.sem_flg = flag;
	sem.sem_op = -1;
	return semop(semid,&sem,1);
}

int sem_unlock(int semid)
{
	struct sembuf sem;

	return 0;
	if (semid<0) return EFAULT;
	sem.sem_num = 0; //A single semaphore
	sem.sem_flg = 0;
	sem.sem_op = 1;
	return semop(semid,&sem,1);
}

int semclose(int semid)
{
	if (semid<0) return EFAULT;
	return semctl(semid,0,IPC_RMID);
}

int main(int argc, char *argv[])
{
	int semid;

	semid = sem_creat(SEMLOCK);
	system("ls -al /tmp > aaa.txt");
	semclose(semid);
}
