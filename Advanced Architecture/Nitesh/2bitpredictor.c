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
int incorrect = 0;
int statechange=0;
int FSM[4]={11,10,01,00}; 
int currentState = FSM[0];
for(size_t i=0;i<strlen(string);i++){
    if (string[i]=='1' && currentState == FSM[0]){
        correct++;
    }
    else if(string[i]=='0' && currentState == FSM[0]){
        currentState=FSM[1];
        incorrect++;
    }
     else if(string[i]=='1' && currentState == FSM[1]){
        currentState=FSM[0];
        correct++;
    }
     else if(string[i]=='0' && currentState == FSM[1]){
        currentState=FSM[2];
        statechange++;
        incorrect++;

    }
     else if(string[i]=='1' && currentState == FSM[2]){
        currentState=FSM[1];
        incorrect++;
    }
     else if(string[i]=='0' && currentState == FSM[2]){
        currentState=FSM[3];
        correct++;
    }
     else if(string[i]=='1' && currentState == FSM[3]){
        currentState=FSM[2];
        statechange++;
        incorrect++;
    }
     else if(string[i]=='0' && currentState == FSM[3]){
       // currentState=FSM[2];
        correct++;
    }
}
double correctrate = (double)correct/(double)strlen(string);
    double incorrectrate = (double)incorrect/(double)strlen(string);
    printf("correct = %d\n", correct);
    printf("incorrect = %d\n", incorrect);
    printf("total = %ld\n", strlen(string));        

    printf("correct rate = %f\n", correctrate);
    printf("incorrect rate = %f\n", incorrectrate);
    printf("state Changes = %d\n",statechange);
}