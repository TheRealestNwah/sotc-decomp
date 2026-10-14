extern void set_param_double_spring_interp_common(char *, float, float, float, float);

void constructor_double_spring_interp_cntrl(signed char *arg0, float fparg0) {
    (*(int *)((char *)(arg0) + 0x14)) = 0;
    (*(int *)((char *)(arg0) + 0x1C)) = 0;
    (*(int *)((char *)(arg0) + 0x18)) = 0;
    set_param_double_spring_interp_common(arg0, 2.0f, -1.0f, 1.0f, -1.0f);
    (*(float *)((char *)(arg0) + 0x10)) = fparg0;
}
