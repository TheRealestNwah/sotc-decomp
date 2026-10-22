typedef struct {
    float vector[5][4];
} CollisionPoint __attribute__((aligned(16)));

void ConstructorCollisionPoint(CollisionPoint *point)
{
    CollisionPoint initial = {
        { {0.0f, 0.0f, 0.0f, 1.0f},
          {0.0f, 0.0f, 0.0f, 1.0f},
          {0.0f, 0.0f, 0.0f, 0.0f},
          {0.0f, 0.0f, 0.0f, 0.0f},
          {0.0f, 0.0f, 0.0f, 1.0f} }
    };
    *point = initial;
}
