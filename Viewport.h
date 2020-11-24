#pragma once
#import "Math.h"

class Viewport {
public:
    void LookAt(Vector3d eye, Vector3d center, Vector3d up);
    void Perspective(float fovx, float aspect, float near, float far);

    Matrix4d GetViewProjection() const { return projection * view; }

private:
    Matrix4d view;
    Matrix4d projection;
};
