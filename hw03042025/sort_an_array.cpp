#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1{mid - left +1};
    int n2{right - mid};

    vector<int> l(n1), r(n2);

    //copy
    for(int i{0}; i<n1; i++)
        l[i] = arr[left+i];
    for(int j{0}; j<n2; j++)
        r[j] = arr[mid+1+j];

    //merge
    int i{0}, j{0}, k{left};
    while(i<n1 && j<n2)
    {
        if(l[i]<=r[j])
        {
            arr[k]=l[i];
            i++;
        }
        else
        {
            arr[k]=r[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        arr[k]=l[i];
        i++;
        k++;
    }

    while(j<n2)
    {
        arr[k]=r[i];
        j++;
        k++;
    }

}

void mergeSort(vector<int>& arr, int left, int right)
{
    if(left<right)
    {
        int mid{left+(right-left)/2};

        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);

        merge(arr, left, mid, right);
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> nums = {5,1,1,2,0,0};
    int n=nums.size();

    printArray(nums);

    mergeSort(nums, 0, n-1);

    printArray(nums);

    return 0;
}