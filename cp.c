
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msdos_fs.h"
#include "cp.h"
#include "dir.h"



//=================================

void extract_file (char* img_file_name, char* src_name, char* dst_name){
    FILE * floppy;
    //char* src_name_8_3[12];
    // convert src_name to src_name_8_3
    // if src_name is 8.3, copy to src_name_8_3
    printf("img_file_name: %s\n", img_file_name);
    printf("src_name: %s\n", src_name);
    printf("dst_name: %s\n", dst_name);

    char src_name_8_3[12];
    char* p_src_name_8_3 = src_name_8_3;
    char *dot = strchr(src_name, '.');
    //char *src_name_8_3_ptr = src_name_8_3;
    int i;
    for(i = 0; i < 11; i++){
        src_name_8_3[i] = ' ';
    }
    src_name_8_3[11] = '\0';
    for (i = 0; i < 8; i++){
        if (src_name[i] == '\0' || src_name[i] == '.' || src_name[i] == '/' || src_name[i] == '\\'){
            break;
        }
        src_name_8_3[i] = src_name[i];
    }
    for (i = 0; i < 3; i++){
        if (dot == NULL){
            break;
        }
        if (dot[i+1] == '\0' || dot[i+1] == '/' || dot[i+1] == '\\'){
            break;
        }
        src_name_8_3[8+i] = dot[i+1];
    }
    printf("src_name_8_3: %s\n", src_name_8_3);

    floppy = fopen(img_file_name, "r");
    char sector[512];
    fseek(floppy,19*512, SEEK_SET );
    fread(sector, sizeof(sector),1,floppy);
    struct msdos_dir_entry *dir_entry =  (struct msdos_dir_entry *)sector;
    //find file in root directory
    while(1){
        //read root directory sector

        // first entry is volume name, we start from second entry
        dir_entry++;
        if (dir_entry->attr == 0x0 || dir_entry->name[0] == 229){ //if end of root directory or deleted file entry
            printf("file not found\n");
            return;
        }
        printf("dir_entry->name: %s\n", dir_entry->name);
        //find file name
        /*if (strcmp(dir_entry->name, src_name_8_3) == 0){
            printf("found file\n");
            break;
        }*/
        if (strncmp(dir_entry->name, p_src_name_8_3, 11) == 0){
            printf("found file\n");
            break;
        }
        //if end of root directory, file not found

        //else go to next entry
    }
    //find file size
    //find file cluster
    //read file cluster
    //write file cluster to dst_name
    //repeat until end of file
}


