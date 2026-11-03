typedef struct { float x, y, z, w; } Vec4;
typedef struct { int type; int pad[3]; int target; int power; int pad18[2]; char geom[0x40]; } DamageMsg;
typedef struct { int target; Vec4 v; int power; } DamageHead;
typedef struct { void (*func)(void); int pad[3]; char data[1]; } LetterHead;
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; struct { float x, y, z, w; } f; } Vector;
extern int D_00139F64;
extern Vector IdentityQuaternion;
extern int create_letter(void *, void *, int, int, int);
extern void init_letter(int, void *, void *);
extern void send_letter(int *);
extern void SetGeometryPointerGlobalState(void *, Vector *, Vector *);
extern void func_000EA0B8(void);
extern void *memset(void *, int, unsigned int);
extern void *memcpy(void *, const void *, unsigned int);

static inline void sethead(LetterHead *h, void (*f)(void), void *d, unsigned int dn) { h->func = f; memcpy(h->data, d, dn); }
static inline void cp(void *d, const void *s, unsigned int n) { memcpy(d, s, n); }

void SendDamageLetter(int target, int dest, int power, Vector *pos)
{
    DamageHead hd;
    union { DamageHead h; Vector v; } u;
    DamageMsg msg;
    LetterHead *head;
    void *body;
    int letter;

    head = 0;
    body = 0;
    letter = create_letter(&head, &body, D_00139F64, 0, dest);
    u.h.target = target;
    u.h.v.x = pos->f.x;
    u.h.v.y = pos->f.y;
    u.h.v.z = pos->f.z;
    u.h.v.w = pos->f.w;
    u.h.power = power;
    hd = u.h;
    msg.type = 0;
    memset(&msg.target, 0, 0x50);
    u.v.q = pos->q;
    msg.target = target;
    msg.power = power;
    u.v.f.w = 1.0f;
    SetGeometryPointerGlobalState(msg.geom, &IdentityQuaternion, &u.v);
    sethead(head, func_000EA0B8, &hd, 0x18);
    cp(body, &msg, 0x60);
    init_letter(letter, &head, &body);
    send_letter(&letter);
}
