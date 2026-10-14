extern void isysRequestDeleteObj(int);
extern void flush_game_camera(void *);
extern void iosFree(void *);
void check_free_cameraman(void **slot)
{
    void *camera=*slot;
    if (camera != 0) {
  isysRequestDeleteObj(*(int *)camera);
  flush_game_camera((char *)*slot + 0x20);
  iosFree(*slot);
  *slot=0;
    }
}
