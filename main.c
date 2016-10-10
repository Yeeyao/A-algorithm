#include "a.h"

int main(void)
{
    int i = 0; // the counter of the result path
    struct Edge TotalEdge[EdgeNum] =
    {
        { 3, 'A', 'B', 0}, { 4, 'B', 'C', 0}, { 8, 'C', 'D', 0}, { 2, 'D', 'E', 0},
        { 4, 'A', 'H', 0}, { 2, 'G', 'H', 0}, { 4, 'F', 'G', 0}, { 3, 'D', 'F', 0},
        { 5, 'B', 'H', 0}, { 3, 'C', 'G', 0}, { 8, 'D', 'G', 0}
    };
    struct Node NodeArr[NodeNum] =
    {
        { 'A', 15, 0, 0 }, { 'B', 14, 0, 0 }, { 'C', 10, 0, 0 }, { 'D', 2, 0, 0 }, { 'E', 2, 0, 0 },
        { 'F', 5, 0, 0 },  { 'G', 9, 0, 0 },  { 'H', 11, 0, 0 }
    };
    // store the result path
    char ResPath[NodeNum] = { 0, 0, 0, 0, 0, 0, 0, 0};
    // open list 11 elements
    struct Node * OPEN= (struct Node *)malloc(EdgeNum * sizeof(struct Node));
    if ( OPEN == NULL )
        printf ( "Error allocating memory!\n");
    memset( OPEN, 0, EdgeNum * sizeof(struct Node) );
    // closed list 11 elements
    struct Node * CLOSED = (struct Node *)malloc(EdgeNum * sizeof(struct Node));
    if ( CLOSED == NULL)
        printf ( "Error allocating memory!\n");
    memset( CLOSED, 0, EdgeNum * sizeof(struct Node) );
    // node n
    struct Node * n = (struct Node *)malloc(sizeof(struct Node));
    if ( n == NULL )
        printf ( "Error allocating memory!\n");
// The A* algorithm:
// OPEN CLOSED list both initialized to 0
    OPEN[0].name = NodeArr[0].name, OPEN[0].FN = NodeArr[0].FN,
            OPEN[0].GN = NodeArr[0].GN, OPEN[0].HN = NodeArr[0].HN;   // node A
    // 将初始节点放入OPEN表
    if ( OPEN[0].name == 0 ) return -1; // error
    while ( OPEN[0].name ) // OPEN 表非空
    {
        n->name = OPEN[0].name, n->FN = OPEN[0].FN,
           n->GN = OPEN[0].GN,n->HN = OPEN[0].HN; // pointer assignment
        ResPath[i++] = n->name; // store the nodes
        printf( "\nn = %c, fn = %d, gn = %d, hn = %d\n", n->name, n->FN, n->GN, n->HN );
        if ( n->name == 'E')
        {
            printf( "\n");
            printf ( "The result path:\n");
            for ( i = 0; ResPath[i] != 0; i++ )
                printf ( "%c ", ResPath[i]);
            free( OPEN ),free( CLOSED ),free ( n );
            return 0;
        } // if GOAL(n) EXIT(success) 取得n节点，为目标节点则返回成功
        else                          // REMOVE(n, OPEN), ADD(n,CLOSED)
        {
            // calculate the value
            //n->GN = 0,n->FN = n->GN + n->HN;
            // 对于n的每个子节点
            if ( ReFromOpen( *n, OPEN ) )
                ;
            else
                printf ( "Error!\n");
            if (CalSucc ( n, OPEN, CLOSED, TotalEdge, NodeArr ))
                ;
            else
                printf ("Error!\n");
            if ( PutIntoClosed( *n, CLOSED ) )
                ; 
            else
                printf( "Error!\n");
            if ( SortNodes ( OPEN ) )
                ;
            else
                printf( "Error!\n");
        }
    }
    return -1;
}
