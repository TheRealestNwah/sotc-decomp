typedef struct {
    int cur;
    int prev;
    int last_changed;
    float time;
} StatusManager;

extern void GAMEUTIL_doit_status_manager(StatusManager *, int, int, float);

void update_type_expression(char *expression, int state, float delta)
{
    GAMEUTIL_doit_status_manager((StatusManager *)(expression + 4), state, 0, delta);
}
