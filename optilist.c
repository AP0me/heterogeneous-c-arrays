#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_TYPE 0
#define CHAR_TYPE 1

struct OptElem {
  int data;
  int dataType;
  struct OptElem** OptArrPointer;
};

struct OptiArrayWithLength {
  int length;
  struct OptElem** arrayOfPointers;
};

struct OptiArrayWithLength* initOptiArray(int arraySize, int defaultVal) {
  struct OptiArrayWithLength* optiArray = malloc(sizeof(struct OptiArrayWithLength));
  optiArray->arrayOfPointers = malloc(sizeof(struct OptElem*) * arraySize);
  optiArray->length = arraySize;

  for (int i = 0; i < arraySize; i++) {
    struct OptElem* charData = malloc(sizeof(struct OptElem));
    charData->data = defaultVal;
    charData->dataType = INT_TYPE; // Assume int data type by default
    charData->OptArrPointer = NULL;
    optiArray->arrayOfPointers[i] = charData;
  }

  return optiArray;
}

void printOptiArray(struct OptiArrayWithLength* optiArray) {
  struct OptElem** arrayOfPointers = optiArray->arrayOfPointers;
  int arraySize = optiArray->length;
  printf("[");
  int k = 0;
  for (int i = 0; i < arraySize; i++) {
    if (arrayOfPointers[k]->OptArrPointer == NULL) {
      switch (arrayOfPointers[k]->dataType) {
        case CHAR_TYPE:
          printf("%c, ", (char)arrayOfPointers[k]->data);
          break;
        case INT_TYPE:
          printf("%d, ", arrayOfPointers[k]->data);
          break;
      }
      k++;
    } else {
      arrayOfPointers = arrayOfPointers[k]->OptArrPointer;
      k = 0;
    }
  }
  printf("]\n");
}

void optiSet(struct OptiArrayWithLength* optiArray, int index, int value, int dataType) {
  struct OptElem* newPointer = malloc(sizeof(struct OptElem));

  if (index < 0) {
    // Negative index, treat it as out-of-bounds, set to last element
    index = optiArray->length - 1;
  } else if (index >= optiArray->length) {
    // Index out of bounds, resize the array
    int newArrayOfPointersSize = index + 1;
    optiArray->arrayOfPointers = realloc(optiArray->arrayOfPointers, sizeof(struct OptElem*) * newArrayOfPointersSize);
    for (int i = optiArray->length; i < newArrayOfPointersSize; i++) {
      struct OptElem* charData = malloc(sizeof(struct OptElem));
      charData->data = 0;
      charData->dataType = dataType;
      charData->OptArrPointer = NULL;
      optiArray->arrayOfPointers[i] = charData;
    }
    optiArray->length = newArrayOfPointersSize;
  }

  if (value >= 0 && value <= 255) {
    newPointer->data = value;
    newPointer->dataType = CHAR_TYPE;
  } else {
    newPointer->data = value;
    newPointer->dataType = INT_TYPE;
  }
  newPointer->OptArrPointer = NULL;

  optiArray->arrayOfPointers[index] = newPointer;
}

void freeOptiArray(struct OptiArrayWithLength* optiArray) {
  int arraySize = optiArray->length;
  for (int i = 0; i < arraySize; i++) {
    free(optiArray->arrayOfPointers[i]);
  }
  free(optiArray->arrayOfPointers);
  free(optiArray);
}

int main() {
  struct OptiArrayWithLength* optiArray = initOptiArray(10, 0);
  printOptiArray(optiArray);
  optiSet(optiArray, 15, 5, INT_TYPE);
  printOptiArray(optiArray);

  freeOptiArray(optiArray);
  return 0;
}
