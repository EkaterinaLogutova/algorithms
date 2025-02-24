#include <iostream>
#include <vector>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    int m = nums1.size();
    int n = nums2.size();
    
    if(m>n)
        return findMedianSortedArrays(nums2, nums1);
    
    int k = m+n;
    int left = (k+1)/2;
    int low = 0, high = m;

    while(low<= high)
    {
        int mid1 = (low+high)/2;
        int mid2 = left - mid1;

        int l1 = -1e6, l2=-1e6, r1=1e6, r2=1e6;

        if(mid1<m)
            r1=nums1[mid1];
        if(mid2<n)
            r2=nums2[mid2];
        if(mid1-1>=0)
            l1=nums1[mid1-1];
        if(mid2-1>=0)
            l2=nums2[mid2-1];
        
        if (l1<=r2 && l2<=r1)
        {
            if(k%2==1)
                return max(l1,l2);
            else
                return ((max(l1,l2)+min(r1,r2))/2.0);
        }
        else if (l1>l2)
        {
            high = mid1 - 1;
        }
        else
        {
            low = mid1 + 1;
        }
    }
    return 0.0;
}

int main(){
    std::vector<int> nums1 = {1,2};
    std::vector<int> nums2 = {3,4};
    cout<<findMedianSortedArrays(nums1, nums2)<<endl;
    return 0;
}