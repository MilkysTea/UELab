//
// Created by Milky_Tea on 2024/12/19.
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include <array>
#include <sstream>
#include "RWTools.h"
#include "Class.h"
#include <fstream>

#define AngleConstant 0.1765f
typedef unsigned short UTF16;
typedef char UTF8;

// 读取字符信息
void GetUTF8(UTF8 *buf, unsigned long NameAddress) {
    UTF16 buf16[16] = {0};
    vm_read(NameAddress, buf16, 16);
    UTF16 *pTempUTF16 = buf16;
    UTF8 *pTempUTF8 = buf;
    UTF8 *pUTF8End = pTempUTF8 + 32;
    while (pTempUTF16 < buf16 + 16) {
        if (*pTempUTF16 <= 0x007F && pTempUTF8 + 1 < pUTF8End) {
            *pTempUTF8++ = (UTF8) *pTempUTF16;
        } else if (*pTempUTF16 >= 0x0080 && *pTempUTF16 <= 0x07FF && pTempUTF8 + 2 < pUTF8End) {
            *pTempUTF8++ = (*pTempUTF16 >> 6) | 0xC0;
            *pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
        } else if (*pTempUTF16 >= 0x0800 && *pTempUTF16 <= 0xFFFF && pTempUTF8 + 3 < pUTF8End) {
            *pTempUTF8++ = (*pTempUTF16 >> 12) | 0xE0;
            *pTempUTF8++ = ((*pTempUTF16 >> 6) & 0x3F) | 0x80;
            *pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
        } else {
            break;
        }
        pTempUTF16++;
    }
}

bool WorldToScreen(Vector3 Pos, Vector2 &Point) {
    float camera = Matrix[3] * Pos.x + Matrix[7] * Pos.y + Matrix[11] * Pos.z + Matrix[15];
    if (camera > 0) {
        float x =
                px + (Matrix[0] * Pos.x + Matrix[4] * Pos.y + Matrix[8] * Pos.z + Matrix[12]) / camera * px;
        float y =
                py - (Matrix[1] * Pos.x + Matrix[5] * Pos.y + Matrix[9] * Pos.z + Matrix[13]) / camera * py;

        Point.x = x;
        Point.y = y;
        return true;
    }
    return false;
}

Vector4 WorldToScreen(Vector3 Pos, float *camer) {
    float camera = Matrix[3] * Pos.x + Matrix[7] * Pos.y + Matrix[11] * Pos.z + Matrix[15];
    *camer = camera;
    float r_x =
            px + (Matrix[0] * Pos.x + Matrix[4] * Pos.y + Matrix[8] * Pos.z +
                  Matrix[12]) / camera * px;
    float r_y =
            py - (Matrix[1] * Pos.x + Matrix[5] * Pos.y + Matrix[9] * (Pos.z) +
                  Matrix[13]) / camera * py;
    float rz =
            py - (Matrix[1] * Pos.x + Matrix[5] * Pos.y + Matrix[9] * (Pos.z + 165) +
                  Matrix[13]) / camera * py;
    float r_z = r_y - rz;
    float r_w = (r_y - rz) / 2;
    return {r_x, r_y, r_z, r_w};

}

#endif //FUNCTION_H
