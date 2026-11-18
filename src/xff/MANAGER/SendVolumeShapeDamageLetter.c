/* SendVolumeShapeDamageLetter: parked at 16 diffs, like its siblings
 * SendDamageBoxLetter and SendDamageCylinderLetter. Remaining: float register
 * numbering (pos[0] lands in $f8 instead of $f2) and the order of the target/b
 * stores. */
#ifdef NONMATCHING
typedef struct { int type; int pad[3]; int target; int a; int pad18[2]; char geom[0x40]; } DamageMsg;
typedef struct { int target; float p[3]; float q[4]; float s[3]; float r[2]; int a; int b; } VolHead;
typedef struct { void (*func)(void); int pad[3]; char data[1]; } LetterHead;
extern int D_00139F64;
extern int create_letter(void *, void *, int, int, int);
extern void init_letter(int, void *, void *);
extern void send_letter(int *);
extern void SetGeometryPointerGlobalState(void *, void *, void *);
extern void func_000EA9F8(void);
extern void *memset(void *, int, unsigned int);
extern void *memcpy(void *, const void *, unsigned int);

static inline void sethead(LetterHead *h, void (*f)(void), void *d, unsigned int dn) { h->func = f; memcpy(h->data, d, dn); }
static inline void cp(void *d, const void *s, unsigned int n) { memcpy(d, s, n); }

void SendVolumeShapeDamageLetter(int target, int dest, int a, int b, float *pos, float *quat, float *size, float *range)
{
    VolHead hd;
    VolHead u;
    DamageMsg msg;
    LetterHead *head;
    void *body;
    int letter;

    head = 0;
    body = 0;
    letter = create_letter(&head, &body, D_00139F64, 0, dest);
    u.target = target;
    u.p[0] = pos[0];
    u.p[1] = pos[1];
    u.p[2] = pos[2];
    u.q[0] = quat[0];
    u.q[1] = quat[1];
    u.q[2] = quat[2];
    u.q[3] = quat[3];
    u.s[0] = size[0];
    u.s[1] = size[1];
    u.s[2] = size[2];
    u.r[0] = range[1];
    u.r[1] = range[0];
    u.a = a;
    u.b = b;
    hd = u;
    msg.type = 0;
    memset(&msg.target, 0, 0x50);
    msg.target = target;
    msg.a = a;
    SetGeometryPointerGlobalState(msg.geom, quat, pos);
    sethead(head, func_000EA9F8, &hd, 0x3C);
    cp(body, &msg, 0x60);
    init_letter(letter, &head, &body);
    send_letter(&letter);
}
#endif
