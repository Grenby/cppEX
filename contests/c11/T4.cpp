#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    int n = 0, from = 0,to = 0;
    cin >> n >> from>>to;

    vector<vector<int>> d(n);

    for (int i =0; i < n; i++)
        d[i].resize(n);

    for (int i = 0; i < n; ++i) {
        for(int j =0;j<n;j++){
            int cost = 0;
            cin >> cost;
            d[i][j] = i==j ? 0 : cost;
        }
    }

    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j){
                int k1 = d[i][k]==-1 || d[k][j]==-1 ? d[i][j] : d[i][k] + d[k][j];
                d[i][j] = min (d[i][j] == -1? k1 : d[i][j], k1);
            }
    cout<<d[from-1][to-1];

    return 0;
}
