extern char B_0015D530[];
extern void *B_0015D4B0;
extern int D_00139F3C;
extern void constructor_camera_context(void *);

void init_camera_context_manager(void)
{
    char *c = B_0015D530;
    constructor_camera_context(c);
    D_00139F3C = 0;
    B_0015D4B0 = c;
}
