#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Düzenlenecek dosyanýn adýný ve içeriðini saklamak için yapý
struct File {
    char name[50];
    char content[1000];
};

// Yeni bir dosya oluþturur
void createFile(struct File *file, char *name) {
    strcpy(file->name, name);
    file->content[0] = '\0';
}

// Dosyayý kaydeder
void saveFile(struct File *file) {
    FILE *fp = fopen(file->name, "w");
    if (fp == NULL) {
        printf("Dosya kaydedilemedi.\n");
        return;
    }
    fprintf(fp, "%s", file->content);
    fclose(fp);
    printf("Dosya kaydedildi: %s\n", file->name);
}

int main() {
    struct File file;
    char choice;
    char fileName[50];

    while (1) {
        printf("\nKod Düzenleyici\n");
        printf("1. Yeni Dosya Oluþtur\n");
        printf("2. Dosyayý Aç\n");
        printf("3. Dosyayý Kaydet\n");
        printf("4. Çýkýþ\n");
        printf("Seçiminizi girin: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Yeni dosya adý: ");
                scanf("%s", fileName);
                createFile(&file, fileName);
                break;
            case '2':
                printf("Açýlacak dosya adý: ");
                scanf("%s", fileName);
                FILE *fp = fopen(fileName, "r");
                if (fp == NULL) {
                    printf("Dosya bulunamadý.\n");
                } else {
                    fseek(fp, 0, SEEK_END);
                    long fileSize = ftell(fp);
                    rewind(fp);
                    fread(file.content, 1, fileSize, fp);
                    file.content[fileSize] = '\0';
                    fclose(fp);
                    printf("Dosya açýldý: %s\n", fileName);
                }
                break;
            case '3':
                if (file.name[0] != '\0') {
                    saveFile(&file);
                } else {
                    printf("Önce bir dosya oluþturun veya açýn.\n");
                }
                break;
            case '4':
                printf("Çýkýlýyor.\n");
                exit(0);
            default:
                printf("Geçersiz seçenek. Lütfen tekrar deneyin.\n");
        }
    }

    return 0;
}
