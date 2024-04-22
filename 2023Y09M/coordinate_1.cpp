#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;
const int M = 110;

int dx[N];
int dy[N];
int x[N];
int y[N];
int n, m;

int main()
{
	cin >> n >> m;
	
	for(int i = 0; i < n; i ++)
		cin >> dx[i] >> dy[i];
		
	for(int i = 0; i < m; i ++)
		cin >> x[i] >> y[i];
		
	for(int i = 0; i < m; i ++){
		for(int j = 0; j < n; j ++){
			x[i] += dx[j];
			y[i] += dy[j];
		}
	}
	
	for(int i = 0; i < m; i ++)
		cout << x[i] << ' ' << y[i] << endl;
		
	return 0;
}
