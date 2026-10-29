extern int D_0013583C, D_00135838, D_001359B8;
extern int D_00135830, D_00135834;
extern float D_001359B0;
extern void bossDeathEffectEnd(void);
extern void solarFlare(void);
extern void reflectionEnd(void);
extern void refractionEnd(void);
extern void waterRefractionEnd(void);
extern void shadowDraw(void);
extern void bgEnd(void);
extern int *getFogMode(void);
extern void zFog(void);
extern void feedbackBlur2(int, float, float);
extern void cameraBlur(int, float);
extern void screenBrightness(int);
extern void drawFrontFog(void);
extern void iosDlPushLayer(int);
extern void iosSetRootDC(void);
extern void iosDlPopLayer(void);
void graphFrameFinish(void)
{
    if (D_0013583C != 0) {
        if (D_00135838 != 0 && D_001359B8 == 0) {
            bossDeathEffectEnd();
            solarFlare();
            reflectionEnd();
            refractionEnd();
            waterRefractionEnd();
            shadowDraw();
            bgEnd();
            if (*getFogMode() != 0)
                zFog();
            if (D_00135830 > 0)
                feedbackBlur2(D_00135830, 1.0f, 0.5f);
            else if (D_00135830 < 0)
                D_00135830 = -D_00135830;
            cameraBlur(1, D_001359B0);
            screenBrightness(D_00135834);
            drawFrontFog();
        }
        iosDlPushLayer(23);
        iosSetRootDC();
        iosDlPopLayer();
        iosDlPushLayer(20);
        iosSetRootDC();
        iosDlPopLayer();
    }
}
