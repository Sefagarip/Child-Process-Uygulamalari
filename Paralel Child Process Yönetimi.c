#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define DOSYA_ADI "ornek_dosya.txt"


void create_file() {
    int fd = creat(DOSYA_ADI, 0644);
    if (fd == -1) {
        perror("Dosya olu�turma hatas�");
        exit(1);
    }
    close(fd);
    printf("Dosya olu�turuldu: %s\n", DOSYA_ADI);
    exit(0);
}


void write_file() {
    FILE *dosya = fopen(DOSYA_ADI, "w");
    if (dosya == NULL) {
        perror("Dosya a�ma hatas�");
        exit(1);
    }
    
    char *yazilacak_veri = "Merhaba! Bu bir paralel process �rne�idir.\n";
    fprintf(dosya, "%s", yazilacak_veri);
    
    fclose(dosya);
    printf("Dosyaya veri yaz�ld�.\n");
    exit(0);
}


void read_file() {
    FILE *dosya = fopen(DOSYA_ADI, "r");
    if (dosya == NULL) {
        perror("Dosya okuma hatas�");
        exit(1);
    }
    
    char buffer[256];
    printf("Dosya i�eri�i:\n");
    
    while (fgets(buffer, sizeof(buffer), dosya) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(dosya);
    exit(0);
}

int main() {
    pid_t pid1, pid2, pid3;
    int durum;

   
    pid1 = fork();
    if (pid1 == -1) {
        perror("�lk fork hatas�");
        exit(1);
    }
    else if (pid1 == 0) {
        create_file();
    }

   
    pid2 = fork();
    if (pid2 == -1) {
        perror("�kinci fork hatas�");
        exit(1);
    }
    else if (pid2 == 0) {
      
        waitpid(pid1, NULL, 0);
        write_file();
    }

  
    pid3 = fork();
    if (pid3 == -1) {
        perror("���nc� fork hatas�");
        exit(1);
    }
    else if (pid3 == 0) {
      
        waitpid(pid2, NULL, 0);
        read_file();
    }

    waitpid(pid1, &durum, 0);
    waitpid(pid2, &durum, 0);
    waitpid(pid3, &durum, 0);

    printf("T�m child process'ler tamamland�.\n");

    return 0;
}
