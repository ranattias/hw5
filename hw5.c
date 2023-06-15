#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msdos_fs.h"
#include "dir.h"
#include "cp.h"



int main (int argc, char *argv[]){
    char *img_file_name;

    printf ("Operation Systems course homework #5 \n");

    img_file_name =  argv[1];

    if (strcmp(argv[2],"dir") == 0)
        img_dir(img_file_name);
    
    if (strcmp(argv[2],"cp") == 0)
        extract_file(argv[3], argv[4]);
    
    
    return 0;
}
