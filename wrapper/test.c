#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 200

int main() {
	long sys_return_value;
	unsigned int info[SIZE];
	sys_return_value = syscall(439, -1, &info);
	printf("My student ID: %u\n", info[0]);
	return 0;
}
