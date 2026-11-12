extern char ZeroPoint[];
extern void *memset(void *, int, unsigned int);
extern void iosGetSinCosf(float *, float);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void glBegin(int);
extern void glEnd(void);
extern void glBlendFunc(int, int);
extern void glColor4f(float, float, float, float);
extern void glColor4fv(void *);
extern void glVertex3fv(void *);

#ifdef NONMATCHING /* 153 diffs, 181 vs 182 words: arc-loop and range-test layout, float register pinning (orig uses $f20-$f24) */
void disphalfarc(void *color, float angle, float radius)
{
    float v[4] __attribute__((aligned(16)));
    float sc[4] __attribute__((aligned(16)));
    float start = angle;
    float end;
    float cur, step;

    if (!(angle <= 0.0f))
        start = 0.0f;
    end = angle;
    if (!(0.0f <= angle))
        end = 0.0f;
    memset(v, 0, 16);
    v[3] = 1.0f;
    iosGetSinCosf(sc, angle);
    iosDlPushLayer(0x17);
    glBegin(8);
    glBlendFunc(5, 6);
    glEnd();
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glBegin(1);
    if (angle < 0.0f ? -3.1415927f < angle : angle < 3.1415927f) {
        glVertex3fv(ZeroPoint);
        v[0] = sc[1] * radius;
        v[2] = sc[0] * radius;
        glVertex3fv(v);
    }
    cur = start;
    glVertex3fv(ZeroPoint);
    v[0] = 0.0f;
    v[2] = radius;
    glVertex3fv(v);
    glEnd();
    glBegin(2);
    if (start < end) {
        do {
            iosGetSinCosf(sc, cur);
            cur += 0.15707964f;
            v[0] = sc[1] * radius;
            v[2] = sc[0] * radius;
            glVertex3fv(v);
        } while (cur < end);
    }
    iosGetSinCosf(sc, end);
    cur = start;
    v[0] = sc[1] * radius;
    v[2] = sc[0] * radius;
    glVertex3fv(v);
    glEnd();
    glColor4fv(color);
    glBegin(6);
    glVertex3fv(ZeroPoint);
    if (cur < end) {
        do {
            iosGetSinCosf(sc, cur);
            cur += 0.15707964f;
            v[0] = sc[1] * radius;
            v[2] = sc[0] * radius;
            glVertex3fv(v);
        } while (cur < end);
    }
    iosGetSinCosf(sc, end);
    v[0] = sc[1] * radius;
    v[2] = sc[0] * radius;
    glVertex3fv(v);
    glEnd();
    iosDlPopLayer();
}
#endif
