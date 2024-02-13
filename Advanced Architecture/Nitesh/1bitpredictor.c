#include<stdio.h>
#include<string.h>
#include <stdlib.h>
int main(){
char * string = 0;
long length;
FILE * f = fopen ("stringTakenNotTaken.txt", "rb");

if (f)
{
  fseek (f, 0, SEEK_END);
  length = ftell (f);
  fseek (f, 0, SEEK_SET);
  string = malloc (length);
  if (string)
  {
    fread (string, 1, length, f);
  }
  fclose (f);
}

    int correct=0; 
    int incorrect=0;
    int FSM=1;
    for (size_t i=0;i<strlen(string);i++){
        if (string[i] =='1' && FSM == 1){
            correct++;
        }
        else if(string[i] =='1' && FSM == 0){
            FSM = 1;
            incorrect++;
        }
        else if(string[i] =='0' && FSM == 0){
            correct++;
        }
        else if(string[i] =='0' && FSM == 1){
            FSM = 0;
            incorrect++;
        }
    }
    double correctrate = (double)correct/(double)strlen(string);
    double incorrectrate = (double)incorrect/(double)strlen(string);
    printf("correct = %d\n", correct);
    printf("incorrect = %d\n", incorrect);
    printf("total = %ld\n", strlen(string));

    printf("correct rate = %f\n", correctrate);
    printf("incorrect rate = %f\n", incorrectrate);
}