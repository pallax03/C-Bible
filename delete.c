#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

// comando per compilare gcc:
// gcc -std=c99 -o main.exe main.c

void destroyMain(char fname[])
{
    if (remove(fname) == 0) printf("%s:\tdeleted\n", fname); else printf("%s:\tcan't delete", fname);
}

bool folderElements(char fname[])
{
    bool flag = false;
    struct dirent *de;  // Pointer for directory entry
  
    DIR *dr = opendir(fname);
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
        return false;

    //dir opened de got names
    while ((de = readdir(dr)) != NULL)
    {
        if(strcmp(de->d_name,".")==1 && strcmp(de->d_name,"..")==1)
        {
            char tmp[100] = {""};
            strcat(tmp, fname);
            strcat(tmp,"/");
            strcat(tmp,de->d_name);
            if(strcmp(de->d_name,"main.exe")==0) destroyMain(tmp); else folderElements(tmp);
        }
    }
    closedir(dr);
    return true;
}

int main()
{
    return folderElements(".");
}