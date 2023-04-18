/**
 * This implements the LRU page-replacement algorithm.
 */

#include "../inc/optArray.h"

int *referenceString;
int refStringLength;

// the page frame list
int *pageTable;
int numOfFramesPerProcess;

int victimIndex;
int hitPageNum;

// statistics
int numOfFaults;

// this index is used to go through the sequence of pages references
int currentPgeReferenceIndex;

int testOPT(int numOfFrames, int *refString, int refStrLen)
{
    // TODO: implement
    // initializing valuess
    numOfFramesPerProcess = numOfFrames;
    referenceString = refString;
    refStringLength = refStrLen;
    numOfFaults = 0;

    // initializing the array
    pageTable = malloc(numOfFramesPerProcess * sizeof(int));

    for (int i = 0; i < numOfFramesPerProcess; ++i)
    {
        pageTable[i] = -1;
    }

    // loop to process the stirng
    for (int i = 0; i < refStringLength; ++i)
    {
        currentPgeReferenceIndex = i;
        insertOPT(referenceString[i]);
        printf("%d -> ", referenceString[i]);
        displayOPT();
    }

    return numOfFaults;
}

/*
 *	try to insert a page into the page table
 */
void insertOPT(int pageNumber)
{
    int searchVal = searchOPT(pageNumber);
    
    pageTable[searchVal] = pageNumber;
}

/*
 *  find either an empty slot, or the page, or a vitim to evict
 */
int searchOPT(int pageNumber)
{
    // TODO: implement
    // linear search
    bool found = false;
    bool foundEmpty = false;
    int countSize = 0;
    int index;

    // look for an empty spot
    for (int i = 0; i < numOfFramesPerProcess; ++i)
    {
        if (pageTable[i] == -1)
        {
            index = i;
            foundEmpty = true;
            numOfFaults++;
            break;
        }
        countSize++;
    }

    // look for the page or a victim to evict
    if (countSize >= numOfFramesPerProcess && !foundEmpty)
    {
        for (int i = 0; i < numOfFramesPerProcess; ++i)
        {
            if (pageTable[i] == pageNumber)
            {
                index = i;
                found = true;
                break;
            }
        }

        // if we did not find it,
        if (!found)
        {
            index = findVictimPageOPT();
            numOfFaults++;
        }
    }

    //return findVictimPageOPT();
    return index;
}

int findVictimPageOPT()
{
    // TODO: implement
    // initializing counter array
    int arrCounter[numOfFramesPerProcess];

    for (int i = 0; i < numOfFramesPerProcess; ++i)
    {
        arrCounter[i] = 0;
    }

    // each counter with its corresponding array will count how far away the value is
    for (int i = 0; i < numOfFramesPerProcess; ++i)
    {
        for (int j = currentPgeReferenceIndex; j < refStringLength; ++j)
        {
            if (pageTable[i] == referenceString[j])
            {
                break;
            }
            arrCounter[i]++;
        }
    }
    
    // finding the max
    int maxIndex = 0;
    int max = arrCounter[0];

    for (int i = 0; i < numOfFramesPerProcess; ++i)
    {
        if (max < arrCounter[i])
        {
            max = arrCounter[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

void displayOPT()
{
    // todo: implement

    for (int i = 0; i < numOfFramesPerProcess; ++i)
    {
        printf("%d ", pageTable[i]);
    }
    printf("\n");
}

void freePageTableOPT()
{
    // TODO: implement
    free(pageTable);
}
