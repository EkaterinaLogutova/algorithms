#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Record
{
    string name;
    vector<int> params;
};

bool compare(const Record& a, const Record& b, const vector<int>& priority)
{
    for(int field: priority)
    {
        int ind = field - 1;

        if(a.params[ind] != b.params[ind])
        {
            return a.params[ind] > b.params[ind];
        }
    }
    return false;
}

int main()
{
    int n, k;
    cin>>n>>k;
    vector<int> priority(k);
    vector<Record> records(n);
    for(int i{0}; i<k; ++i)
    {
        cin>> priority[i];
    }
    for(int i{0}; i<n; ++i)
    {
        cin>> records[i].name;
        records[i].params.resize(k);
        for(int j=0; j<k; ++j)
        {
            cin>> records[i].params[j];
        }
    }

    sort(records.begin(), records.end(),[&priority](const Record& a,
         const Record& b){
            return compare(a, b, priority);
         });
    
    for(auto& record: records)
    {
        cout<<record.name<<endl;
    }

    return 0;
}