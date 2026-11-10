/* ~88 diffs, 4 words longer (158 vs 154). Callback variant of FlushModifiedManager (src/xff/MANAGER/modified_manager.c): same width switch (1/2/4-byte values) clearing flags[value], but when both callback and arg are set it also calls callback(arg, value) per entry; bad widths go to the iosJumpRecoverPoint("modman:\tclear error:%d") path. The separate counter `k` for the plain loops matches the original register use (it keeps pointer/counter in $a2/$a1 there and $s0/$s1 in the callback loops). The Original has a single shared recover call site and 4 fewer words of branch glue; sharing the error path with goto produced the same code, and splitting every case into return-after-loop made it shorter (144). */
typedef struct {
    int used;
    int current;
    unsigned char * flags;
    int width;
    void * data;
} ModifiedManager;

extern void iosJumpRecoverPoint(const char *, ...);

#ifdef NONMATCHING
void FlushModifiedManagerCB(ModifiedManager *manager, void *arg, void (*callback)(void *, int))
{
    int count = manager->used;
    int index;
    int k;

    if (count != 0) {
        if (callback == 0 || arg == 0) {
            switch (manager->width) {
            case 1: {
                unsigned char *values = manager->data;
                for (k = 0; k < count; k++)
                    manager->flags[*values++] = 0;
                break;
            }
            case 2: {
                unsigned short *values = manager->data;
                for (k = 0; k < count; k++)
                    manager->flags[*values++] = 0;
                break;
            }
            case 4: {
                int *values = manager->data;
                for (k = 0; k < count; k++)
                    manager->flags[*values++] = 0;
                break;
            }
            default:
                iosJumpRecoverPoint("modman:\tclear error:%d\n", manager->width);
                break;
            }
        } else {
            switch (manager->width) {
            case 1: {
                unsigned char *values = manager->data;
                for (index = 0; index < count; index++) {
                    manager->flags[*values] = 0;
                    callback(arg, *values++);
                }
                break;
            }
            case 2: {
                unsigned short *values = manager->data;
                for (index = 0; index < count; index++) {
                    manager->flags[*values] = 0;
                    callback(arg, *values++);
                }
                break;
            }
            case 4: {
                int *values = manager->data;
                for (index = 0; index < count; index++) {
                    manager->flags[*values] = 0;
                    callback(arg, *values++);
                }
                break;
            }
            default:
                iosJumpRecoverPoint("modman:\tclear error:%d\n", manager->width);
                break;
            }
        }
        manager->used = 0;
    }
}
#endif
