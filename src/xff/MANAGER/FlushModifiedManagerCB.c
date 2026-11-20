/* Callback variant of FlushModifiedManager (src/xff/MANAGER/modified_manager.c): same width switch (1/2/4-byte values) clearing flags[value], but when both callback and arg are set it also calls callback(arg, value) per entry. Bad widths share one iosJumpRecoverPoint("modman:\tclear error:%d") call site, reached by goto from the first switch. */
typedef struct {
    int used;
    int current;
    unsigned char * flags;
    int width;
    void * data;
} ModifiedManager;

extern void iosJumpRecoverPoint(const char *, ...);

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
                goto err;
            }
        } else {
            switch (manager->width) {
            case 1: {
                unsigned char *values = manager->data;
                for (index = 0; index < count; index++) {
                    manager->flags[*values] = 0;
                    callback(arg, *values);
                    values++;
                }
                break;
            }
            case 2: {
                unsigned short *values = manager->data;
                for (index = 0; index < count; index++) {
                    manager->flags[*values] = 0;
                    callback(arg, *values);
                    values++;
                }
                break;
            }
            case 4: {
                int *values = manager->data;
                for (index = 0; index < count; index++) {
                    manager->flags[*values] = 0;
                    callback(arg, *values);
                    values++;
                }
                break;
            }
            default:
            err:
                iosJumpRecoverPoint("modman:\tclear error:%d\n", manager->width);
                break;
            }
        }
        manager->used = 0;
    }
}
