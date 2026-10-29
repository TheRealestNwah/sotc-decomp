typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
typedef struct { Vec4 position; Vec4 auxiliary; FinderEntry geometry; } KeepResult;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;
extern int func_000A0DE8(CollisionPoint *, Vec4 *, float *, Vec4 *, FinderEntry *, float);
extern int func_000A1580(CollisionPoint *, Vec4 *, float *, Vec4 *, FinderEntry *, float);

static int func_000AE6F8(CollisionPoint *out, Vec4 *auxiliary, float *start, Vec4 *finish, FinderEntry *entry, float keep)
{
    Vec4 end;
    int status;
    int result = 0;
    end.q = finish->q;
    status = func_000A0DE8(out, auxiliary, start, &end, entry, keep);
    if (status == 1) {
        end.q = out->position.q;
        result = 1;
    }
    if (status == 0 && func_000A1580(out, auxiliary, start, &end, entry, keep))
        result = 1;
    return result;
}
