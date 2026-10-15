typedef struct { long d[10]; } WindGeom;

void CopyScriptAnimationWindGeometryPointer(WindGeom *dst, WindGeom *src)
{
    *dst = *src;
}
