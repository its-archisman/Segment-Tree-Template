#include <vector>
#include <bits/stdc++.h>
using namespace std;
class SegmentTree
{
    public:
    vector<int> tree;
    SegmentTree(int n)
    {
        tree.resize(4*n + 1);
    }
    void build(vector<int> &a, int ind, int low, int high)
    {
        if(low == high)
        {
            tree[ind] = a[low];
            return;
        }
        int mid = (low + high)/2;
        build(a, 2*ind + 1, low, mid);
        build(a, 2*ind + 2, mid+1, high);

        tree[ind] = min(tree[2*ind + 1], tree[2*ind + 2]);
    }
    int query(int ind, int low, int high, int l, int r)
    {
        if(r<low || l>high) return INT_MAX;

        if(low>=l && high<=r) return tree[ind];

        int mid = (low + high) >> 1;
        int left = query(2*ind + 1, low, mid, l, r);
        int right = query(2*ind + 2, mid+1, high, l, r);

        return min(left, right);
    }
    void update(int ind, int low, int high, int i, int val)
    {
        if(low == high)
        {
            tree[ind] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if(i <= mid)
            update(2*ind + 1, low, mid, i, val);
        else
            update(2*ind, mid+1, high, i, val);
        
        tree[ind] = min(tree[2*ind + 1], tree[2*ind + 2]);
    }
};

signed main()
{
    vector<int> a={1, 4, 2, 4, 6, 4, 9, 11};
    int n = a.size();
    SegmentTree seg(n);
    seg.build(a, 0, 0, n - 1);
    cout << seg.query(0, 0, n-1, 6, 7)<<'\n';
}
