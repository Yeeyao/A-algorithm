#ifndef A_H_INCLUDED
#define A_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#define NodeNum 8
#define EdgeNum 11
#define MaxNodeNum 4

struct Edge
{
    int Weight;
    char FirstNode;
    char SecondNode;
    char Successor;
};

struct Node
{
    char name;
    int HN;
    int GN;
    int FN;
    //struct Edge LEdge[];
};

// remove node n form OPEN list
int ReFromOpen ( struct Node a, struct Node * OPEN );

// put node n into CLOSED list
int PutIntoClosed ( struct Node a, struct Node * ClOSED);

// put node into the OPEN list
int PutIntoOpen ( struct Node a, struct Node * OPEN );

// remove node n form CLOSED list
int ReFromClosed ( struct Node a, struct Node * CLOSED );

// calculate the fn of successors and update lists
int CalSucc ( struct Node * a, struct Node * OPEN, struct Node * CLOSED,
              struct Edge * TotEdge, struct Node * NodeArr );

// sort the nodes in OPEN list
int SortNodes ( struct Node * OPEN );


#endif // A_H_INCLUDED
