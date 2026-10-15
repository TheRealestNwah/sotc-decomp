extern int D_0017A084; void gameflowSetPauseEnable(int enable) { int *count = &D_0017A084; int v; if (enable == 0) { v = *count + 1; } else { v = *count - 1; } *count = v; }
