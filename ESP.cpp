#include "ESP.h"
#include "g_mem.h"
#include "offsets.h"
#include <cmath>
#include <algorithm>
#include <cstdio>

// Undefine any potential macro conflicts
#ifdef RGB
#undef RGB
#endif

//
// WorldToScreenConverter Implementation
//

WorldToScreenConverter::WorldToScreenConverter()
    : gameDimensions(1920, 1080), overlayDimensions(1920, 1080), hasValidMatrix(false) {}

Vector2 WorldToScreenConverter::MapGameToOverlay(const Vector2& gameScreen) const {
    if (gameDimensions.x <= 0.0f || gameDimensions.y <= 0.0f)
        return gameScreen;

    float scaleX = overlayDimensions.x / gameDimensions.x;
    float scaleY = overlayDimensions.y / gameDimensions.y;

    return Vector2(
        (gameScreen.x - gameDimensions.x * 0.5f) * scaleX + overlayDimensions.x * 0.5f,
        (gameScreen.y - gameDimensions.y * 0.5f) * scaleY + overlayDimensions.y * 0.5f
    );
}

void WorldToScreenConverter::Update(HWND robloxWindow) {
    uintptr_t visualEngine = g_Memory.ReadPtr(g_Memory.GetBaseAddress() + Offsets::VisualEngine::Pointer);
    if (!visualEngine) return;

    Vector2 dims = g_Memory.Read<Vector2>(visualEngine + Offsets::VisualEngine::Dimensions);
    if (dims.x > 0.0f && dims.y > 0.0f) {
        gameDimensions = dims;
    }

    RECT clientRect{};
    if (robloxWindow && GetClientRect(robloxWindow, &clientRect)) {
        overlayDimensions.x = static_cast<float>(clientRect.right - clientRect.left);
        overlayDimensions.y = static_cast<float>(clientRect.bottom - clientRect.top);
    }

    viewProjectionMatrix = g_Memory.Read<Matrix4x4>(visualEngine + Offsets::VisualEngine::ViewMatrix);
    hasValidMatrix = (viewProjectionMatrix[0][0] != 0.0f || viewProjectionMatrix[1][1] != 0.0f);
}

Vector2 WorldToScreenConverter::Project(const Vector3& worldPos) {
    if (!hasValidMatrix) return Vector2(-1, -1);

    Vector4 clipPos;
    clipPos.x = worldPos.x * viewProjectionMatrix[0][0] + worldPos.y * viewProjectionMatrix[0][1] +
        worldPos.z * viewProjectionMatrix[0][2] + viewProjectionMatrix[0][3];
    clipPos.y = worldPos.x * viewProjectionMatrix[1][0] + worldPos.y * viewProjectionMatrix[1][1] +
        worldPos.z * viewProjectionMatrix[1][2] + viewProjectionMatrix[1][3];
    clipPos.z = worldPos.x * viewProjectionMatrix[2][0] + worldPos.y * viewProjectionMatrix[2][1] +
        worldPos.z * viewProjectionMatrix[2][2] + viewProjectionMatrix[2][3];
    clipPos.w = worldPos.x * viewProjectionMatrix[3][0] + worldPos.y * viewProjectionMatrix[3][1] +
        worldPos.z * viewProjectionMatrix[3][2] + viewProjectionMatrix[3][3];

    if (clipPos.w < 0.001f) return Vector2(-1, -1);

    float invW = 1.0f / clipPos.w;
    float ndcX = clipPos.x * invW;
    float ndcY = clipPos.y * invW;

    Vector2 gameScreen;
    gameScreen.x = (ndcX + 1.0f) * 0.5f * gameDimensions.x;
    gameScreen.y = (1.0f - ndcY) * 0.5f * gameDimensions.y;

    return MapGameToOverlay(gameScreen);
}

//
//
//

//
// ESP Implementation
//

ESP::ESP(WorldToScreenConverter* converter) : w2s(converter) {}

ESPBounds ESP::ComputeBounds(const Vector2& head, const Vector2& root, const Vector2& foot, float sizeScale) {
    ESPBounds bounds = {};
    bounds.valid = false;

    if (head.x < 0.0f || head.y < 0.0f || root.x < 0.0f || root.y < 0.0f)
        return bounds;

    float top = head.y;
    float bottom = (foot.x >= 0.0f && foot.y >= 0.0f) ? foot.y : root.y;
    float centerX = root.x;

    float height = bottom - top;
    if (height < 8.0f) height = 8.0f;

    float width = height * 0.45f;
    width *= sizeScale / 80.0f;

    const float headPadding = height * 0.08f;
    const float footPadding = height * 0.05f;

    bounds.top = top - headPadding;
    bounds.bottom = bottom + footPadding;
    bounds.left = centerX - width * 0.5f;
    bounds.right = centerX + width * 0.5f;
    bounds.valid = true;
    return bounds;
}

