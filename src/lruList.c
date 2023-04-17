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

int hitPageNumber = 0;

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
        printf("%d -> ", refString[i]);
        displayLRU();
	    insertLRU(refString[i]);
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

    // if the size of the table is zero, then it is empty and we can directly insert a page number
    // this initial value will be the least recently used
    if (pageTableTop == NULL)
    {
        newFrame->up = NULL;
        newFrame->down = NULL;
        pageTableTop = newFrame;
        leastRecentlyUsed = newFrame;

    }
    // else, insert until we reach the number of frames per process, that way we cannot exceed it 
    else if (pageTableSize < numberOfFramesPerProcess)
    {
        newFrame->up = NULL;
        newFrame->down = pageTableTop;
        pageTableTop->up = newFrame;
        pageTableTop = newFrame;

    }
    // else, check for page fault or miss
    // if a hit, move the value to the front
    // if a miss, remove the oldest value and push the 'new' value in
    else
    {
        FRAME *hitOrMiss = searchLRU(pageNumber);

        // if miss
        if (hitOrMiss == NULL)
        {
            // insert
            newFrame->up = NULL;
            newFrame->down = pageTableTop;
            pageTableTop->up = newFrame;
            pageTableTop = newFrame;

            //remove
            leastRecentlyUsed = leastRecentlyUsed->up;
            leastRecentlyUsed->down = NULL;

            printf("miss!\n");
        }
        // if a hit
        else
        {
            // if the value is at the front, we do not have to do anything
            if (pageTableTop->pageNumber == hitOrMiss->pageNumber)
            {   
                hitPageNumber++;
                printf("Hit front!\n");
            }
            // else if the least recently used value is where the hit happens
            // move it to the front
            // i will simply insert it to the front and then remove the last node
            else if (leastRecentlyUsed->pageNumber == hitOrMiss->pageNumber)
            {
                // insert
                newFrame->up = NULL;
                newFrame->down = pageTableTop;
                pageTableTop->up = newFrame;
                pageTableTop = newFrame;

                //remove
                leastRecentlyUsed = leastRecentlyUsed->up;
                leastRecentlyUsed->down = NULL;
                printf("Hit LRU!\n");
            }
            // if in between, 'move it' to the front
            // I will just connect the previous and next nodes to each other and then disconnect the 'free floating' node
            else
            {
                FRAME *tempUpper = hitOrMiss->up;
                FRAME *tempLower = hitOrMiss->down;
                tempUpper->down = hitOrMiss->down;
                tempLower->up = hitOrMiss->up;
                hitOrMiss = NULL;

                // insert to the front
                newFrame->up = NULL;
                newFrame->down = pageTableTop;
                pageTableTop->up = newFrame;
                pageTableTop = newFrame;
                
            }
        }
    }
    pageTableSize++;
}

/**
 * Searches for page pageNumber in the page frame list
 * returns NULL if a frame with pageNumber was not found
 * otherwise, returns a reference to the frame with pageNumber
 */
FRAME *searchLRU(int pageNumber)
{
    // TODO: implement
    FRAME *retFrame = NULL;

    // searching the list to see if the page number exists
    // if it does not, it will simply leave the return value at NULL
    FRAME *travel = pageTableTop;
    while (travel != NULL)
    {
        if (travel->pageNumber == pageNumber)
        {
            retFrame = travel;
            break;
        }
        
        travel = travel->down;
    }

    return retFrame;
}

void displayLRU()
{
    // TODO: implement
    FRAME *travel = pageTableTop;

    while (travel != NULL)
    {
        printf("%d ", travel->pageNumber);
        
        travel = travel->down;
    }
    printf("\n");
}

void freePageTableLRU()
{
    // TODO: implement
}