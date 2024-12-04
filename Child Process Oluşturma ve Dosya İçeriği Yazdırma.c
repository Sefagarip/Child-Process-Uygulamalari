#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
    
        fprintf(stderr, "Fork i�lemi ba�ar�s�z oldu!\n");
        return 1;
    } else if (pid == 0) {
       
        printf("Child process �al���yor...\n");
        
        execlp("cat", "cat", "/etc/hostname", NULL);

        perror("execlp");
        exit(1);
    } else {
  
        printf("Parent process child process'i bekliyor...\n");

        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child process normal �ekilde sonland�. ��k�� kodu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process anormal �ekilde sonland�.\n");
        }
    }

    return 0;
}
