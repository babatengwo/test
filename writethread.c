#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


void *writeDataToFile(NODE *head) 
{ 
	NODE *current; 
	int fd, i, real_write; 
	char fdname[32]={0};

	current = head->next;

	//    sem_wait(&mutex); 

	for (i=0; i<FILESUM; i++) {
		sem_wait(&mutex); 

		sprintf(fdname,"./wdir/%d.txt", i);
		fd = open(fdname, O_RDWR|O_CREAT);

		printf("current->data = %s\n", current->data);
		real_write=write(fd, current->data, FILESIZE);
		printf("real_write = %d\n", real_write);

		current = current->next; 
		close(fd);

		sem_post(&mutex); 
		sleep(1); 	
	}

	//        sem_post(&mutex); 
	//        sleep(1); 

	return NULL;
} 
