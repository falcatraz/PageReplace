/**
 * This implements the LRU page-replacement algorithm.
 */

#include "../inc/lruList.h"

static int *referenceString;
static int refStringLength;

static FRAME *pageTableTop;
static FRAME *leastRecentlyUsed;
static int pageTableSize;

static int numberOfFramesPerProcess = 0;

// statistics
int nummberOfFaults = 0;

int hitPageNumber;

/*
 * insert pages from a reference string into a page table and measure
 * the page fault rate
 */
int testLRU(int numOfFrames, int *refString, int refStrLen)
{
    // TODO: implement
    numberOfFramesPerProcess = numOfFrames;
    refStringLength = refStrLen;
    referenceString = refString;
    pageTableSize = 0;

    pageTableTop = NULL;
    leastRecentlyUsed = NULL;

    // we will call insert, and in insert we will see if the value is in there or if we need to insert something
    for (int i = 0; i < refStringLength; ++i)
    {
	    // inserting a page into the page table
	    insertLRU(refString[i]);
	    displayLRU();
    }

    return 0;
}

/*
 *	try to insert a page into the page table
 */
void insertLRU(int pageNumber)
{
    // TODO: implement
    // create a new page pointer so that we can insert it
    FRAME* newFrame = malloc(sizeof(FRAME));
    newFrame->pageNumber = pageNumber;
    newFrame->up = NULL;
    newFrame->down = NULL;

    printf("Hi\n");

    // if the size of the table is zero, then it is empty and we can directly insert a page number
    if (pageTableTop == NULL)
    {
	    pageTableTop = newFrame;
	    leastRecentlyUsed = newFrame;
	    pageTableSize++;
    }
    // if we have less than four pages in the frame (page table), then we can insert it to the end
    else
    {
	pageTableTop->up = newFrame;
	newFrame->down = pageTableTop;

	pageTableSize++;

    }
    // else, we search if the pageNumber is in there, if it is not, then we have to insert it.
    // if it is, we simply move it to the front





    free(newFrame);
}

/**
 * Searches for page pageNumber in the page frame list
 * returns NULL if a frame with pageNumber was not found
 * otherwise, returns a reference to the frame with pageNumber
 */
FRAME *searchLRU(int pageNumber)
{
    // TODO: implement

    return NULL;
}

void displayLRU()
{
    // TODO: implement
    for (FRAME* travel = pageTableTop; travel != NULL; travel = travel->down)
    {
	printf("%d : ", travel->pageNumber);
    }
}

void freePageTableLRU()
{
    // TODO: implement
}

