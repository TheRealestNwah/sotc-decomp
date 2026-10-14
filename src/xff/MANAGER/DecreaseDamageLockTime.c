typedef struct {
    int flag;
    char pad4[0x50];
    int state;
    float time;
    float time_prev;
    int count;
    float zero;
    float rate;
} DamageLock;

void DecreaseDamageLockTime(DamageLock *lock, float dt)
{
    lock->zero = 0.0f;
    lock->flag = 0;
    if (lock->state >= 0) {
        lock->time -= dt;
        if (lock->time < lock->zero) {
            lock->time = lock->zero;
            lock->time_prev = lock->zero;
            lock->state = -1;
            lock->count = -1;
            lock->rate = lock->zero;
        }
    }
}
