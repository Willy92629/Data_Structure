#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define MAX_M 1000

int t; // ����ռ�
int m; // �J�|���
int n; // �B�ͼ�
int c; // �C���@�M�|���O���J�|���
int d[MAX_N]; // �C��B�ͯ�Y���J�|���

int dp[MAX_M+1][MAX_N+1]; // DP �Ʋ�

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
	fscanf(fp,"%d", &t); // ��J t �մ���
	while (t--) {
   		fscanf(fp,"%d%d%d", &m, &n, &c); // ��J m�Bn�Bc
   		for (i = 1; i <= n; i++) {
			fscanf(fp,"%d", &d[i]); // ��J d[i]
   		}

		for (i = 0; i <= m; i++) { // ��l��
			for (j = 0; j <= n; j++) {
				dp[i][j] = 0;
			}
	}

	for (i = 1; i <= m; i++) { // �M�� i
		for (j = 1; j <= n; j++) { // �M�� j
			dp[i][j] = dp[i][j-1]; // ���N dp[i][j] �]�� dp[i][j-1]
			if (i >= d[j] + c) { // �p�G i �j�󵥩� d[j] + c
				dp[i][j] = dp[i][j] > dp[i-d[j]-c][j-1] + d[j] ? dp[i][j] : dp[i-d[j]-c][j-1] + d[j]; // ��s dp[i][j]
			}
		}
	}

	fprintf(fr,"%d\n", dp[m][n]); // ��X����
	}

return 0;
} 
