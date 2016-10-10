#include "a.h"

int ReFromOpen ( struct Node a, struct Node * OPEN )
{
    int i = 0, j, k;
    printf ( "Remove %c from the OPEN list!\n", OPEN->name );
    while ( OPEN[i].name != 0 && OPEN[i].name != a.name )
        i++;
    if ( OPEN[i+1].name == 0 )
        {
            OPEN[i].name = 0, OPEN[i].HN = 0, OPEN[i].GN = 0, OPEN[i].FN = 0;
            return 1;
        }
    else
    {
		for ( k = i; OPEN[k].name !=0; k++ ) // the total of nodes in OPEN
			;
		for ( j = k-1; j > i; j-- ) // assignment
			 OPEN[j-1].name = OPEN[j].name, OPEN[j-1].FN = OPEN[j].FN,
                      OPEN[j-1].GN = OPEN[j].GN, OPEN[j-1].HN = OPEN[j].HN;
		OPEN[k-1].name = 0, OPEN[k-1].HN = 0, OPEN[k-1].GN = 0, OPEN[k-1].FN = 0;
    }
    return 1;
}

int ReFromClosed ( struct Node a, struct Node * CLOSED )
{
    int i = 0, j, k;
    printf ( "Remove %c from the CLOSED list!\n", CLOSED->name );
    while ( CLOSED[i].name != 0 && CLOSED[i].name != a.name )
        i++;
    if ( CLOSED[i+1].name == 0 )
        {
            CLOSED[i].name = 0, CLOSED[i].HN = 0, CLOSED[i].GN = 0, CLOSED[i].FN = 0;
            return 1;
        }
    else
    {
		for ( k = i; CLOSED[k].name !=0; k++ ) // the total of nodes in OPEN
			;
		for ( j = k-1; j > i; j-- ) // assignment
			 CLOSED[j-1].name = CLOSED[j].name, CLOSED[j-1].FN = CLOSED[j].FN,
                      CLOSED[j-1].GN = CLOSED[j].GN, CLOSED[j-1].HN = CLOSED[j].HN;
		CLOSED[k-1].name = 0, CLOSED[k-1].HN = 0, CLOSED[k-1].GN = 0, CLOSED[k-1].FN = 0;
    }
    return 1;
}
// put node n into CLOSED list
int PutIntoClosed ( struct Node a, struct Node * CLOSED)
{
    int i = 0;
    printf( "Put %c into CLOSED list.\n", a.name);
    while ( CLOSED[i].name != 0 )
        i++;
    CLOSED[i].name = a.name, CLOSED[i].HN = a.HN,
              CLOSED[i].GN = a.GN, CLOSED[i].FN = a.FN;
    return 1;
}
// put node into the OPEN list
int PutIntoOpen ( struct Node a, struct Node * OPEN )
{
    int i = 0;
    printf( "Put %c into OPEN list.\n", a.name);
    while ( OPEN[i].name != 0 )
        i++;
    OPEN[i].name = a.name, OPEN[i].HN = a.HN,
            OPEN[i].GN = a.GN, OPEN[i].FN = a.FN;
    return 1;
}
// remove node n form CLOSED list

// calculate the fn of successors and update both lists
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
        // read from the edge array
        Temp->FirstNode = TotEdge[i].FirstNode, Temp->SecondNode = TotEdge[i].SecondNode,
              Temp->Successor = TotEdge[i].Successor, Temp->Weight = TotEdge[i].Weight;
        // find the successors of node a(n)
        if ( Temp->FirstNode == a->name || Temp->SecondNode == a->name )
        {
            // store the edge into the tempedge
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
    for ( i = 0; i < MaxNodeNum && TempEdge[i].Weight != 0; i++ )
    {
        bool InOpen = 0, InClosed = 0;
        int k;
        // traverse the OPEN lists to find the successor node
        for ( k = 0; k < NodeNum && OPEN[k].name != 0; k++ )
            if( OPEN[k].name == TempEdge[i].Successor )
                InOpen = 1;
        for ( k = 0; k < NodeNum && CLOSED[k].name != 0; k++ )
            if( CLOSED[k].name == TempEdge[i].Successor )
                InClosed = 1;

        // find the successor's corresponding node
        for ( k = 0; k < NodeNum; k++ )
            if ( NodeArr[k].name == TempEdge[i].Successor )
                break;
        // calculate the value and insert into OPEN list
        TempNode->name = NodeArr[k].name;
        TempNode->HN = NodeArr[k].HN;
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
			// remove the node from the CLOSED and put it into the OPEN list
            if ( TempNode->FN < NodeArr[j].FN )
            {    NodeArr[j].FN = TempNode[j].FN;
				ReFromClosed( NodeArr[j], CLOSED );
				PutIntoOpen( NodeArr[j], OPEN);
			}
            else
                ;
        }
    }
    free ( TempEdge ), free ( Temp ), free ( TempNode );
    return 1;
}

// sort the nodes of OPEN list
int SortNodes ( struct Node * OPEN )
{
    int i, j, number;
    struct Node * location = ( struct Node *)malloc( sizeof( struct Node ));
    if ( location == NULL )
        printf ( "Error allocating memory!\n");
    struct Node * temp = ( struct Node *)malloc( sizeof( struct Node ));
    if ( temp == NULL )
        printf ( "Error allocating memory!\n");
    location = OPEN;
    for ( number = 0; OPEN[number].name != 0; number++ )
        ;
    OPEN = location;
    // here use the insertion sort
    for ( i = 1; i < number && OPEN[i].name != 0; i++ )
    {

        for ( j = i - 1; j >= 0 && OPEN[j].FN > OPEN[j+1].FN; j-- )
        {
            temp->name = OPEN[j+1].name, temp->FN = OPEN[j+1].FN,
                  temp->GN = OPEN[j+1].GN, temp->HN = OPEN[j+1].HN;
            OPEN[j+1].name = OPEN[j].name, OPEN[j+1].FN = OPEN[j].FN,
                      OPEN[j+1].GN = OPEN[j].GN, OPEN[j+1].HN = OPEN[j].HN;
            OPEN[j].name = temp->name, OPEN[j].FN = temp->FN,
                    OPEN[j].GN = temp->GN, OPEN[j].HN = temp->HN;
        }
    }
    free( temp );
    return 1;
}
