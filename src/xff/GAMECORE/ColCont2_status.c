typedef struct CollisionStatus {
    unsigned long status;
    unsigned long eventStatus;
} CollisionStatus;

int ColCont2_IsColStatus(CollisionStatus *self, long mask, long expected)
{
    if (expected == -1) {
        if (mask == expected)
            return 1;
    } else {
        if ((self->status & mask) == expected)
            return 1;
        goto fail;
    }
    if (self->status & mask)
        return 1;
fail:
    return 0;
}

int ColCont2_IsEventColStatus(CollisionStatus *self, long mask, long expected)
{
    if (expected == -1) {
        if (mask == expected)
            return 1;
    } else {
        if ((self->eventStatus & mask) == expected)
            return 1;
        goto fail;
    }
    if (self->eventStatus & mask)
        return 1;
fail:
    return 0;
}
