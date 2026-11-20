extern char *D_0012FDF8[];
extern char *D_0012FEE8[];
extern char *D_0012FF68[];
extern char *D_0012FFE8[];
extern char *D_00130090[];
extern char *D_001300C0[];
extern char *D_00130140[];
extern char RO_0013C788[];
extern char RO_0013C7C0[];
extern char RO_0013C7F0[];
extern void kprintfContextCentering(void *, const char *, ...);

void DEBUG_disp_center_collision_attribute_info(unsigned long a, void *ctx)
{
    kprintfContextCentering(ctx, RO_0013C788, a & 1, (a & 2) >> 1, (a & 4) >> 2, (a >> 21) & 0xF, (a & 8) >> 3,
                            (a & 0x2000000000000000UL) >> 61);
    kprintfContextCentering(ctx, RO_0013C7C0, D_0012FDF8[(int)((a & 0x3F0) >> 4)], D_0012FEE8[(int)((a & 0x7C00) >> 10)],
                            D_0012FF68[(int)((a >> 26) & 0x1F)], D_001300C0[(int)((a & 0xF80000000UL) >> 31)],
                            D_00130140[(int)((a >> 47) & 0x7F)]);
    kprintfContextCentering(ctx, RO_0013C7F0, (a >> 15) & 0x3F, D_0012FFE8[(int)((a & 0x3F000000000UL) >> 36)],
                            D_00130090[(int)((a & 0x3C0000000000UL) >> 42)]);
}
