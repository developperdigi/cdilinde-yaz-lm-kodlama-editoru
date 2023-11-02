#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// D�zenlenecek dosyan�n ad�n� ve i�eri�ini saklamak i�in yap�
struct File {
    char name[50];
    char content[1000];
};

// Yeni bir dosya olu�turur
void createFile(struct File *file, char *name) {
    strcpy(file->name, name);
    file->content[0] = '\0';
}

// Dosyay� kaydeder
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
        printf("\nKod D�zenleyici\n");
        printf("1. Yeni Dosya Olu�tur\n");
        printf("2. Dosyay� A�\n");
        printf("3. Dosyay� Kaydet\n");
        printf("4. ��k��\n");
        printf("Se�iminizi girin: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Yeni dosya ad�: ");
                scanf("%s", fileName);
                createFile(&file, fileName);
                break;
            case '2':
                printf("A��lacak dosya ad�: ");
                scanf("%s", fileName);
                FILE *fp = fopen(fileName, "r");
                if (fp == NULL) {
                    printf("Dosya bulunamad�.\n");
                } else {
                    fseek(fp, 0, SEEK_END);
                    long fileSize = ftell(fp);
                    rewind(fp);
                    fread(file.content, 1, fileSize, fp);
                    file.content[fileSize] = '\0';
                    fclose(fp);
                    printf("Dosya a��ld�: %s\n", fileName);
                }
                break;
            case '3':
                if (file.name[0] != '\0') {
                    saveFile(&file);
                } else {
                    printf("�nce bir dosya olu�turun veya a��n.\n");
                }
                break;
            case '4':
                printf("��k�l�yor.\n");
                exit(0);
            default:
                printf("Ge�ersiz se�enek. L�tfen tekrar deneyin.\n");
        }
    }

    return 0;
}
