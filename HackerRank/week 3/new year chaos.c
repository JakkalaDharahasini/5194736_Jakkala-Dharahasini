#include <stdio.h>
#include <malloc.h>
typedef struct {
int  v;
char s;
} CH;int sort(CH *a, int n)
{
int i, j, s;
int c = 0;
CH t;for (i = 0; i < n; i++) {
s = 0;
for (j = 0; j < (n - 1); j++) {
if (a[j + 1].v < a[j].v) {
if (a[j].s >= 2)
return -1;a[j].s++;
t = a[j];
a[j] = a[j + 1];
a[j + 1] = t;
c++;
s = 1;
}
}
if (s == 0)
break;
}return c;
}int main()
{
int t, n, i, c;
CH *ch;scanf("%d", &t);
while (t--) {
scanf("%d", &n);
ch = (CH *)calloc(n, sizeof(CH));
for (i = 0; i < n; ++i)
scanf("%d", &ch[i].v);c = sort(ch, n);
if (c >= 0)
printf("%d\n", c);
else
printf("Too chaotic\n");
free(ch);
}return 0;
}