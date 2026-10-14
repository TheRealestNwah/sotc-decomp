extern float D_00139F54;

void set_screen_wide_and_progressive(int wide, int progressive)
{
    if (wide != 0) {
        if (progressive == 0) {
            D_00139F54 = 1.3333333f;
        } else {
            D_00139F54 = 1.0f;
        }
    } else {
        if (progressive == 0) {
            D_00139F54 = 1.0f;
        } else {
            D_00139F54 = 0.75f;
        }
    }
}
