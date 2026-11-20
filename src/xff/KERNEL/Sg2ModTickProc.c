
typedef struct 
{
  void (*func)(void);
  int len;
} EvEntry;
typedef struct 
{
  unsigned char buf[0x200];
  int wp;
  int rp;
  unsigned char msg[0x40];
  int len;
} MidiIn;
typedef struct 
{
  int x0;
  int slotClass;
  char pad8[0x10 - 0x8];
  int active;
  char pad14[0x1C - 0x14];
  int tgt0;
  int tgt1;
  int step0;
  int step1;
  int fading;
  int pad30;
  int cur0;
  int cur1;
  char pad3C[0x64 - 0x3C];
  MidiIn in;
  char pad2B0[0x9B0 - 0x2B0];
} Mod;
extern EvEntry channel_ev[];
extern EvEntry systemcommon_ev[];
extern unsigned char *B_000C5C0C;
extern Mod *B_000C5C10;
extern unsigned int B_000C5C08;
extern Mod B_000C5C18[];
extern int DIntr(void);
extern int EIntr(void);
extern int Sg2SlotCheckSlotClass(int);
/* Parked: 24 words differ (register choice in the MIDI event lookups and the fade update) */
#ifdef NONMATCHING
void Sg2ModTickProc(void)
{
  int intr = DIntr();
  for (B_000C5C08 = 0; B_000C5C08 < 32; B_000C5C08++)
  {
    Mod *m = &B_000C5C18[B_000C5C08];
    MidiIn *in = &m->in;
    B_000C5C0C = in->msg;
    B_000C5C10 = m;
    while (in->wp != in->rp)
    {
      unsigned char c = in->buf[in->rp];
      in->rp = (in->rp + 1) & 0x1FF;
      if (c < 0xF7)
      {
        if (((signed char) c) < 0)
        {
          in->len = 0;
        }
        in->msg[in->len++] = c;
        if (in->msg[0] < 0xF0)
        {
          if (in->len >= channel_ev[(*B_000C5C0C) >> 4].len)
          {
            channel_ev[(*B_000C5C0C) >> 4].func();
            in->len = 1;
          }
        }
        else
          if (in->len >= systemcommon_ev[(*B_000C5C0C) & 0xF].len)
        {
          systemcommon_ev[(*B_000C5C0C) & 0xF].func();
          in->len = 1;
        }
      }
      else
        if (c == 0xF7)
      {
        systemcommon_ev[(*B_000C5C0C) & 0xF].func();
        in->len = 1;
      }
      else
      {
        if (((signed char) c) < 0)
        {
          in->len = 0;
        }
        in->msg[in->len++] = c;
        if (in->len >= systemcommon_ev[c & 0xF].len)
        {
          systemcommon_ev[c & 0xF].func();
          in->len = 1;
        }
      }
    }

    if ((B_000C5C10->active != 0) && (Sg2SlotCheckSlotClass(B_000C5C10->slotClass) == 0))
    {
      Mod *f = B_000C5C10;
      f->x0 = -1;
      f->active = 0;
    }
    if (B_000C5C10->fading)
    {
      Mod *f = B_000C5C10;
      int s0 = f->step0;
      int d = (f->step1 < 0 ? -f->step1 : f->step1) < (s0 < 0 ? -s0 : s0) ? f->step0 : f->step1;
      f->cur0 = f->cur0 + f->step0;
      f->cur1 = f->step1 + f->cur1;
      if (((d > 0) && (B_000C5C10->cur0 >= B_000C5C10->tgt0)) || ((d < 0) && (B_000C5C10->cur0 <= B_000C5C10->tgt0)))
      {
        B_000C5C10->cur0 = B_000C5C10->tgt0;
      }
      if (((d > 0) && (B_000C5C10->cur1 >= B_000C5C10->tgt1)) || ((d < 0) && (B_000C5C10->cur1 <= B_000C5C10->tgt1)))
      {
        B_000C5C10->cur1 = B_000C5C10->tgt1;
      }
      if ((B_000C5C10->cur0 == B_000C5C10->tgt0) && (B_000C5C10->cur1 == B_000C5C10->tgt1))
      {
        B_000C5C10->fading = 0;
      }
    }
  }

  if (intr)
  {
    EIntr();
  }
}
#endif
