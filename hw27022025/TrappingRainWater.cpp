// нужно посчитать, сколько воды может быть между столбами
//кол-во воды не больше, чем высота столбов, между которыми она накходиться =>
//=> легче всего запомнить высоту слева и справа (min и max)
//высота столба определяется по min высоте из пары

//см. дополнительно rain_water_idea.jpg

#include <iostream>
#include <vector>

using namespace std;

int water(vector<int> height)
{
    int n = height.size(); //подсчитываем количество столбов (включая вырожденные)
    int left{0}, right{n-1}; //для прохода по массиву
    int maxleft{0}, maxright{0}, result{0};

    while(left<=right)
    {
        maxleft = max(maxleft, height[left]); //каждый раз подсчитываем новые максимумы
        maxright = max (maxright, height[right]);

        if (height[left]<=height[right]) //где наибольший столбец?
        {
            result+=min(maxleft, maxright) - height[left]; //сколько воды на каждом шаге?
            left++;
        }
        else{
            result+=min(maxleft, maxright) - height[right];
            right--;
        }
    }
    return result;
}

int main()
{
    vector<int> height{0,1,0,2,1,0,1,3,2,1,2,1};

    cout<<water(height); //output 6

}
