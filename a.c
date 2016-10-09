the implementation file
#include "a.h"

int ReFromOpen ( struct Node a, struct Node * OPEN )
{
    printf ( "Remove the %c from the OPEN list!\n", OPEN->name );
    while ( OPEN->name != 0 && OPEN->name != a.name )
        OPEN++;
    OPEN->name = 0, OPEN->HN = 0, OPEN->GN = 0, OPEN->FN = 0;
    return 1;
}

// put node n into CLOSED list
int PutIntoClosed ( struct Node a, struct Node * ClOSED)
{
    printf ( "Put the %c into CLOSED list.\n", a.name);
    while ( ClOSED->name != 0 )
        ClOSED++;
    ClOSED->name = a.name, ClOSED->HN = a.HN,
            ClOSED->GN = a.GN, ClOSED->FN = a.FN;
    return 1;
}

// put node into the OPEN list
int PutIntoOpen ( struct Node a, struct Node * OPEN )
{
    printf( "Put %c into OPEN list.\n", a.name);
    while ( OPEN->name != 0 )
        OPEN++;
    OPEN->name = a.name, OPEN->HN = a.HN,
          OPEN->GN = a.GN, OPEN->FN = a.FN;
    return 1;
}

// remove node n form CLOSED list
int ReFromClosed ( struct Node a, struct Node * CLOSED )
{
    printf ( "Remove %c from the CLOSED list!\n", a.name );
    while ( CLOSED->name != 0 && CLOSED->name != a.name )
        CLOSED++;
    CLOSED->name = 0, CLOSED->HN = 0, CLOSED->GN = 0, CLOSED->FN = 0;
    return 1;
}

int CalSucc ( struct Node * a, struct Node * OPEN, struct Node * CLOSED,
              struct Edge * TotEdge, struct Node * NodeArr )
{
    // j refers to the number of edges in Tempedge
    int i, j;
    // store the successors 4 in max
    struct Edge * TempEdge = (struct Edge *)malloc( MaxNodeNum * sizeof(struct Edge));
    if ( TempEdge == NULL )
        printf ( "Error allocating memory!\n");
    memset( TempEdge, 0, MaxNodeNum * sizeof(struct Edge));
    // Temp edge
    struct Edge * Temp = (struct Edge *)malloc(sizeof(struct Edge));
    if ( Temp == NULL)
        printf ( "Error allocating memory!\n");
    // Temp node
    struct Node * TempNode = (struct Node *)malloc(sizeof(struct Node));
    if ( TempNode == NULL )
        printf ( "Error allocating memory!\n");

    // traverse the edge array and find the successors
    for ( i = 0, j = 0; i < EdgeNum; i++ )
    {
        Temp->FirstNode = TotEdge[i].FirstNode, Temp->SecondNode = TotEdge[i].SecondNode,
              Temp->Successor = TotEdge[i].Successor, Temp->Weight = TotEdge[i].Weight;
        // find the successors of node a(n)
        if ( Temp->FirstNode == a->name || Temp->SecondNode == a->name )
        {
            // store the edge
            TempEdge[j].FirstNode = Temp->FirstNode;
            TempEdge[j].SecondNode = Temp->SecondNode;
            TempEdge[j].Weight = Temp->Weight;
            if ( TempEdge[j].FirstNode == a->name )
                TempEdge[j].Successor = TempEdge[j].SecondNode;
            else
                TempEdge[j].Successor = TempEdge[j].FirstNode;
            j++;
        }
    }

    // for each successor renew the pointers
    for ( i = 0; i < MaxNodeNum && TempEdge[i].FirstNode != 0; i++ )
    {
        bool InOpen = 0, InClosed = 0;
        int k, l = 0;
        // traverse the OPEN lists to find the successor node
        for ( k = 0; k < EdgeNum && OPEN[k].name != 0; k++ )
            if( OPEN[k].name == TempEdge[i].Successor )
                InOpen = 1;
        for ( k = 0; k < EdgeNum && CLOSED[k].name != 0; k++ )
            if( CLOSED[k].name == TempEdge[i].Successor )
                InClosed = 1;
        // find the successor's corresponding node
        for ( k = 0; k < NodeNum; k++, l++ )
            if ( NodeArr[k].name == TempEdge[i].Successor )
                break;
        // calculate the value and insert into OPEN list
        TempNode->name = NodeArr[l].name;
        TempNode->HN = NodeArr[l].HN;
        TempNode->GN = TempEdge[i].Weight;
        TempNode->FN = TempNode->HN + TempNode->GN;
        // if the successor does not contain in OPEN and CLOSED list
        if ( !InOpen && !InClosed )
            PutIntoOpen( *TempNode, OPEN );
        // if the successor is in OPEN but not in CLOSED
        else if ( InOpen && !InClosed )
            if ( TempNode->FN < NodeArr[j].FN )
                NodeArr[j].FN = TempNode[j].FN;
            else
                ;
        // if the successor is in CLOSED but not in OPEN
        else if ( !InOpen && InClosed )
        {
            if ( TempNode->FN < NodeArr[j].FN )
                NodeArr[j].FN = TempNode[j].FN;
            else
                ;
            // remove the node from the CLOSED and put it into the OPEN list
            ReFromClosed( NodeArr[j], CLOSED );
            PutIntoOpen( NodeArr[j], OPEN);
        }
    }
    free ( TempEdge ), free ( Temp ), free ( TempNode );
    return 1;
}

int SortNodes ( struct Node * OPEN )
{
    struct Node * location = ( struct Node *)malloc( sizeof( struct Node ));
    if ( location == NULL )
        printf ( "Error allocating memory!\n");
    struct Node * temp = ( struct Node *)malloc( sizeof( struct Node ));
    if ( temp == NULL )
        printf ( "Error allocating memory!\n");
    location = OPEN;
    int i, j, number;
    for ( number = 0; OPEN->name != 0; number++ )
        OPEN++;
    OPEN = location;
    // here use the insertion sort
    for ( i = 0; i < number && OPEN[i+1].name != 0; i++ )
    {
        temp->name = OPEN[i+1].name, temp->FN = OPEN[i+1].FN,
              temp->GN = OPEN[i+1].GN, temp->HN = OPEN[i+1].HN;
        for ( j = i; j > 0 && temp->FN < OPEN[j].FN; j-- )
            OPEN[i+1].name = OPEN[i].name, OPEN[i+1].FN = OPEN[i].FN,
                      OPEN[i+1].GN = OPEN[i].GN, OPEN[i+1].HN = OPEN[i].HN;
        OPEN[j].name = temp->name, OPEN[j].FN = temp->FN,
                OPEN[j].GN = temp->GN, OPEN[j].HN = temp->HN;
    }
    free( temp );
    return 1;
}
