typedef struct { int type; int pad[3]; int target; float damage; float power; int pad1C; char geom[0x40]; } DamageMsg;
typedef struct { void (*func)(void); int pad[3]; char data[1]; } LetterHead;
extern int D_00139F60;
extern int create_letter(void *, void *, int, int, int);
extern void init_letter(int, void *, void *);
extern void send_letter(int *);
extern void CopyGeometryPointer(void *, void *);
extern void func_000EBE78(void);
extern void *memset(void *, int, unsigned int);
extern void *memcpy(void *, const void *, unsigned int);

static inline void sethead(LetterHead *h, void (*f)(void), void *d, unsigned int dn) { h->func = f; memcpy(h->data, d, dn); }
static inline void cp(void *d, const void *s, unsigned int n) { memcpy(d, s, n); }

void SendDirectDamageLetter(int target, int dest, void *geom, int power, float damage)
{
    DamageMsg msg;
    LetterHead *head;
    void *body;
    int letter;

    head = 0;
    body = 0;
    letter = create_letter(&head, &body, D_00139F60, dest, 0);
    msg.type = 1;
    memset(&msg.target, 0, 0x50);
    msg.target = target;
    msg.damage = damage;
    msg.power = power;
    CopyGeometryPointer(msg.geom, geom);
    sethead(head, func_000EBE78, 0, 0);
    cp(body, &msg, 0x60);
    init_letter(letter, &head, &body);
    send_letter(&letter);
}
