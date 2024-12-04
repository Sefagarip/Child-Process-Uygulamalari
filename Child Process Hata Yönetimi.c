#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        
        fprintf(stderr, "Fork iþlemi baþarýsýz oldu\n");
        return 1;
    }

    if (pid == 0) {
      
        FILE *dosya = fopen("test.txt", "r");
        
        if (dosya == NULL) {
          
            fprintf(stderr, "Dosya açýlamadý. Abort ediliyor.\n");
            abort(); 
        }

     
        printf("Dosya baþarýyla açýldý.\n");
        fclose(dosya);
        exit(0); 
    } else {
        
        int status;
        waitpid(pid, &status, 0);

        if (WIFSIGNALED(status)) {
          
            int signal = WTERMSIG(status);
            printf("Child process %d sinyali ile sonlandý. Sinyal numarasý: %d\n", pid, signal);

            if (signal == SIGABRT) {
                printf("abort() çaðrýsý nedeniyle sonlandý.\n");
            }
        } else if (WIFEXITED(status)) {
            
            int exit_status = WEXITSTATUS(status);
            printf("Child process normal olarak çýktý. Çýkýþ durumu: %d\n", exit_status);
        }
    }

    return 0;
}
