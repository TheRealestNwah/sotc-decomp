extern char D_00137638[];

typedef struct {
    int a;
    int b;
    int c;
    int d;
    int e;
    void *data;
} WindEffectData;

void constructor_wind_effect_data(WindEffectData *w)
{
    w->a = 0;
    w->b = 0;
    w->c = 0;
    w->d = 0;
    w->e = 0;
    w->data = D_00137638;
}
