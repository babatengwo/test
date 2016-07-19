#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
 
 
#define FILESIZE    8*1024
#define FILESUM     16
   
static sem_t mutex; 
   
typedef struct link
{ 
    char data[FILESIZE]; 
    struct link *next; 
    struct link *read;
    struct link *write;
}NODE; 
   
NODE *init_link(void)
{ 
    int i; 
    NODE *head, *previous, *current; 
 
    previous = (NODE *)malloc(sizeof(NODE));
    if(previous == NULL)
        exit(1); 
   
    memset(previous->data, 0, FILESIZE); 
    previous->next = NULL; 
    previous->read = previous->write = NULL; 
    head = previous; 
   
    for(i=0; i<FILESUM; i++) 
    { 
        current = (NODE*)malloc(sizeof(NODE)); 
        if(current == NULL) 
            exit(1); 
   
        current->next = head; 
        previous->next = current; 
        previous = current; 
    } 
 
    return head; 
} 
   
 
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
 
 
int main(int argc , char **argv) 
{ 
    int ret; 
    NODE *head; 
    pthread_t id1,id2; 
  
    //创建信号量 并初始化其值为 1
    if ((ret=sem_init(&mutex, 0, 1)) != 0){
        perror("sem_init error"); 
        return -1; 
    } 
    
    head = init_link(); 
   
    ret = pthread_create(&id1, NULL, (void *)writeDataToFile, head); 
    ret = pthread_create(&id2, NULL, (void *)readDataFromFile, head); 
   
    pthread_join(id1, NULL); 
    pthread_join(id2, NULL); 
       
   
    return 0; 
}  
