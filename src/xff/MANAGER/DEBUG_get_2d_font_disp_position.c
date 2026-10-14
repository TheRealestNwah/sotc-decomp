extern int getDrawScreenHeight(void);
extern int getDrawScreenWidth(void);

void DEBUG_get_2d_font_disp_position(float *arg0, float *arg1, float fparg0, float fparg1) {
    int temp_s0;
    int temp_s0_2;

    temp_s0 = getDrawScreenWidth();
    *arg0 = ((float) -temp_s0 * 0.5f) + ((float) getDrawScreenWidth() * fparg0);
    temp_s0_2 = getDrawScreenHeight();
    *arg1 = ((float) -temp_s0_2 * 0.5f) + ((float) getDrawScreenHeight() * fparg1);
}
