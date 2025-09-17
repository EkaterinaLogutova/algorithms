#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
};

bool compare(const Point &a, const Point &b)
{
    if(a.x==b.x)
    {
        return a.y < b.y;
    }
    return a.x < b.x;
}

int main()
{
    int n;
    cin>>n;

    vector<Point> points(n);

    for(int i{0}; i<n; ++i)
    {
        cin>> points[i].x >> points[i].y;
    }
    sort(points.begin(), points.end(), compare);

    cout<<"\n";
    
    for (auto point : points) {
        cout << point.x << " " << point.y << endl;
    }

    return 0;
}