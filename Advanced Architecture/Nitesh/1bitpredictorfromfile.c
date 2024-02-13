#define __STDC_FORMAT_MACROS
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include<string.h>
void simulate(FILE* inputFile, FILE* outputFile)
{
    FILE *fptr,*local;
    fptr = fopen("stringTakenNotTaken.txt", "w");
    fptr = fopen("LocalPredictor.txt", "w");

    //fflush(fptr);
  // See the documentation to understand what these variables mean.
  int32_t microOpCount;
  uint64_t instructionAddress;
  int32_t sourceRegister1;
  int32_t sourceRegister2;
  int32_t destinationRegister;
  char conditionRegister;
  char TNnotBranch;
  char loadStore;
  int64_t immediate;
  uint64_t addressForMemoryOp;
  uint64_t fallthroughPC;
  uint64_t targetAddressTakenBranch;
  char macroOperation[12];
  char microOperation[23];

  int64_t totalMicroops = 0;
  int64_t totalMacroops = 0;
  int64_t numLoads = 0;
  int64_t numStores = 0;
  int64_t Taken = 0;
  int64_t notTaken = 0;
  int64_t uncondCount = 0;
  int64_t condCount = 0;
  int64_t addCount = 0;
  int64_t subCount = 0;
  int64_t orCount = 0;
  int64_t xorCount = 0;
  int64_t andCount = 0;
  int64_t shlCount = 0;
  int64_t shrCount = 0;
  int64_t notCount = 0;
  int64_t fpCount = 0;
  int64_t otherCount = 0;

  int64_t aluCount = 0;



  
  fprintf(outputFile, "Processing trace...\n");
  
  while (true) {
    int result = fscanf(inputFile, 
                        "%" SCNi32
                        "%" SCNx64 
                        "%" SCNi32
                        "%" SCNi32
                        "%" SCNi32
                        " %c"
                        " %c"
                        " %c"
                        "%" SCNi64
                        "%" SCNx64
                        "%" SCNx64
                        "%" SCNx64
                        "%11s"
                        "%22s",
                        &microOpCount,
                        &instructionAddress,
                        &sourceRegister1,
                        &sourceRegister2,
                        &destinationRegister,
                        &conditionRegister,
                        &TNnotBranch,
                        &loadStore,
                        &immediate,
                        &addressForMemoryOp,
                        &fallthroughPC,
                        &targetAddressTakenBranch,
                        macroOperation,
                        microOperation);
                        
    /*if(loadStore == 'L')
    	numLoads++;
    else if(loadStore == 'S')
    	numStores++;*/
    if(targetAddressTakenBranch != 0 && conditionRegister == 'R'){
      
        if(TNnotBranch == 'T'){
    	    Taken++;
            fprintf(outputFile,"1 ");
           
            fputs("1", fptr);
            fputs("%"PRIu64, instructionAddress );
        }
    
        else if(TNnotBranch == 'N'){
    	    notTaken++;
            fprintf(outputFile,"0");
            fputs("0 ", fptr);
            fputs("%"PRIu64, instructionAddress );
       }
    }
/*
           if((targetAddressTakenBranch != 0 ) && (conditionRegister == '-'))
      uncondCount++;  
   else if(targetAddressTakenBranch != 0 && conditionRegister == 'R')
      condCount++;
    */
        if (result == EOF) {
      break;
    }

    if (result != 14) {
      fprintf(stderr, "Error parsing trace at line %" PRIi64 "\n", totalMicroops);
      abort();
    }

  }
  
  fprintf(outputFile, "\nBranchTaken %" PRIi64 "\n", Taken);  
   fprintf(outputFile, "\nBranchNotTaken %" PRIi64 "\n", notTaken);
    /*fprintf(outputFile, "Unconditional branch: %" PRIi64 "\n", uncondCount);
  fprintf(outputFile, "Conditional branch: %" PRIi64 "\n", condCount);*/
    fclose(fptr);

  }
int main(int argc, char *argv[]) 
{
    
  FILE *inputFile = stdin;
  FILE *outputFile = stdout;
  
  if (argc >= 2) {
    inputFile = fopen(argv[1], "r");
    assert(inputFile != NULL);
  }
  if (argc >= 3) {
    outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);
  }
  
  simulate(inputFile, outputFile);

  return 0;
}