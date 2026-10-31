typedef struct {
    int id;
    void *emitter;
} EmitterRef;

extern void stop_particle_emitter_callback(void *, int);
extern void end_particle_emitter(void *, int, int);
extern void stop_particle_emitter_geometry_pointer_reference(void *, int);
extern void isysRequestDeleteObj(void *);

static void func_000EE510(void *obj, EmitterRef *r)
{
    stop_particle_emitter_callback(r->emitter, r->id);
    end_particle_emitter(r->emitter, r->id, 1);
    stop_particle_emitter_geometry_pointer_reference(r->emitter, r->id);
}

static void T_000EE558(void *obj)
{
    isysRequestDeleteObj(obj);
}
