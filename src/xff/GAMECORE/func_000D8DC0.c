typedef struct {
    float x;
    float y;
} Key;

extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);

static float func_000D8DC0(Key *tab, int n, float *s)
{
    int i;

    for (i = 0; i < n - 1; i++) {
        if (tab[i].x >= s[1])
            break;
    }
    if (i <= 0)
        return tab[0].y;
    return GAMEUTIL_get_interp_value(tab[i].y, tab[i - 1].y,
                                     GAMEUTIL_get_dist_ratio(s[1], tab[i - 1].x, tab[i].x));
}
