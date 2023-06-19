
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msdos_fs.h"
#include "cp.h"
#include "dir.h"



//=================================

void extract_file (char* src_name, char* dst_name){
    printf ("extract floppy file name: %s  to file name: %s \n",src_name, dst_name);

    printf("File %s does not exist in the root directory\n",src_name);

/*
    floppy = fopen(img_name, "r");
    fseek(floppy,19*512, SEEK_SET );
    fread(sector, sizeof(sector),1,floppy);


    struct msdos_dir_entry *dir_entry =  (struct msdos_dir_entry *)sector;

    // first entry is volume name, we start from second entry 
    dir_entry++;
    dir_entry->name
    
    while (dir_entry->attr & 0x30){  // while not archive entry 


*/

}

//=================================