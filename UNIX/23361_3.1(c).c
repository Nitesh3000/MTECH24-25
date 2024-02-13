#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int sfile=open("file.hole",O_RDWR);
    int dfile=open("dfile.txt",O_RDWR | O_CREAT | O_TRUNC, 420);

    //error handling if opening of the files fails
    if (sfile == -1 || dfile == -1){
        perror("error for opening");
        exit(1);
    }
    char rdbuffer[1024];
    ssize_t sfbytesRead = 0;
    int consNullCounter = 0;

    //read the source file till end
    while((sfbytesRead=read(sfile,rdbuffer,sizeof(rdbuffer)))>0){
        for(int i=0; i<sfbytesRead;i++){
            if(rdbuffer[i]=='\0'){
                consNullCounter++; //if null byte is encountered then increment
            }
            else{
                if(consNullCounter>0){  //more than 1 null bytes at once
                    off_t offset = lseek(dfile,consNullCounter,SEEK_CUR); // the file pointer in the dfile is moved by consNullCounter 
                    if(offset == -1){
                        perror("error for lseek");
                        exit(1);
                    }
                    consNullCounter=0; //reset
                }
                //writing the non-null byte to the dfile
                ssize_t wrbytesdest=write(dfile,rdbuffer+i,1);
                if(wrbytesdest == -1){
                    perror("error for write");
                    exit(1);
                }
            }
        }
    }
    close(sfile);
    close(dfile);

    return 0;
}
