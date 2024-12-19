#ifndef MYPROJECT_CLASS_H
#define MYPROJECT_CLASS_H

class Rotator {
public:
    Rotator() : Pitch(0.f), Yaw(0.f), Roll(0.f) {

    }

    Rotator(float _Pitch, float _Yaw, float _Roll) : Pitch(_Pitch), Yaw(_Yaw), Roll(_Roll) {

    }

    ~Rotator() {

    }

    float Pitch;
    float Yaw;
    float Roll;

    inline Rotator Clamp() {

        if (Pitch > 180) {
            Pitch -= 360;
        } else {
            if (Pitch < -180) {
                Pitch += 360;
            }
        }
        if (Yaw > 180) {
            Yaw -= 360;
        } else {
            if (Yaw < -180) {
                Yaw += 360;
            }
        }
        if (Pitch > 89) {
            Pitch = 89;
        }
        if (Pitch < -89) {
            Pitch = -89;
        }
        while (Yaw < 180) {
            Yaw += 360;
        }
        while (Yaw > 180) {
            Yaw -= 360;
        }
        Roll = 0;
        return Rotator(Pitch, Yaw, Roll);
    }

    inline float Length() {
        return sqrtf(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
    }

    Rotator operator+(Rotator v) {
        return Rotator(Pitch + v.Pitch, Yaw + v.Yaw, Roll + v.Roll);
    }

    Rotator operator-(Rotator v) {
        return Rotator(Pitch - v.Pitch, Yaw - v.Yaw, Roll - v.Roll);
    }
};

struct Quat {
    float x;
    float y;
    float z;
    float w;
};

struct FTransform {
    Quat Rotation;
    Vector3 Translation;
    float chunk;
    Vector3 Scale3D;
    float Size;
};

struct FMatrix {
    float M[4][4];
};

#endif //MYPROJECT_CLASS_H
