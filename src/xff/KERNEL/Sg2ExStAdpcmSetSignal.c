typedef int (*StreamSignal)(void *, int, int, int);
extern StreamSignal B_000C5C00;

void Sg2ExStAdpcmSetSignal(StreamSignal signal)
{
    B_000C5C00 = signal;
}