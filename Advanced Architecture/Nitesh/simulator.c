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
                        
    if(loadStore == 'L')
    	numLoads++;
    else if(loadStore == 'S')
    	numStores++;
    /*else if(TNnotBranch == 'T')
    	Taken++;  
    else if(TNnotBranch == 'N')
    	notTaken++;  */
   else if((targetAddressTakenBranch != 0 ) && (conditionRegister == '-'))
      uncondCount++;  
   else if(targetAddressTakenBranch != 0 && conditionRegister == 'R')
      condCount++; 
    else if((strcmp(microOperation,"ADD")==0) || (strcmp(microOperation,"ADD_IMM")==0)){
      addCount++;
      aluCount++;
    }
      else if(strcmp(macroOperation,"NOT")==0){
      notCount++;
      aluCount++;
    }
    else if((strcmp(microOperation,"SUB")==0 || (strcmp(microOperation,"SUB_IMM")==0))){
      subCount++;
       aluCount++;
    }
    else if(strcmp(macroOperation,"OR")==0){
      orCount++;
       aluCount++;
    }
    else if(strcmp(macroOperation,"XOR")==0){
      xorCount++;
       aluCount++;
    }
    else if((strcmp(macroOperation,"AND")==0) || strcmp(macroOperation,"AND_IMM")==0){
      andCount++;
       aluCount++;
    }

    else if((strcmp(microOperation,"SHL")==0) || (strcmp(microOperation,"SHL_IMM")==0)) {
      shlCount++;
       aluCount++;
    }  
    else if((strcmp(microOperation,"SHR")==0) || (strcmp(microOperation,"SHR_IMM")==0)) {
      shrCount++;
       aluCount++;
    }    
    else  if((strcmp(microOperation,"FP_ADD")==0) || (strcmp(microOperation,"FP_MULL")==0) || (strcmp(microOperation,"FP_DIV")==0) || (strcmp(microOperation,"FP_DIV")==0)) {
      fpCount++;
    } 
    else{
      otherCount++;
    }              
    if (result == EOF) {
      break;
    }

    if (result != 14) {
      fprintf(stderr, "Error parsing trace at line %" PRIi64 "\n", totalMicroops);
      abort();
    }

    // For each micro-op
    totalMicroops++;

    // For each macro-op:
    if (microOpCount == 1) {
      totalMacroops++;
    }
  }
  float averageCPI = (1*(float)aluCount + 2*(float)numLoads + 3*(float)numStores + 3*(float)uncondCount + 4*(float)condCount +3*(float)fpCount + (float)otherCount) / (float)totalMicroops;
  
  fprintf(outputFile, "Processed %" PRIi64 " trace records.\n", totalMicroops);

    fprintf(outputFile, "Micro-ops: %" PRIi64 "\n", totalMicroops);
  fprintf(outputFile, "Macro-ops: %" PRIi64 "\n", totalMacroops);
  fprintf(outputFile, "Loads %" PRIi64 "\n", numLoads);
  fprintf(outputFile, "Stores %" PRIi64 "\n", numStores);  
 // fprintf(outputFile, "BranchTaken %" PRIi64 "\n", Taken);  
   // fprintf(outputFile, "BranchNotTaken %" PRIi64 "\n", notTaken);  

  fprintf(outputFile, "Unconditional branch: %" PRIi64 "\n", uncondCount);
  fprintf(outputFile, "Conditional branch: %" PRIi64 "\n", condCount);
  fprintf(outputFile, "ADD: %" PRIi64 "\n", addCount);
    fprintf(outputFile, "Subtract: %" PRIi64 "\n", subCount);
    fprintf(outputFile, "OR: %" PRIi64 "\n", orCount);
    fprintf(outputFile, "Xor: %" PRIi64 "\n", xorCount);
    fprintf(outputFile, "AND: %" PRIi64 "\n", andCount);
     fprintf(outputFile, "ShiftLeft: %" PRIi64 "\n", shlCount);
    fprintf(outputFile, "ShiftRight: %" PRIi64 "\n", shrCount);
    fprintf(outputFile, "NOT: %" PRIi64 "\n", notCount);

   

    fprintf(outputFile, "Total Alu count: %" PRIi64 "\n", aluCount);
        fprintf(outputFile, "Floating Point counts: %" PRIi64 "\n", fpCount);
        fprintf(outputFile, "Other Instructions counts: %" PRIi64 "\n", otherCount);


    fprintf(outputFile, "===========Percentage================\n");
    fprintf(outputFile, "Percentage of Load Operations:%f \n" ,(float)numLoads/ (float)totalMicroops*100 );
    fprintf(outputFile, "Percentage of Store Operations:%f \n" ,(float)numStores/ (float)totalMicroops*100 );
    fprintf(outputFile, "Percentage of Unconditional Jumps Operations:%f \n" ,(float)uncondCount/ (float)totalMicroops*100 );
    fprintf(outputFile, "Percentage of Conditional Jumps Operations:%f \n" ,(float)condCount/ (float)totalMicroops*100 );
    fprintf(outputFile, "Percentage of ALU Operations:%f \n" ,(float)aluCount/ (float)totalMicroops*100 );
    fprintf(outputFile, "Percentage of Floating point Operations:%f \n" ,(float)fpCount/ (float)totalMicroops*100 );
    fprintf(outputFile, "Percentage of Other Instruction Operations:%f \n" ,(float)otherCount/ (float)totalMicroops*100 );

    fprintf(outputFile, "===========================\n");

    fprintf(outputFile, "AverageCPI(..Assuming ClockCyles for Other Instruction to be 1.. ): %f \n", averageCPI);


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
