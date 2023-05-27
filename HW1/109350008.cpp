#include <iostream>

using namespace std;

int coin[10001];
int n;
int cmp = 0;
int check;
int ans;


int partial_sum(int start , int end)
{
    int sum = 0;
    for (int i = start; i <= end; i++) sum += coin[i];

    return sum;
}

int compare(int start, int mid, int end)
{
    int left_sum = partial_sum(start, mid);
    int right_sum = partial_sum(mid + 1, end);

    if (left_sum > right_sum) return 1;
    else if (left_sum < right_sum) return 2;
    else return 3;
    
}

void find_fake(int start, int end)
{
    if (check) // assume fake coin is heavier
    {
        // only 3 remaining
        if (end - start + 1 == 3)
        {
            cmp = coin[start];
            if (coin[start + 1] == coin[start + 2]) ans = start;
            else if (coin[start] == coin[start + 1]) ans = start + 2;
            else ans = start + 1;
        }

        // only 2 remaining
        else if (end - start == 1)
        {
            if (coin[end] != cmp) ans = end;
            else ans = start;
        }

        // even
        else if ((end - start + 1) % 2 == 0)
        {
            int mid = (start + end - 1) / 2;
            if (compare(start, mid, end) == 1) cmp = coin[mid + 1], find_fake(start, mid); // fake on left
            else if (compare(start, mid, end) == 2) cmp = coin[start], find_fake(mid + 1, end); // fake on right
            else if (compare(start, mid, end) == 3) check = 0, find_fake(0, n-1); // fake coin is lighter, run case2
        }

        // odd
        else if ((end - start + 1) % 2 == 1)
        {
            int mid = (start + end) / 2;
            if (partial_sum(start, mid - 1) == partial_sum(mid + 1, end))
            {
                cmp = coin[start];
                if (coin[mid] == cmp) check = 0, find_fake(0, n-1); // fake coin is lighter, run case2
                else ans = mid;
            }
            else if (partial_sum(start, mid - 1) > partial_sum(mid + 1, end)) cmp = coin[mid], find_fake(start, mid - 1); // fake on left
            else if (partial_sum(start, mid - 1) < partial_sum(mid + 1, end)) cmp = coin[mid], find_fake(mid + 1, end); // fake on right
        }
    }

    else // fake coin is lighter
    {
        // only 3 remaining
        if (end - start + 1 == 3)
        {
            cmp = coin[start];
            if (coin[start + 1] == coin[start + 2]) ans = start;
            else if (coin[start] == coin[start + 1]) ans = start + 2;
            else ans = start + 1;
        }

        // only 2 remaining
        else if (end - start == 1)
        {
            if (coin[end] != cmp) ans = end;
            else ans = start;
        }

        // even
        else if ((end - start + 1) % 2 == 0)
        {
            int mid = (start + end - 1) / 2;
            if (compare(start, mid, end) == 2) cmp = coin[mid + 1], find_fake(start, mid); // fake on left
            else if (compare(start, mid, end) == 1) cmp = coin[start], find_fake(mid + 1, end); // fake on right
        }

        // odd
        else if ((end - start + 1) % 2 == 1)
        {
            int mid = (start + end) / 2;
            if (partial_sum(start, mid - 1) == partial_sum(mid + 1, end)) ans = mid;
            else if (partial_sum(start, mid - 1) < partial_sum(mid + 1, end)) cmp = coin[mid], find_fake(start, mid - 1); // left is fake
            else cmp = coin[mid], find_fake(mid + 1, end);
        }
    }
}

int main()
{
    while (cin >> n)
    {
        check = 1;
        ans = 0;
        for (int i = 0; i <= 10000; i++) coin[i] = 0;

        for (int i = 0; i < n; i++) cin >> coin[i];
        find_fake(0, n-1);

        cout << ans << endl;
    }

    return 0;
}

