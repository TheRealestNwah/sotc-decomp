typedef struct {
    int cur;
    int prev;
    int last_changed;
    float time;
} StatusManager;

void GAMEUTIL_doit_status_manager(StatusManager *s, int state, int reset, float dt)
{
    int prev;

    if (reset == 1) {
        s->time = 0.0f;
        s->last_changed = state;
        s->prev = state;
        s->cur = state;
        return;
    }
    prev = s->cur;
    if (prev == state) {
        s->time += dt;
    } else {
        s->time = 0.0f;
        s->last_changed = prev;
    }
    s->prev = prev;
    s->cur = state;
}
