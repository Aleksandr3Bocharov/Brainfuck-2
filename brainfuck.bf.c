#include <memory.h>
#include <stdio.h>

int main(void)
{
     int i = 0;
     unsigned char arr[30000];
     memset(arr, 0, sizeof(arr));
     arr[i] = getchar();
     i++;
     arr[i] = getchar();
     i++;
     i--;
     putchar(arr[i]);
     i--;
     putchar(arr[i]);
     return 0;
}
