
extern float iosGetRandom(void);
extern float iosGetTableCos(short);
extern float iosGetTableSin(short);

void AI_GetRandomSphereOfs(void *arg0, float fparg0, float fparg1) {
    float temp_f20;
    float temp_f20_2;
    float temp_f20_3;
    float temp_f20_4;
    float temp_f21;
    float temp_f24;
    int temp_f0;
    int temp_f0_2;

    temp_f21 = 2.0f * iosGetRandom();
    temp_f20 = (2.0f * iosGetRandom()) - 1.0f;
    temp_f24 = fparg0 + ((fparg1 - fparg0) * iosGetRandom());
    temp_f0 = (int) ((temp_f20 * 3.14159265f * 32768.0f) / 3.14159265f);
    temp_f20_2 = iosGetTableSin((short) temp_f0);
    temp_f0_2 = (int) ((temp_f21 * 3.14159265f * 32768.0f) / 3.14159265f);
    (*(float *)((char *)(arg0) + 0)) = (float) (temp_f20_2 * iosGetTableSin((short) temp_f0_2) * temp_f24);
    (*(float *)((char *)(arg0) + 4)) = (float) (iosGetTableSin((short) temp_f0) * temp_f24);
    temp_f20_3 = iosGetTableSin((short) temp_f0);
    temp_f20_4 = temp_f20_3 * iosGetTableCos((short) temp_f0_2);
    (*(int *)((char *)(arg0) + 0xC)) = 0;
    (*(float *)((char *)(arg0) + 8)) = (float) (temp_f20_4 * temp_f24);
}
