#include <cstdio>
#include <iostream>

using namespace std;

const int N = 10, MOD = 1e6;

struct Matrix {
    long long m[N][N];

    Matrix() {
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                m[i][j] = (i == j);
    }

    Matrix(long long val) {
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                m[i][j] = val;
    }

    Matrix operator*(const Matrix& other) const
    {
        Matrix result(0);
        for(int k = 0; k < N; ++k)
        {
            for(int i = 0; i < N; ++i)
            {
                for(int j = 0; j < N; ++j)
                {
                    result.m[k][i] = (result.m[k][i] + m[k][j] * other.m[j][i]) % MOD;
                }
            }
        }
        return result;
    }

    Matrix& operator*=(const Matrix& other)
    {
        *this = *this * other;
        return *this;
    }
};

Matrix matrix_power(Matrix base, long long p)
{
    Matrix result;
    while(p) {
        if(p & 1) result *= base;
        base *= base;
        p >>= 1;
    }
    return result;
}

int main() {
    long long len, K, L, f[N + 1];

    while (cin >> len >> K >> L)
    {
        K %= MOD;
        L %= MOD;

        Matrix dp(0);
        dp.m[9][0] = L;
        dp.m[9][5] = K;
        for(int i = 0; i < N - 1; ++i)
            dp.m[i][i + 1] = 1;

        f[0] = 1;
        for(int i = 1; i <= N; ++i) {
            f[i] = 0;
            if(i - 5 >= 0)
                f[i] = K * f[i - 5] % MOD;
            if(i - 10 >= 0)
                f[i] = (f[i] + L * f[i - 10]) % MOD;
        }

        if(len == 5)
        {
            printf("%06lld\n", f[5]);
        }
        else if(len == 10) {
            printf("%06lld\n", f[10]);
        }
        else
        {
            Matrix ans = matrix_power(dp, len - 10);
            long long res = 0;
            for(int K = 0; K < N; ++K)
                res = (res + f[K + 1] * ans.m[9][K]) % MOD;
            printf("%06lld\n", res);
        }
    }

    return 0;
}