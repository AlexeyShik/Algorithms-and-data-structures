import java.math.BigInteger;
import java.util.Scanner;

class SolveQ {
    BigInteger n;
    int m;
    int mod;


    SolveQ(BigInteger n, int m, int mod) {
        this.n = n;
        this.m = m;
        this.mod = mod;
    }

    public boolean correct(int i, int j) {
        boolean is0 = false;
        boolean is1 = false;
        for (int k = 1; k < m; ++k) {
            is0 |= ((j & (1 << k)) == 0) && ((i & (1 << k)) == 0)
                    && ((j & (1 << (k - 1))) == 0) && ((i & (1 << (k - 1))) == 0);
            is1 |= ((j & (1 << k)) == (1 << k)) && ((i & (1 << k)) == (1 << k))
                    && ((j & (1 << (k - 1))) == (1 << (k - 1))) && ((i & (1 << (k - 1))) == (1 << (k - 1)));
        }
        return !(is0 || is1);
    }

    public int[][] mul(int[][] a, int[][] b) {
        int[][] c = new int[a.length][b[0].length];
        for (int i = 0; i < c.length; ++i)
            for (int j = 0; j < c[i].length; ++j)
                c[i][j] = 0;
        for (int i = 0; i < a.length; ++i) {
            for (int j = 0; j < b[0].length; ++j) {
                for (int t = 0; t < a.length; ++t) {
                    c[i][j] = (c[i][j] + a[i][t] * b[t][j]) % mod;
                }
            }
        }
        return c;
    }

    public int[][] binpow(int[][] matrix, BigInteger N) {
        if (N.equals(BigInteger.ONE))
            return matrix;
        BigInteger M = N.or(BigInteger.ONE);
        if (M.equals(N)) { // N = 2k + 1
            return mul(binpow(matrix, N.subtract(BigInteger.ONE)), matrix);
        } else { // N = 2k
            int[][] square = mul(matrix, matrix);
            return binpow(square, N.divide(BigInteger.ONE.add(BigInteger.ONE)));
        }
    }

    public Integer toSolve() {
        int[][] matrix = new int[1 << m][1 << m];
        for (int i = 0; i < (1 << m); ++i) {
            for (int j = 0; j < (1 << m); ++j) {
                matrix[i][j] = 0;
            }
        }
        for (int i = 0; i < (1 << m); ++i) {
            for (int j = 0; j < (1 << m); ++j) {
                if (correct(i, j)) {
                    matrix[i][j] = 1;
                }
            }
        }
        if (!n.equals(BigInteger.ONE)) {
            int[][] finallyMatrix = binpow(matrix, n.subtract(BigInteger.ONE));
            int[][] start = new int[1 << m][1];
            for (int i = 0; i < (1 << m); ++i) {
                start[i][0] = 1;
            }
            int[][] result = mul(finallyMatrix, start);
            int ans = 0;
            for (int i = 0; i < (1 << m); ++i) {
                ans += result[i][0];
                ans %= mod;
            }
            return ans;
        } else {
            int[][] start = new int[1 << m][1];
            for (int i = 0; i < (1 << m); ++i) {
                start[i][0] = 1;
            }
            int ans = 0;
            for (int i = 0; i < (1 << m); ++i) {
                ans += start[i][0];
                ans %= mod;
            }
            return ans;
        }
    }
}

public class Algo_dp_Q {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        BigInteger n = cin.nextBigInteger();
        int m = cin.nextInt();
        int mod = cin.nextInt();
        SolveQ solve = new SolveQ(n, m, mod);
        System.out.println(solve.toSolve());
    }
}
