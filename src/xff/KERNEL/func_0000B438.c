static void func_0000B438(int n, float out[][4], float in[][4])
{
    int i, j, k, r;
    float a[n][n + 1];
    float b[n][n + 1];
    float c[n][n + 1];
    float d[n][n + 1];
    float v[n];
    float e[n][n + 1];
    float f[n][n + 1];
    float g[n][n + 1];
    float h[n][n + 1];
    float w[n];
    float m[n][n + 1];

    for (r = 0; r < n; r++) {
        for (j = 0; j < n; j++) {
            if (r == j) {
                out[r][j] = 1.0f;
            } else {
                out[r][j] = 0.0f;
            }
        }
    }

    for (k = 0; k < n; k++) {
        for (r = 0; r < n; r++) {
            a[r][n] = out[r][k];
        }
        for (r = 0; r < n; r++) {
            for (j = 0; j < n; j++) {
                a[r][j] = in[r][j];
            }
        }
        for (i = 0; i < n - 1; i++) {
            for (j = i; j <= n; j++) {
                b[i][j] = a[i][j] / a[i][i];
            }
            for (j = i; j <= n; j++) {
                a[i][j] = b[i][j];
            }
            for (r = i + 1; r < n; r++) {
                for (j = i; j <= n; j++) {
                    c[r][j] = a[r][i] * b[i][j];
                }
            }
            for (r = i + 1; r < n; r++) {
                for (j = i; j <= n; j++) {
                    a[r][j] = a[r][j] - c[r][j];
                }
            }
        }
        for (r = 0; r < n; r++) {
            for (j = 0; j <= n; j++) {
                d[r][j] = a[r][j];
            }
        }
        for (r = 0; r < n; r++) {
            v[r] = d[r][n];
            for (j = n; j > 0; j--) {
                e[r][j] = d[r][j - 1];
            }
            e[r][0] = v[r];
        }
        for (i = n - 1; i > 0; i--) {
            for (j = i + 1; j >= 0; j--) {
                f[i][j] = e[i][j] / e[i][i + 1];
            }
            for (j = i + 1; j >= 0; j--) {
                e[i][j] = f[i][j];
            }
            for (r = i - 1; r >= 0; r--) {
                for (j = i + 1; j >= 0; j--) {
                    g[r][j] = e[r][i + 1] * f[i][j];
                }
            }
            for (r = i - 1; r >= 0; r--) {
                for (j = i + 1; j >= 0; j--) {
                    e[r][j] = e[r][j] - g[r][j];
                }
            }
        }
        for (r = 0; r < n; r++) {
            for (j = 0; j <= n; j++) {
                h[r][j] = e[r][j];
            }
        }
        for (r = 0; r < n; r++) {
            w[r] = h[r][0];
            for (j = 0; j < n; j++) {
                m[r][j] = h[r][j + 1];
            }
            m[r][n] = w[r];
        }
        for (r = 0; r < n; r++) {
            out[r][k] = m[r][n];
        }
    }
}
