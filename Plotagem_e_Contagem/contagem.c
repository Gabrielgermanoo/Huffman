#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void bubble_sort(int *v, int size, int *count)
{
  int i, j;
  int flag = 0;
  for (j = size - 1; j >= 0; j--){
    for (i = 0; i < j; i++){
        ++*count;
        if (v[i] > v[i + 1]){
          flag = 1;
          swap(&v[i], &v[i + 1]);  
      }
    }
    if(!flag)
      return;
    
  }
}

void quick_sort(int *a, int left, int right, int *count) {
    int i, j, x, y;
    i = left;
    j = right;
    x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
            ++*count;
        }
        while(a[j] > x && j > left) {
            j--;
            ++*count;
        }
        ++*count;
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
    
    if(j > left) {
        quick_sort(a, left, j, count);
    }
    if(i < right) {
        quick_sort(a, i, right, count);
    }
}

int main(){
    
    int i, j, x = 0, y = 0;
  
    FILE *out = fopen("contagem.txt", "w+");
    for(j = 1; j < 15000; j++)
    {
      int a[j]; int b[j];
      for(i=0; i < j; i++)
      {
        a[i] = b[i] = rand();
      }
      quick_sort(a, 0, i, &x);
      bubble_sort(b, i, &y);
      fprintf(out, "%d\t\t\t\t%d\t\t\t\t%d\n", x, y, i);
      x = y = 0;
    }
    fclose(out);
    return 0;
}