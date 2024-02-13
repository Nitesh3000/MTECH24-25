import matplotlib as plt
import numpy as np
instruction_types = ['Loads', 'Stores', 'UnconditionalBranch', 'Conditional_Branch', 'ALU']
LoadPercent = 232/10
StoresPercent = 108/10
CondPercent = 157/10
UncondPercent = 36/10
AluPercent = 203/10
percentage = [LoadPercent, StoresPercent, CondPercent, UncondPercent, AluPercent]
scaling_factor = 100 / sum(percentage)
scaled_percentage = [p * scaling_factor for p in percentage]
plt.bar(instruction_types, scaled_percentage)
plt.xlabel('Instruction Types')
plt.ylabel('Percentage')
plt.title('Percentage of Each Instruction Type')

plt.show()