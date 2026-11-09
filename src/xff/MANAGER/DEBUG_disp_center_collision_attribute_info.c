/* Parked: ~88 words off. gcc hoists the 1 and 0xF masks into registers (original uses andi) and orders the bitfield extractions differently. */
#ifdef NONMATCHING
extern int D_0012FDF8[];
extern int D_0012FEE8[];
extern int D_0012FF68[];
extern int D_0012FFE8[];
extern int D_00130090[];
extern int D_001300C0[];
extern int D_00130140[];
extern char RO_0013C788[];
extern char RO_0013C7C0[];
extern char RO_0013C7F0[];
extern void kprintfContextCentering(int, char *, long, long, long, long, long, long);

void DEBUG_disp_center_collision_attribute_info(unsigned long a, int ctx)
{
    kprintfContextCentering(ctx, RO_0013C788, a & 1, (a & 2) >> 1, (a & 4) >> 2, (a >> 21) & 0xF, (a & 8) >> 3, (a >> 29) & 1);
    kprintfContextCentering(ctx, RO_0013C7C0, D_0012FDF8[(long)((a & 0x3F0) << 0x1C) >> 0x20], D_0012FEE8[(long)((a & 0x7C00) << 0x16) >> 0x20],
                            D_0012FF68[(long)(((a >> 26) & 0x1F) << 0x20) >> 0x20], D_001300C0[(long)(((a >> 31) & 0x1F) << 0x20) >> 0x20],
                            D_00130140[(long)(((a >> 47) & 0x7F) << 0x20) >> 0x20], 0);
    kprintfContextCentering(ctx, RO_0013C7F0, (a >> 15) & 0x3F, D_0012FFE8[(long)(((a >> 36) & 0x3F) << 0x20) >> 0x20],
                            D_00130090[(long)(((a >> 42) & 0xF) << 0x20) >> 0x20], 0, 0, 0);
}
#else
extern void DEBUG_disp_center_collision_attribute_info(unsigned long, int);
#endif
