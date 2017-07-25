/*
 * 贪心算法解决活动排列问题
 * 活动有开始时间和结束时间，要求在从所有活动中选出一组活动，这一组活动可以互不干扰的进行，并且这一组活动中包含的活动数量最多
 *
 */
#include "iostream"
#include "vector"
#include "algorithm"
#include "deque"
#include "unordered_map"

using namespace std;

vector<string> greedy_activity_selector(vector<pair<string,pair<int,int>>> &activities)
{
    //先按活动结束时间排序
    sort(activities.begin(),activities.end(),[](const pair<string,pair<int,int>> &a,const pair<string,pair<int,int>> &b){return a.second.second<b.second.second;});
    vector<string> ret{activities.front().first};
    int end=activities.front().second.second;
    //挑选最先结束的活动加入到解中
    for(int i=1;i<activities.size();++i)
    {
        if(activities[i].second.first>=end)
        {
            end=activities[i].second.second;
            ret.push_back(activities[i].first);
        }
    }
    return ret;
};

int main()
{
    vector<pair<string,pair<int,int>>> activities{
            {"a1",{1,4}},{"a2",{3,5}},{"a3",{0,6}},{"a4",{5,7}},{"a5",{3,9}},{"a6",{5,9}},{"a7",{6,10}},{"a8",{8,11}},{"a9",{8,12}},{"a10",{2,14}},{"a11",{12,16}}
    };
    vector<string> out=greedy_activity_selector(activities);
    for(const auto &str:out)
        cout<<str<<' ';
    cout<<endl;
    return 0;
}
