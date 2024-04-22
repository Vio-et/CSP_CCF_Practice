// Orladno 2024-3-30
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 100010;
double op[N][2];
double k[N]; 
double d[N];
int n, m;

int main()
{
	cin >> n >> m;
	
	k[0] = 1;
	
	for(int i = 1; i <= n; i ++){
		scanf("%lf %lf", &op[i][0], &op[i][1]);
		if(op[i][0] == 1){
			k[i] = k[i - 1] * op[i][1];
			d[i] = d[i - 1];
		}
		else if(op[i][0] == 2){
			k[i] = k[i - 1];
			d[i] = d[i - 1] + op[i][1];
		}
	}
	
	int i = 0, j = 0;
	double x = 0, y = 0;

	for(int c = 1; c <= m; c ++){
		scanf("%d %d %lf %lf", &i, &j, &x, &y);
		
		double times = k[j] / k[i - 1];
		double degree = d[j] - d[i - 1];
		
		x *= times;
		y *= times;
		
		double tx = x, ty = y;
		
		x = tx * cos(degree) - ty * sin(degree);
		y = tx * sin(degree) + ty * cos(degree);
		
		printf("%.3lf %.3lf\n", x, y);
	}

	return 0;
}
