#include <iostream>
#include <vector>
#include <cassert>
#include <omp.h>
#include "args.h"
#include "field.h"
#include "search.h"

int gauss(std::vector<std::vector<element>> &a, std::vector<element> &b, std::vector<element> &ans)
{
    int n = (int) a.size();
    int m = (int) a[0].size();
    for (int i = 0; i < n; i++)
        a[i].push_back(b[i]);

    std::vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {

        int sel = -1;
        for (int i = row; i < n; i++)
            if (a[i][col] != 0) {
                sel = i;
                break;
            }

        if (sel == -1)
            continue;

        for (int i = col; i <= m; i++)
            std::swap(a[sel][i], a[row][i]);

        where[col] = row;

        for (int i = 0; i < n; i++)
            if (i != row) {
                element c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign(m, 0);
    for (int i = 0; i < m; i++)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i = 0; i < n; i++) {
        element sum = 0;
        for (int j = 0; j < m; j++)
            sum += ans[j] * a[i][j];
        if (sum != a[i][m]) {
            return 0;
        }
    }

    for (int i = 0; i < m; i++)
        if (where[i] == -1) {
            return 2;
        }

    return 1;
}

template<typename T>
std::vector<std::vector<T>> construct_hankel(std::vector<T> &a)
{
    assert(a.size() % 2 == 1);
    int n = (a.size() + 1) / 2;
    std::vector<std::vector<T>> H(n, std::vector<T>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            H[i][j] = a[i + j];
    return H;
}

std::vector<element> mu;
int cnt[200] = {0};
int M[200] = {0};

bool search(int dep)
{
    cnt[dep]++;

    if (dep == 0) {
        if (args.print_sequence) {
            for (const element &x : mu)
                std::cout << x << ' ';
            std::cout << std::endl;
        }
        return true;
    }
    
    if (args.only_start_at_one && mu.size() == 0) {
        mu.push_back(1);
        if (search(dep - 1))
            if (args.stop_after_first)
                return true;
        mu.pop_back();
        return false;
    }


    std::vector<bool> possible(MOD, true);

    int m = mu.size() / 2;
    #pragma omp parallel for num_threads(12)
    for (int n = 1; n <= m; n++) {
        int r = mu.size() - 2 * n;
        std::vector<element> a(mu.begin() + r, mu.begin() + r + 2 * n - 1);
        std::vector<std::vector<element>> H = construct_hankel(a);
        std::vector<element> y(mu.begin()+r+n, mu.begin()+r+2*n);
        std::vector<element> x;
        gauss(H, y, x);
        element bad = 0;
        for (int i = 0; i < n; i++)
            bad += x[i] * mu[r+n+i];

        #pragma omp critical
        {
            possible[bad.value] = false;
        }
    }

    int nval = 0;
    for (int i = 1; i < MOD; i++) 
        if (possible[i]) {
            nval++;
            mu.push_back(i);
            if (search(dep - 1))
                if (args.stop_after_first)
                    return true;
            mu.pop_back();
        }

    M[dep] = std::max(M[dep], nval);

    return false;
}
