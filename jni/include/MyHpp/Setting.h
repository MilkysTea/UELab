//
// Created by Milky_Tea on 2024/12/19.
//

#ifndef SETTING_H
#define SETTING_H
#include "imgui.h"

struct {
    struct {
        bool OpenMenu = true;
        bool Checked = true;
        bool Box = true;
        bool Line = true;
        bool Health = true;
        bool Bone = true;
    }Draw;

    struct {
        ImColor RedColor = ImColor(255,0,0,255);
        ImColor GreenColor = ImColor(0,255,0,255);
        ImColor BlueColor = ImColor(0,0,255,255);
        ImColor YellowColor = ImColor(255,255,0,255);
        ImColor WhiteColor = ImColor(255,255,255,255);
        ImColor BlackColor = ImColor(0,0,0,255);
    }Color;
}Settings;

#endif //SETTING_H
