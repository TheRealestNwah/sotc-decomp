extern void iosFree(void *);

void check_free_clip_screen(void **arg0) {
    void *temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        iosFree(temp_v0);
        *arg0 = 0;
    }
}
