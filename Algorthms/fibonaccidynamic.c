#include <stdio.h>
#include <stdlib.h>
void printing(int arr[],int length){
    for(int i=0;i<length;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int main() {
    int fibonacci[10];
    int element;
    fibonacci[0] = 1;
    fibonacci[1] = 2;

    for (int i = 2; i < 10; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        printf("%d  ", fibonacci[i]);
    }
     int fibindex = 0;
        int index=0;
        int size=fibonacci[fibindex++];
        char option;
        int *arr=(int *)malloc(size * sizeof(int));

    while (1){
        char option;
        printf("Do you want to insert('i') or delete('d') or exit 'exit': ");
        scanf(" %c",&option);
       
        if(option == 'i'){
            printf("please enter the element the insert: ");
            scanf("%d",&element);
        
        if (index==size){
                    printf("entered here\n");
                    size=fibonacci[fibindex++];
                   // printf("insertion time: size and  fibindex: %d, %d \n", size, fibindex);
                    int *temp=(int *)malloc(size * sizeof(int));
                    for(int i = 0;i<index;i++){
                       temp[i]=arr[i];
                    }
                    free(arr);
                    arr=temp;
                }
         arr[index++]=element;
         printing(arr,fibonacci[fibindex-1]);
        // printf("%d\n" , arr[index-1]);
        }
        else if(option=='d'){
            index=index-1;
            arr[index]=0;
            printf("index: %d \n",index);
            //index=index-1;
            if(index == -1){
                printf("no element to delete..array is empty..thank you\n");
                break;
            }
            //printf("index : %d and fibonacci[fibindex-1]: %d\n", index, fibonacci[fibindex-1]);
            if (index==fibonacci[fibindex-2]){
                
                
                size=fibonacci[fibindex-2];
                fibindex--;
                //printf("size: %d\n",size);
                int *temp=(int *)malloc(size * sizeof(int));
                for(int i = 0;i<index;i++){
                   temp[i]=arr[i];
                }
                free(arr);
                arr=temp;
                
            }
            printing(arr,size);

        }
        else if(option == 'e'){
            printf("thank you for using this program. \n");
            break;
        }
        else{
            printf("invalid option.. \nEnter Again\n");
        }
    }
}