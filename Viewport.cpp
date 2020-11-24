#include "Viewport.h"

void Viewport::LookAt(Vector3d eye, Vector3d center, Vector3d up)
{
    Vector3d fwd = (eye - center).normalized();
    Vector3d side = cross(fwd, up).normalized();
    up = cross(side, fwd);
    Matrix4d m = {
        side.x, side.y, side.z, 0,
        up.x, up.y, up.z, 0,
        fwd.x, fwd.y, fwd.z, 0,
        0, 0, 0, 1,
    };
    view = m * Matrix4d::move(eye.negated());
}

void Viewport::Perspective(float fovx, float aspect, float near, float far)
{
    float t = 1.0f / tanf(fovx / 2);
    projection = {
        t, 0, 0, 0,
        0, t * aspect, 0, 0,
        0, 0, (far + near) / (near - far), (2 * far * near) / (near - far),
        0, 0, -1, 0,
    };
}
