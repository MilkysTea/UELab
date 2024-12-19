//
// Created by Milky_Tea on 2024/12/19.
//

#ifndef DRAWFUNTION_H
#define DRAWFUNTION_H

void DrawRect(Vector4 ScreenPos) {
    ImGui::GetBackgroundDrawList()->AddRect({ScreenPos.x - ScreenPos.z / 4, ScreenPos.y - ScreenPos.z / 2},
                  {ScreenPos.x + ScreenPos.z / 4, ScreenPos.y + ScreenPos.z / 2},
                  Settings.Color.RedColor, 5, 0,3);
}

void DrawLine(Vector4 ScreenPos) {
    ImGui::GetBackgroundDrawList()->AddLine({px, 150}, {ScreenPos.x, ScreenPos.y - ScreenPos.z / 2 - 50},
                  Settings.Color.WhiteColor,3);
}

#endif //DRAWFUNTION_H
