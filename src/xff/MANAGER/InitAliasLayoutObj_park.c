/* Parked: 1 diff (was 5), same size.
 * Remaining: beqz instead of beql on the final dst+0x144 check (the Original
 * annuls the "return 1" copy in the delay slot). Selecting the source pointer
 * before the 16-byte copy lets the sq go into the func_00074A78 jal slot. */
#ifdef NONMATCHING

extern char *GetScriptLayoutClass(void *);
extern void *dynamic_cast_to_camera_obj(void *);
extern char *get_camera_obj_layout_class(void *);
extern char *GetLightClass(void *);
inline static char *layoutClass(unsigned char *o)
{
  switch (o[8])
  {
    case 0xA:
      return ((char *) o) + 0x20;

    case 0xB:
      return GetScriptLayoutClass(o) + 0x70;

    case 0x11:
      return get_camera_obj_layout_class(dynamic_cast_to_camera_obj(o));

    case 0x13:
      return GetLightClass(o);

    case 9:

    case 0xD:

    case 0x16:
      return ((char *) o) + 0x90;

    default:
      return 0;

  }

}

typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroPoint;
extern unsigned short D_00136BE0;
extern void func_00074A78(void *, int *, int);
extern void CreateClothChildLayoutObj(void *, int, int);
extern void *GetLayoutDispObjGroup(void);
extern void *GetLayoutObjGroup(void);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
int InitAliasLayoutObj(unsigned char *obj, int *def, unsigned char *parent)
{
  char *src;
    int new_var;
  char *dst;
  src = layoutClass(parent);
  if (src == 0)
  {
    return 0;
  }
  dst = layoutClass(obj);
  *((int *) (dst + 0x134)) = (int) (src + 0x10);
  *((int *) (dst + 0x138)) = (int) (src + 0x20);
  *((int *) (dst + 0x13C)) = (int) (src + 0x50);
  *((int *) (dst + 0x194)) = (int) parent;
  dst[0x1BC] = 0;
  *((int *) (dst + 0x138)) = *((int *) (src + 0x138));
  *((int *) (dst + 0x134)) = *((int *) (src + 0x134));
  *((int *) (dst + 0x13C)) = *((int *) (src + 0x13C));
  *((int *) (dst + 0x154)) = *((int *) (src + 0x154));
  *((int *) (dst + 0x158)) = *((int *) (src + 0x158));
  *((int *) (dst + 0x15C)) = *((int *) (src + 0x15C));
  *((int *) (dst + 0x164)) = *((int *) (src + 0x164));
  *((int *) (dst + 0x168)) = *((int *) (src + 0x168));
  *((int *) (dst + 0x160)) = *((int *) (src + 0x160));
  *((int *) (dst + 0x16C)) = *((int *) (src + 0x16C));
  *((int *) (dst + 0x170)) = *((int *) (src + 0x170));
  {
    s128 *p = (s128 *) def[10];
    if (!p) p = &ZeroPoint;
    *((s128 *) dst) = *p;
  }
  func_00074A78(obj, def, 0);
  CreateClothChildLayoutObj(obj, def[3], 0);
  if ((*((int *) (layoutClass(obj) + 0x144))) != 0)
  {
    isysAddGroupWithLinkParam(obj, GetLayoutDispObjGroup(), 0, 0);
  }
  isysAddGroupWithLinkParam(obj, GetLayoutObjGroup(), 0, 0);
  if (new_var = (*((int *) (dst + 0x144))) != 0)
  {
    unsigned short n = D_00136BE0++;
    *((unsigned short *) ((*((int *) (dst + 0x144))) + 0x262)) = n;
  }
  return 1;
}
#else
extern int InitAliasLayoutObj(unsigned char *, int *, unsigned char *);
#endif
