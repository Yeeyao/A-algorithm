# A-algorithm
This is a homework from my artificial intelligence course.
I follow the steps in this blog:http://www.cnblogs.com/kanego/archive/2011/08/30/2159070.html
Best_First_Search()
{
Open = [起始节点]; Closed = [];
while ( Open表非空 )
{
从Open中取得一个节点X，并从OPEN表中删除。
if (X是目标节点)
{
求得路径PATH；返回路径PATH；
}
for (每一个X的子节点Y)
{
if( Y不在OPEN表和CLOSE表中 )
{
求Y的估价值；并将Y插入OPEN表中；//还没有排序
}
else
if( Y在OPEN表中 )
{
if( Y的估价值小于OPEN表的估价值 )
更新OPEN表中的估价值；
}
else //Y在CLOSE表中
{
if( Y的估价值小于CLOSE表的估价值 )
{
更新CLOSE表中的估价值；
从CLOSE表中移出节点，并放入OPEN表中；
}
}
将X节点插入CLOSE表中；
按照估价值将OPEN表中的节点排序；
}//end for
}//end while
}//end func
