#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


#define IMG_SIZE (358 * 288)

void *readDataFromFile(NODE *head) 
{ 
	int fd, real_read, i;
	NODE *current; 
	char fdname[32]={0};

	current = head->next; 

	for (i=0; i<FILESUM; i++) {             
		sem_wait(&mutex); 
#if 0
		if (current->read == current->write) {
			sem_post(&mutex);
			continue;
		}
#endif
		sprintf(fdname, "./rdir/%d.txt", i);
		fd = open(fdname, O_RDONLY);

		real_read=read(fd, current->data, FILESIZE);

		printf("real_read = %d\n", real_read);
		printf("current->data = %s\n", current->data);

		current = current->next; 
		close(fd);

		sem_post(&mutex); 
	}          
	//        sem_post(&mutex); 
	//        sleep(2); 


	return NULL;
} 