float ESP::CalculateDistance(const Vector3& pos1, const Vector3& pos2) {
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    float dz = pos1.z - pos2.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

ImU32 ESP::GetHealthColor(float healthPercent) {
    if (healthPercent > 0.66f) {
        return IM_COL32(0, 255, 0, 255);      // Green
    }
    else if (healthPercent > 0.33f) {
        return IM_COL32(255, 255, 0, 255);     // Yellow
    }
    else {
        return IM_COL32(255, 0, 0, 255);       // Red
    }
}

//
//
//

//
// PLAYER RELATED STUFF
//

void ESP::RenderPlayers(const std::vector<PlayerInfo>& players, ImDrawList* drawList) {
    if (!config.enableESP || !w2s || !drawList) return;

    // Find local player for distance calculations
    PlayerInfo localPlayer;
    for (const auto& p : players) {
        if (p.isLocal) {
            localPlayer = p;
            break;
        }
    }

    int idx = 0;
    for (const auto& player : players) {
        if (!player.isValid) continue;
        float distance = 10.0f;
        if (localPlayer.isValid) {
            distance = CalculateDistance(player.headPosition, localPlayer.headPosition);
        }
        if (distance > config.dist) continue;
        if (player.isLocal && !config.showLocalPlayer) continue;
        if (!player.isLocal && !config.showOtherPlayers) continue;

        // Calculate screen positions
        Vector3 headTop = player.headPosition;
        headTop.y += 0.5f;

        Vector3 footPos = player.rootPosition;
        footPos.y -= 3.0f;

        Vector2 head2D = w2s->Project(headTop);
        Vector2 root2D = w2s->Project(player.rootPosition);
        Vector2 foot2D = w2s->Project(footPos);

        ESPBounds bounds = ComputeBounds(head2D, root2D, foot2D, config.boxSize);
        if (!bounds.valid) continue;

        // Distance-based opacity
        float distanceOpacity = config.opacity;
        if (distance > 20.0f) {
            float opacityFactor = 20.0f / distance;
            opacityFactor = (std::max)(0.3f, opacityFactor);
            distanceOpacity = config.opacity * opacityFactor;
        }

        // Draw ESP box (outline)
        drawList->AddRect(
            ImVec2(bounds.left, bounds.top),
            ImVec2(bounds.right, bounds.bottom),
            IM_COL32(255, 255, 255, (int)(distanceOpacity * 255)),
            0.0f,
            0,
            2.0f
        );

        // Render player info
        RenderPlayerInfo(player, drawList, bounds);

        // Render health
        if (config.showHealth) {
            RenderPlayerHealth(player, drawList, bounds, distance);
        }

        // Render distance
        if (distance > 0.0f) {
            char distText[32];
            sprintf_s(distText, "%.0f", distance);
            ImVec2 distSize = ImGui::CalcTextSize(distText);
            float centerX = (bounds.left + bounds.right) * 0.5f;
            drawList->AddText(
                ImVec2(centerX - distSize.x * 0.5f, bounds.bottom + 4.0f),
                IM_COL32(255, 255, 255, 255),
                distText
            );
        }

        idx++;
    }
}

void ESP::RenderPlayerInfo(const PlayerInfo& player, ImDrawList* drawList, const ESPBounds& bounds) {
    float centerX = (bounds.left + bounds.right) * 0.5f;
    float textGap = 4.0f;

    if (!config.showHealth) {
        // Just show name above the box
        ImVec2 textSize = ImGui::CalcTextSize(player.name.c_str());
        drawList->AddText(
            ImVec2(centerX - textSize.x * 0.5f, bounds.top - textSize.y - textGap),
            IM_COL32(255, 255, 255, 255),
            player.name.c_str()
        );
    }
}

void ESP::RenderPlayerHealth(const PlayerInfo& player, ImDrawList* drawList, const ESPBounds& bounds, const float distance) {
    float centerX = (bounds.left + bounds.right) * 0.5f;
    float textGap = 4.0f;
    float currentHealth = player.health * player.maxHealth;
    ImU32 healthColor = GetHealthColor(player.health);
    ImU32 BarColor = IM_COL32(197, 107, 47, 255);
    ImU32 HTextColor = IM_COL32(255, 255, 255, 255);
    if (config.ColoredBar) {
        BarColor = healthColor;
        HTextColor = healthColor;
    }

    // Format health text
    char healthText[128];
    if (config.showHealthText) {
        sprintf_s(healthText, "%s [%d/%d]", player.name.c_str(),
            (int)currentHealth, (int)player.maxHealth);
    }
    else {
        sprintf_s(healthText, "%s", player.name.c_str());
    }
    ImVec2 textSize = ImGui::CalcTextSize(healthText);

    // Draw health text above the box
    drawList->AddText(
        ImVec2(centerX - textSize.x * 0.5f, bounds.top - textSize.y - textGap),
        HTextColor,
        healthText
    );

    // Draw health bar - NOW BELOW THE NICKNAME, ABOVE THE BOX
    if (config.showHealthBar) {   // use showHealthBarNPC for NPCs
        if (distance < 120) {
            float barWidth = 8.0f;                                    // thickness of the bar
            float barHeight = bounds.bottom - bounds.top;             // full height of the box
            float barX = bounds.left - barWidth - 3.0f;               // 3px gap from the box
            float barY = bounds.top;

            // Background
            drawList->AddRectFilled(
                ImVec2(barX, barY),
                ImVec2(barX + barWidth, barY + barHeight),
                IM_COL32(40, 40, 40, 200)
            );

            // Health fill (from bottom up)
            float fillHeight = barHeight * player.health;             // use NPC.health for NPCs
            if (fillHeight > 0.0f) {
                drawList->AddRectFilled(
                    ImVec2(barX, barY + (barHeight - fillHeight)),
                    ImVec2(barX + barWidth, barY + barHeight),
                    BarColor
                );
            }

            // Optional: segment dividers every 20%
            for (int i = 1; i < 5; ++i) {
                float dividerY = barY + barHeight * (1.0f - i * 0.2f);
                drawList->AddLine(
                    ImVec2(barX, dividerY),
                    ImVec2(barX + barWidth, dividerY),
                    IM_COL32(0, 0, 0, 220),
                    1.0f
                );
            }

            // Outline
            drawList->AddRect(
                ImVec2(barX, barY),
                ImVec2(barX + barWidth, barY + barHeight),
                IM_COL32(0, 0, 0, 255),
                0.0f, 0, 1.0f
            );
        }
        else {
            float barWidth = textSize.x * 0.6;  // Use the actual text width instead of box width
            float barHeight = 6.0f;       // Fixed height for consistent look //6
            float barX = centerX - barWidth * 0.5f;
            float barY = bounds.top - barHeight + textGap / 2;

            // Background bar
            drawList->AddRectFilled(
                ImVec2(barX, barY),
                ImVec2(barX + barWidth, barY + barHeight),
                IM_COL32(50, 50, 50, 180)
            );

            // Health fill
            float fillWidth = barWidth * player.health;
            if (fillWidth > 0.0f) {
                // Inner padding for cleaner look
                float padding = 1.0f;
                drawList->AddRectFilled(
                    ImVec2(barX + padding, barY + padding),
                    ImVec2(barX + fillWidth - padding, barY + barHeight - padding),
                    BarColor
                );
            }

            // Segment dividers every 20%
            for (int i = 1; i < 5; ++i) {
                float dividerX = barX + barWidth * (i * 0.2f);
                drawList->AddLine(
                    ImVec2(dividerX, barY + 1.0f),
                    ImVec2(dividerX, barY + barHeight - 1.0f),
                    IM_COL32(0, 0, 0, 220),
                    1.5f
                );
            }

            // Outline
            drawList->AddRect(
                ImVec2(barX, barY),
                ImVec2(barX + barWidth, barY + barHeight),
                IM_COL32(0, 0, 0, 180),
                0.0f,
                0,
                1.0f
            );
        }
    }

    // Health text on the side of the box (only if health bar is disabled)
    //if (config.showHealthText && !config.showHealthBar) {
    //    char healthValueText[32];
    //    sprintf_s(healthValueText, "%d/%d", (int)currentHealth, (int)player.maxHealth);
    //    drawList->AddText(
    //        ImVec2(bounds.right + 5.0f, bounds.top),
    //        healthColor,
    //        healthValueText
    //    );
    //}
}

//
//
//

//
// NPC RELATED STUFF
//

void ESP::RenderNPC(const std::vector<PlayerInfo>& players, const std::vector<NPCInfo>& NPCL, ImDrawList* drawList) {
    if (!config.enableNPCESP || !w2s || !drawList) return;

    // Find local player for distance calculations
    PlayerInfo localPlayer;
    for (const auto& p : players) {
        if (p.isLocal) {
            localPlayer = p;
            break;
        }
    }

    int idx = 0;
    for (const auto& NPC : NPCL) {
        if (!NPC.isValid) continue;
        float distance = 10.0f;
        // Calculate distance / Check distance
        if (localPlayer.isValid) {
            distance = CalculateDistance(NPC.headPosition, localPlayer.headPosition);
        }
        if (distance > config.distNPC) continue;

        // Calculate screen positions
        Vector3 headTop = NPC.headPosition;
        headTop.y += 0.5f;

        Vector3 footPos = NPC.rootPosition;
        footPos.y -= 3.0f;

        Vector2 head2D = w2s->Project(headTop);
        Vector2 root2D = w2s->Project(NPC.rootPosition);
        Vector2 foot2D = w2s->Project(footPos);

        ESPBounds bounds = ComputeBounds(head2D, root2D, foot2D, config.boxSize);
        if (!bounds.valid) continue;

        // Distance-based opacity
        //float distanceOpacity = config.opacityNPC;
        //if (distance > 20.0f) {
        //    float opacityFactor = 20.0f / distance;
        //    opacityFactor = (std::max)(0.3f, opacityFactor);
        //    distanceOpacity = config.opacityNPC * opacityFactor;
        //}

        //// Draw ESP box (filled background)
        //ImU32 fillColor;
        //fillColor = IM_COL32(0, 0, 0, (int)(distanceOpacity * 0));

        //drawList->AddRectFilled(
        //    ImVec2(bounds.left, bounds.top),
        //    ImVec2(bounds.right, bounds.bottom),
        //    fillColor
        //);

        //// Draw ESP box (outline)
        //drawList->AddRect(
        //    ImVec2(bounds.left, bounds.top),
        //    ImVec2(bounds.right, bounds.bottom),
        //    IM_COL32(255, 255, 255, (int)(distanceOpacity * 255)),
        //    0.0f,
        //    0,
        //    2.0f
        //);

        // Render player info
        RenderNPCInfo(NPC, drawList, bounds);

        // Render health
        if (config.showHealth) {
            RenderNPCHealth(NPC, drawList, bounds);
        }

        // Render distance
        if (distance > 0.0f) {
            char distText[32];
            sprintf_s(distText, "%.0f", distance);
            ImVec2 distSize = ImGui::CalcTextSize(distText);
            float centerX = (bounds.left + bounds.right) * 0.5f;
            drawList->AddText(
                ImVec2(centerX - distSize.x * 0.5f, bounds.bottom + 4.0f),
                IM_COL32(255, 255, 255, 255),
                distText
            );
        }

        idx++;
    }
}

void ESP::RenderNPCInfo(const NPCInfo& NPC, ImDrawList* drawList, const ESPBounds& bounds) {
    float centerX = (bounds.left + bounds.right) * 0.5f;
    float textGap = 4.0f;

    if (!config.showHealthNPC) {
        // Just show name above the box
        ImVec2 textSize = ImGui::CalcTextSize(NPC.name.c_str());
        drawList->AddText(
            ImVec2(centerX - textSize.x * 0.5f, bounds.top - textSize.y - textGap),
            IM_COL32(255, 255, 255, 255),
            NPC.name.c_str()
        );
    }
}

void ESP::RenderNPCHealth(const NPCInfo& NPC, ImDrawList* drawList, const ESPBounds& bounds) {
    float centerX = (bounds.left + bounds.right) * 0.5f;
    float textGap = 4.0f;
    float currentHealth = NPC.health * NPC.maxHealth;
    ImU32 healthColor = GetHealthColor(NPC.health);

    // Format health text
    char healthText[128];
    if (config.showHealthTextNPC) {
        sprintf_s(healthText, "%s [%d/%d]", NPC.name.c_str(),
            (int)currentHealth, (int)NPC.maxHealth);
    }
    else {
        sprintf_s(healthText, "%s", NPC.name.c_str());
    }
    ImVec2 textSize = ImGui::CalcTextSize(healthText);

    // Draw health text above the box
    drawList->AddText(
        ImVec2(centerX - textSize.x * 0.5f, bounds.top - textSize.y - textGap),
        IM_COL32(255, 255, 255, 255),
        healthText
    );

    // Draw health bar - NOW BELOW THE NICKNAME, ABOVE THE BOX
    if (config.showHealthBarNPC) {
        float barWidth = textSize.x * 0.6;  // Use the actual text width instead of box width
        float barHeight = 6.0f;       // Fixed height for consistent look
        float barX = centerX - barWidth * 0.5f;
        float barY = bounds.top - barHeight + textGap / 2;

        // Background bar
        drawList->AddRectFilled(
            ImVec2(barX, barY),
            ImVec2(barX + barWidth, barY + barHeight),
            IM_COL32(50, 50, 50, 180)
        );

        // Health fill
        float fillWidth = barWidth * NPC.health;
        if (fillWidth > 0.0f) {
            // Inner padding for cleaner look
            float padding = 1.0f;
            drawList->AddRectFilled(
                ImVec2(barX + padding, barY + padding),
                ImVec2(barX + fillWidth - padding, barY + barHeight - padding),
                healthColor
            );
        }

        // Outline
        drawList->AddRect(
            ImVec2(barX, barY),
            ImVec2(barX + barWidth, barY + barHeight),
            IM_COL32(0, 0, 0, 180),
            0.0f,
            0,
            1.0f
        );
    }


    if (config.showArmorTextNPC && NPC.canArmorBreak) {
        char armorValueText[32];
        sprintf_s(armorValueText, "%d/%d", (int)NPC.armor.Value, (int)NPC.armor.MaxValue);
        drawList->AddText(
            ImVec2(bounds.right + 5.0f, bounds.top),
            IM_COL32(255, 255, 255, 255),
            armorValueText
        );
    }
}

//
//
//

//
// CHEST RELATED STUFF
//

void ESP::RenderChests(const std::vector<PlayerInfo>& players, const std::vector<ChestInfo>& chests, ImDrawList* drawList) {
    if (!config.enableChestESP || !w2s || !drawList) return;

    // Find local player for distance calculations
    PlayerInfo localPlayer;
    for (const auto& p : players) {
        if (p.isLocal) {
            localPlayer = p;
            break;
        }
    }

    int idx = 0;
    for (const auto& chest : chests) {
        if (!chest.isValid) continue;
        float distance = 10.0f;
        // Calculate distance / Check distance
        if (localPlayer.isValid) {
            distance = CalculateDistance(chest.Position, localPlayer.headPosition);
        }
        if (distance > config.distChest) continue;

        // Calculate screen positions
        Vector3 Top = chest.Position;
        Top.y += 0.5f;

        Vector3 Bottom = chest.Position;
        Bottom.y -= 0.5f;

        Vector2 head2D = w2s->Project(Top);
        Vector2 root2D = w2s->Project(chest.Position);
        Vector2 foot2D = w2s->Project(Bottom);

        ESPBounds bounds = ComputeBounds(head2D, root2D, foot2D, config.boxSize);
        if (!bounds.valid) continue;

        // Distance-based opacity
        float distanceOpacity = config.opacityChest;
        if (distance > 20.0f) {
            float opacityFactor = 20.0f / distance;
            opacityFactor = (std::max)(0.3f, opacityFactor);
            distanceOpacity = config.opacityChest * opacityFactor;
        }

        // Draw ESP box (filled background)
        ImU32 fillColor;
        fillColor = IM_COL32(0, 0, 0, (int)(distanceOpacity * 0));

        drawList->AddRectFilled(
            ImVec2(bounds.left, bounds.top),
            ImVec2(bounds.right, bounds.bottom),
            fillColor
        );

        // Draw ESP box (outline)
        drawList->AddRect(
            ImVec2(bounds.left, bounds.top),
            ImVec2(bounds.right, bounds.bottom),
            IM_COL32(255, 255, 255, (int)(distanceOpacity * 255)),
            0.0f,
            0,
            2.0f
        );

        // Render player info
        RenderChestInfo(chest, drawList, bounds);

        // Render distance
        if (distance > 0.0f) {
            char distText[32];
            sprintf_s(distText, "%.0f", distance);
            ImVec2 distSize = ImGui::CalcTextSize(distText);
            float centerX = (bounds.left + bounds.right) * 0.5f;
            drawList->AddText(
                ImVec2(centerX - distSize.x * 0.5f, bounds.bottom + 4.0f),
                IM_COL32(255, 255, 255, 255),
                distText
            );
        }

        idx++;
    }
}

void ESP::RenderChestInfo(const ChestInfo& chest, ImDrawList* drawList, const ESPBounds& bounds) {
    float centerX = (bounds.left + bounds.right) * 0.5f;
    float textGap = 4.0f;

    ImVec2 textSize = ImGui::CalcTextSize(chest.name.c_str());
    drawList->AddText(
        ImVec2(centerX - textSize.x * 0.5f, bounds.top - textSize.y - textGap),
        IM_COL32(255, 255, 255, 255),
        chest.name.c_str()
    );
}

//
//
//

//
// GUI
//


void ESP::RenderMenu(bool* p_open) {
    if (!p_open || !*p_open) return;

    ImGui::Begin("what is a tacet", p_open, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::CollapsingHeader("Misc")) {
        ImGui::Checkbox("Auto Fishing", &config.autoFishing);
        ImGui::Checkbox("Auto Cast", &config.autoCast);
        if (config.autoCast) {
            ImGui::SliderInt("Cast Delay", &config.castDelay, 50, 200);
            ImGui::Text("Casting only works with VCZX keys");
        }
        if (config.testFuns) {
            ImGui::Checkbox("Ardour Scream Spam", &config.ardourSpam);
        }
        ImGui::Text("Do not focus on another window or chat during fishing or casting it will type shit");
        ImGui::Text("To be added...");
        ImGui::NewLine();
    }

    if (ImGui::CollapsingHeader("Auto Parry")) {
        ImGui::Text("To be added...");
        ImGui::NewLine();
    }

    if (ImGui::CollapsingHeader("Player ESP")) {
        ImGui::Checkbox("Enable ESP", &config.enableESP);
        ImGui::SliderInt("ESP Distance", &config.dist, 0, 100000);
        ImGui::SliderFloat("ESP Size", &config.boxSize, 100.0f, 140.0f);
        ImGui::SliderFloat("Opacity", &config.opacity, 0.0f, 1.0f);

        ImGui::Separator();
        ImGui::Checkbox("Local Player", &config.showLocalPlayer);
        ImGui::Checkbox("ESP Other Players", &config.showOtherPlayers);
        //ImGui::Checkbox("All Players Mode", &config.allPlayersMode);

        ImGui::Checkbox("Show Health", &config.showHealth);
        if (config.showHealth) {
            ImGui::Indent();
            ImGui::Checkbox("Show Health Bar", &config.showHealthBar);
            if (config.showHealthBar) {
                ImGui::SameLine(); ImGui::Checkbox("Colored Bar", &config.ColoredBar);
            }
            ImGui::Checkbox("Show Health Text", &config.showHealthText);
            ImGui::Unindent();
        }
        ImGui::NewLine();
    }

    if (ImGui::CollapsingHeader("NPC ESP")) {
        ImGui::Checkbox("Enable NPC ESP", &config.enableNPCESP);
        ImGui::Checkbox("Hide Useless", &config.hideUselessNPC);
        ImGui::SliderInt("NPC ESP Distance", &config.distNPC, 100, 5000);
        ImGui::TextDisabled("Distance depends on your roblox Graphics Quality");
        ImGui::Checkbox(" Show Health", &config.showHealthNPC);
        if (config.showHealthNPC) {
            ImGui::Indent();
            ImGui::Checkbox(" Show Health Bar", &config.showHealthBarNPC);
            ImGui::Checkbox(" Show Health Text", &config.showHealthTextNPC);
            ImGui::Unindent();
        }
        ImGui::NewLine();
    }

    if (ImGui::CollapsingHeader("Chest ESP")) {
        ImGui::Checkbox("Enable Chest ESP", &config.enableChestESP);
        ImGui::SliderInt("Chest ESP Distance", &config.distChest, 100, 5000);
        ImGui::TextDisabled("Distance depends on your roblox Graphics Quality");
        ImGui::NewLine();
    }
    if (ImGui::Button("Save config")) {
        GetConfig().save();
    }
    if (ImGui::Button("Load config")) {
        GetConfig().load();
    }

    ImGui::Separator();
    ImGui::Text("Version 1.1.4");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Press INS to toggle menu");
    ImGui::Text("Press END to exit");

    //if (ImGui::Button("Exit")) {
    //    // Signal exit - gotta handle this in main loop // nah scrap it
    //}

    ImGui::End();

    // Player list window
    //if (!config.allPlayersMode) {
    //    ImGui::Begin("Player List", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    //    // Note: Need to store the player list or pass it to this function
    //    ImGui::Text("Individual player toggles will go here later...");
    //    ImGui::Text("Please dont forget to pass player vector to RenderMenu for individual toggles");

    //    ImGui::End();
    //}
}

//
//
//