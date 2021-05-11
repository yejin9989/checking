/*
* [2018110981][한원석] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define MAX 512

int bound;
int W = 0, n = 0, maxprofit = 0, answeight = 0, ansbound = 0;
int w[MAX] = { 0, }, p[MAX] = { 0, };
bool include[MAX] = { 0, }, bestset[MAX] = { 0, };

void exchangesort(int n) {
   for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
         if (p[i] / w[i] < p[j] / w[j]) {
            int tmp = 0;
            tmp = w[i];
            w[i] = w[j];
            w[j] = tmp;
            tmp = p[i];
            p[i] = p[j];
            p[j] = tmp;
         }
      }
   }
}


bool promising(int i, int profit, int weight) {
   int j, k, totweight;
   bound = 0;
   if (weight >= W) return false;
   else {
      j = i + 1;
      bound = profit;
      totweight = weight;
      while (j <= n && totweight + w[j] <= W) {
         totweight += w[j];
         bound += p[j];
         j++;
      }
      k = j;
      if (k <= n)
         bound += (W - totweight)*(p[k] / w[k]);

      return bound > maxprofit;
   }
}

void knapsack(int i, int profit, int weight) {
   if (weight <= W && profit > maxprofit) {
      maxprofit = profit;
      answeight = weight;
      ansbound = bound;
   }
   if (promising(i, profit, weight)) {
      include[i + 1] = true;
      knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
      include[i + 1] = false;
      knapsack(i + 1, profit, weight);
   }
}

int main()
{
   int T = 0;
   scanf("%d", &n);

   for (int i = 1; i <= n; i++) {
      scanf("%d", &w[i]);
   }
   for (int j = 1; j <= n; j++) {
      scanf("%d", &p[j]);
   }
   exchangesort(n);

   scanf("%d", &T);
   for (int a = 0; a < T; a++) {
      int maxi = 0;
      scanf("%d", &W);
      maxprofit = 0;
      ansbound = 0, answeight = 0;
      knapsack(0, 0, 0);
      printf("%d ", maxprofit);
      printf("%d %d\n",answeight, ansbound);
   }
    return 0;
}