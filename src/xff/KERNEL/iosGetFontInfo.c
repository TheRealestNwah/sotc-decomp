typedef struct { char data[32]; } FontInfo;
extern FontInfo B_000C27B8[];
void iosGetFontInfo(FontInfo *info, int no)
{
    *info = B_000C27B8[no];
}
