//
// Created by Jun Wei Moo on 19/9/24.
//

#include "Camera.h"
#include <cmath>

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
    : position(0.0f, 0.0f, 5.0f),
      target(0.0f, 0.0f, 0.0f),
      up(0.0f, 1.0f, 0.0f),
      fov(fov),
      aspectRatio(aspectRatio),
      nearPlane(nearPlane),
      farPlane(farPlane) {
    RecalculateViewMatrix();
    RecalculateProjectionMatrix();
}

Camera::~Camera() {}

void Camera::Update(float deltaTime) {
    // TODO: Handle camera movement logic here
    RecalculateViewMatrix();
}

Matrix4x4 Camera::GetViewMatrix() const {
    return viewMatrix;
}

Matrix4x4 Camera::GetProjectionMatrix() const {
    return projectionMatrix;
}

Matrix4x4 Camera::GetViewProjectionMatrix() const {
    return projectionMatrix * viewMatrix;
}

Vector3 Camera::GetPosition() const {
    return position;
}

Vector3 Camera::GetTarget() const {
    return target;
}

Vector3 Camera::GetUp() const {
    return up;
}

void Camera::SetPosition(const Vector3& pos) {
    position = pos;
    RecalculateViewMatrix();
}

void Camera::SetTarget(const Vector3& tgt) {
    target = tgt;
    RecalculateViewMatrix();
}

void Camera::SetUp(const Vector3& upDir) {
    up = upDir;
    RecalculateViewMatrix();
}

void Camera::RecalculateViewMatrix() {
    Vector3 forward = (position - target).Normalize();
    Vector3 right = up.Cross(forward).Normalize();
    Vector3 trueUp = forward.Cross(right);

    viewMatrix = Matrix4x4(
        right.x,    right.y,    right.z,    -right.Dot(position),
        trueUp.x,   trueUp.y,   trueUp.z,   -trueUp.Dot(position),
        forward.x,  forward.y,  forward.z,  -forward.Dot(position),
        0.0f,       0.0f,       0.0f,       1.0f
    );
}

void Camera::RecalculateProjectionMatrix() {
    float f = 1.0f / tanf(fov * 0.5f * (M_PI / 180.0f));
    float nf = 1.0f / (nearPlane - farPlane);

    projectionMatrix = Matrix4x4(
        f / aspectRatio, 0.0f, 0.0f,                                 0.0f,
        0.0f,            f,    0.0f,                                 0.0f,
        0.0f,            0.0f, (farPlane + nearPlane) * nf,        (2.0f * farPlane * nearPlane) * nf,
        0.0f,            0.0f, -1.0f,                                0.0f
    );
}
