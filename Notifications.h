#pragma once

#include <imgui.h>
#include <vector>
#include <string>
#include <algorithm>
#undef min
#undef max

enum class NotificationType
{
    Info,
    Success,
    Warning,
    Error
};

struct Notification
{
    std::string message;
    NotificationType type;
    float duration;
    float elapsed;
};

namespace Notifications
{
    inline std::vector<Notification> queue;

    inline void Push(
        const std::string& message,
        NotificationType type = NotificationType::Info,
        float duration = 3.0f)
    {
        queue.push_back({ message, type, duration, 0.0f });
    }

    inline ImU32 GetColor(NotificationType type)
    {
        switch (type)
        {
        case NotificationType::Success:
            return IM_COL32(80, 220, 130, 255);

        case NotificationType::Warning:
            return IM_COL32(255, 190, 70, 255);

        case NotificationType::Error:
            return IM_COL32(255, 85, 95, 255);

        default:
            return IM_COL32(150, 100, 255, 255);
        }
    }

    inline void Render()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImDrawList* draw = ImGui::GetForegroundDrawList();

        const float width = 300.0f;
        const float height = 32.0f;
        const float spacing = 10.0f;
        const float margin = 20.0f;

        float yOffset = margin;

        // Iterate backwards so expired entries can be removed safely.
        for (int i = static_cast<int>(queue.size()) - 1; i >= 0; --i)
        {
            auto& n = queue[i];
            n.elapsed += io.DeltaTime;

            if (n.elapsed >= n.duration + 0.35f)
            {
                queue.erase(queue.begin() + i);
                continue;
            }
        }

        // Draw oldest notification at the bottom.
        for (int i = 0; i < static_cast<int>(queue.size()); ++i)
        {
            auto& n = queue[i];

            const float fadeIn = std::clamp(n.elapsed / 0.2f, 0.0f, 1.0f);
            const float fadeOut = std::clamp(
                (n.duration + 0.35f - n.elapsed) / 0.35f,
                0.0f, 1.0f);

            const float alpha = (std::min)(fadeIn, fadeOut);

            // Screen-space position: bottom-right.
            ImVec2 pos(
                io.DisplaySize.x - width - margin,
                io.DisplaySize.y - height - yOffset
            );

            // Slide in from the right.
            pos.x += (1.0f - fadeIn) * 35.0f;

            const int a = static_cast<int>(255.0f * alpha);

            const ImU32 background =
                IM_COL32(22, 22, 30, static_cast<int>(230 * alpha));

            const ImU32 accent = GetColor(n.type);
            const ImU32 accentWithAlpha =
                (accent & 0x00FFFFFF) | (static_cast<ImU32>(a) << 24);

            // Shadow.
            draw->AddRectFilled(
                ImVec2(pos.x + 3, pos.y + 3),
                ImVec2(pos.x + width + 3, pos.y + height + 3),
                IM_COL32(0, 0, 0, static_cast<int>(90 * alpha)),
                10.0f
            );

            // Main card.
            draw->AddRectFilled(
                pos,
                ImVec2(pos.x + width, pos.y + height),
                background,
                10.0f
            );

            // Colored accent bar.
            draw->AddRectFilled(
                pos,
                ImVec2(pos.x + 4, pos.y + height),
                accentWithAlpha,
                3.0f
            );

            // Notification text.
            draw->AddText(
                ImVec2(pos.x + 16, pos.y + 11),
                IM_COL32(245, 245, 250, a),
                n.message.c_str()
            );

            yOffset += height + spacing;
        }
    }
}