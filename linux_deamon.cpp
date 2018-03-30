
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

void server() {
	int count = 1;
	while (true) {
		printf("server.%d\n", count);
		count++;
		sleep(1);
	}
}
void deamon() {
	// if not using deamon, directly run server;
	// if (false) {
	//	server();
	// }
	printf("start deamon...\n");
	
	// fork son
	int pid = fork();
	if (pid > 0) { // this is father
		int status = 0;
		if (waitpid(pid, &status, 0) == -1) {
			printf("wait child process error! ret = -1.\n");
		}
		printf("father process exit.\n");
		exit(0);	// fathre process exit
	}
	
	// fork son's son
	pid = fork();
	if (pid < 0) {
		printf("fork son's son process error. ret = -1.\n");
	}
	if (pid > 0) {
		printf("son process exit. ret = 0.\n");
		exit(0);	//son process exit
	}
	
	//son's son process start.
	printf("son's son(deamon) process running...\n");
	
	//run server
	server();
}
int main()
{
	deamon();
	printf("over\n");
	return 0;
}
