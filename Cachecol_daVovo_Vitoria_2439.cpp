#include <iostream>

using namespace std;

const long long MOD = 1e9 + 7;
const int K = 2;

struct Matrix {
    long long mat[K][K];

    Matrix()
    {
        for (int i = 0; i < K; i++)
        {
            for (int j = 0; j < K; j++)
                mat[i][j] = 0;
        }
    }

    Matrix operator*(const Matrix& other) const
    {
        Matrix result;
        for (int i = 0; i < K; i++)
        {
            for (int j = 0; j < K; j++)
            {
                for (int k = 0; k < K; k++)
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
            }
        }
        return result;
    }
};

Matrix matrix_power(Matrix base, long long exp)
{
    Matrix result;

    for (int i = 0; i < K; i++)
        result.mat[i][i] = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = result * base;
        base = base * base;
        exp /= 2;
    }
    return result;
}

int main() {
    long long n;
    cin >> n;

    if (n == 1)
    {
        cout << 12 << endl;
        return 0;
    }

    if (n == 2)
    {
        cout << 54 << endl;
        return 0;
    }

    Matrix base;
    base.mat[0][0] = 0;
    base.mat[0][1] = 1;
    base.mat[1][0] = (MOD - 2) % MOD;
    base.mat[1][1] = 5;

    Matrix t = matrix_power(base, n - 1);

    long long f1 = 12;
    long long f2 = 54;

    // f(n) = t[0][0] * f1 + t[0][1] * f2
    long long result = (t.mat[0][0] * f1 + t.mat[0][1] * f2) % MOD;
    cout << result << endl;

    return 0;
}
