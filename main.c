#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
 
int main(int argc , char **argv) 
{ 
	int ret; 
	NODE *head;
	int fd1, fd2;
	pthread_t id1,id2; 

	//创建信号量 并初始化其值为 1
	if ((ret=sem_init(&mutex, 0, 1)) != 0){
		perror("sem_init error"); 
		return -1; 
	} 

	head = init_link(); 

	fd1 = open("aaa.yuv", O_RDONLY);
	if (fd) {
		perror("open read file error\n");
		return -1;
	}
	fd2 = open(fdname, O_RDWR|O_CREAT);
	if (fd) {
		perror("open read file error\n");
		return -1;
	}

	ret = pthread_create(&id1, NULL, (void *)writeDataToFile, head); 
	ret = pthread_create(&id2, NULL, (void *)readDataFromFile, head); 

	pthread_join(id1, NULL); 
	pthread_join(id2, NULL); 


	return 0; 
}  
