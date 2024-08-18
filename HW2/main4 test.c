#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define MAX_M 1000

int t; // 測資組數
int m; // 蛋糕單位
int n; // 朋友數
int c; // 每切一刀會浪費的蛋糕單位
int d[MAX_N]; // 每位朋友能吃的蛋糕單位

int dp[MAX_M+1][MAX_N+1]; // DP 數組

int main()
{
	int i,j;

	FILE *fp;
	if ((fp = fopen("input4(10000).txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
    FILE *fr;
	if ((fr = fopen("output4.txt","w"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	fscanf(fp,"%d", &t); // 輸入 t 組測資
	while (t--) {
   		fscanf(fp,"%d%d%d", &m, &n, &c); // 輸入 m、n、c
   		for (i = 1; i <= n; i++) {
			fscanf(fp,"%d", &d[i]); // 輸入 d[i]
   		}

		for (i = 0; i <= m; i++) { // 初始化
			for (j = 0; j <= n; j++) {
				dp[i][j] = 0;
			}
	}

	for (i = 1; i <= m; i++) { // 遍歷 i
		for (j = 1; j <= n; j++) { // 遍歷 j
			dp[i][j] = dp[i][j-1]; // 先將 dp[i][j] 設為 dp[i][j-1]
			if (i >= d[j] + c) { // 如果 i 大於等於 d[j] + c
				dp[i][j] = dp[i][j] > dp[i-d[j]-c][j-1] + d[j] ? dp[i][j] : dp[i-d[j]-c][j-1] + d[j]; // 更新 dp[i][j]
			}
		}
	}

	fprintf(fr,"%d\n", dp[m][n]); // 輸出答案
	}

return 0;
} 
