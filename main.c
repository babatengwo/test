#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


#define IMG_SIZE (352*288)

struct v4l2_devices_t {
	struct v4l2_buffer *readp;
	struct v4l2_buffer *writep;
	struct v4l2_buffer buff[5];
	int count;
	int read_fd;
	int write_fd;
	pthread_t thread1;
	pthread_t thread2;
	sem_t mutex;
};

struct v4l2_devices_t *v4l2_dev = NULL;

struct v4l2_buffer {
	char *data;
	int data_size;
	struct v4l2_buffer *next;
};
 

int v4l2_buffer_init(v4l2_buffer *buff)
{
	int i;

	if (!buff) {
		perror("poniter is NULL !\n");
		return -1;
	}

	for (i = 0; i < 5; i++) {
		buff[i].data = (struct v4l2_buffer *)malloc(struct v4l2_buffer);
		if (!buff[i].data) {
			perror("error \n");
			return -1;
		}
	}
	return 0
}


void *writeDataToFile(void *data) 
{ 
	int fd, i, real_write; 
	char fdname[32]={0};
	struct v4l2_devices_t *v4l2_dev = (struct v4l2_devices_t *)data;

	while (1) {
	
		sem_wait(v4l2_dev)
	}

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


int main(int argc , char **argv) 
{ 
	int ret; 
	NODE *head;
	int fd1, fd2;
	pthread_t id1,id2; 

	if (!v4l2_dev) {
		v4l2_dev = (struct v4l2_devices_t *)malloc(sizeof(struct v4l2_devices_t));
	}



	//创建信号量 并初始化其值为 1
	if ((ret=sem_init(&v4l2_dev->mutex, 0, 1)) != 0){
		perror("sem_init error"); 
		return -1; 
	} 
	
	ret = v4l2_buffer_init(v4l2_dev->buff);
	if (ret) {
		perror("buffer init failed !\n");
		return -1;
	}

	fd1 = open("akiyo_cif352x288.yuv", O_RDONLY);
	if (fd) {
		perror("open read file error\n");
		return -1;
	}
	fd2 = open("aaa.yuv", O_RDWR|O_CREAT);
	if (fd) {
		perror("open write file error\n");
		return -1;
	}

	ret = pthread_create(&id1, NULL, (void *)writeDataToFile, v4l2_dev); 
	ret = pthread_create(&id2, NULL, (void *)readDataFromFile, v4l2_dev); 

	pthread_join(id1, NULL); 
	pthread_join(id2, NULL); 


	return 0; 
}  
