#include<stdio.h>
#include<stdlib.h>
int main()
{
int q,i,j,a,b,y,z;
unsigned long long int c;
scanf("%d %d %lld",&a,&b,&c);
char x[a][b];
for(i=0;i<a;i++)
{
scanf("%s",x[i]);
}if(c>200)
c=c%200;
for(q=2;q<=c;q++)
{
if(q%2!=0)
{
for(i=0;i<a;i++)
{
for(j=0;j<b;j++)
{
if(x[i][j]=='o')
{
if(x[i][j+1]!='o'&&j+1<b)
x[i][j+1]='.';
if(x[i][j-1]!='o'&&j-1>=0)
x[i][j-1]='.';
if(x[i+1][j]!='o'&&i+1<a)
x[i+1][j]='.';
if(x[i-1][j]!='o'&&i-1>=0)
x[i-1][j]='.';
x[i][j]='.';
}
}
}
}
if(q%2==0)
{
for(i=0;i<a;i++)
{
for(j=0;j<b;j++)
{
if(x[i][j]=='.')
x[i][j]='O';
else if(x[i][j]=='O')
x[i][j]='o';
}
}
}
}
for(i=0;i<a;i++)
{
for(j=0;j<b;j++)
{
if(x[i][j]=='o')
x[i][j]=x[i][j]-32;
printf("%c",x[i][j]);
}
printf("\n");
}
return 0;
}