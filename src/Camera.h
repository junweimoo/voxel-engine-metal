//
// Created by Jun Wei Moo on 19/9/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "utils/Math.h"

class Camera {
public:
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);
    ~Camera();

    void Update(float deltaTime);
    Matrix4x4 GetViewMatrix() const;
    Matrix4x4 GetProjectionMatrix() const;
    Matrix4x4 GetViewProjectionMatrix() const;

    void SetPosition(const Vector3& position);
    void SetTarget(const Vector3& target);
    void SetUp(const Vector3& up);

    Vector3 GetPosition() const;
    Vector3 GetTarget() const;
    Vector3 GetUp() const;

private:
    Vector3 position;
    Vector3 target;
    Vector3 up;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    Matrix4x4 viewMatrix;
    Matrix4x4 projectionMatrix;

    void RecalculateViewMatrix();
    void RecalculateProjectionMatrix();
};

#endif //CAMERA_H
