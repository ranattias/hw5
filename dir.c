#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msdos_fs.h"


//Open Questions
// file name is 8+3 or 256bit (extended)?



void img_dir (char *img_name){
    FILE * floppy;
    char sector[512];

    
    // read BPB sector
   	//struct fat_boot_sector *fbs = (struct fat_boot_sector *)sector;
    //printf("image file name: %s\n",img_name);
    floppy = fopen(img_name, "r");
    //fread (sector, sizeof(sector),1,floppy);
    //printf("test %d\n",fbs->fat_length);
    //printf("root directory entries  %x %x\n",fbs->dir_entries[0],fbs->dir_entries[1]);
    
    
    //read root directory sector:

    fseek(floppy,19*512, SEEK_SET );
    fread(sector, sizeof(sector),1,floppy);


    struct msdos_dir_entry *dir_entry =  (struct msdos_dir_entry *)sector;

    // first entry is volume name, we start from second entry 
    dir_entry++;
    while (dir_entry->attr & 0x30){  // while not archive entry 

        short unsigned int  year = (dir_entry->cdate >> 9);
        short unsigned int  month = (dir_entry->cdate << 7);
        month = month >> 12;
        short unsigned int day = (dir_entry->cdate << 11);
        day = day >> 11;
        printf("   %d/%d/%d  ", day, month, (year +1980));

        short unsigned int hour = dir_entry->ctime >> 11;
        short unsigned int minuts = dir_entry->ctime << 5;
        minuts = minuts >> (5+5);
        
        if (hour > 12){
            hour -=12;
            printf ("%d:%d PM ",hour, minuts);
        }
        else 
            printf ("%d:%d AM ",hour, minuts);
        if(dir_entry->attr & 0x10)
            printf ("  <DIR>            ");
        else
            printf("  %15d  ",dir_entry->size);
        
                
        //printf("  %s ",dir_entry->name);
        
        
        for (int i=0; i<8; i++)
            if (dir_entry ->name[i] ==0x20)
                dir_entry ->name[i] = 0;
        printf(" %s",dir_entry->name);
        if (dir_entry ->ext[0] !=0x20)
            printf(".%s ",dir_entry->ext);
        
        dir_entry++;
        printf("\n");
    }


/*

    unsigned short int FAT12Entry;

    for (int i=0; i<SECTOR_SIZE/2; i++){
        fread (&FAT12Entry, sizeof(FAT12Entry),1,floppy);
        printf("entry %d: %X \n", i,FAT12Entry);
        if (i & 0x1)
            printf("entry %d: %X \n", i,FAT12Entry>>4);
        else 
            printf("entry %d: %X \n", i,FAT12Entry & 0x0fff);
    }
  */      

    fclose(floppy);
 

}