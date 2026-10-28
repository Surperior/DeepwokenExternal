#pragma once

#include "Notifications.h"

#include <chrono>
#include <ctime>
#include <string>
#include <unordered_map>

namespace EventNotifications
{
    constexpr int GMT_OFFSET_MINUTES = 7 * 60;
    constexpr int MINUTES_PER_DAY = 24 * 60;
    constexpr int NOTIFY_BEFORE_MINUTES = 5;

    struct EventSeries
    {
        const char* name;
        int firstEventMinute;
    };

    constexpr EventSeries events[] =
    {
        { "Carnival of Hearts", 720 },
        { "Interluminary Parasol", 750 },
        { "Battle Royale", 780 }
    };

    inline void Check()
    {
        using namespace std::chrono;

        const auto now = system_clock::now();

        std::time_t referenceTime =
            system_clock::to_time_t(now) + GMT_OFFSET_MINUTES * 60;

        std::tm referenceTm{};

        if (gmtime_s(&referenceTm, &referenceTime) != 0)
            return;

        const int currentMinute =
            referenceTm.tm_hour * 60 + referenceTm.tm_min;

        const int dateKey =
            (referenceTm.tm_year + 1900) * 10000 +
            (referenceTm.tm_mon + 1) * 100 +
            referenceTm.tm_mday;

        // Remember which event series have already notified today.
        static std::unordered_map<std::string, int> lastNotifiedDate;

        for (const auto& event : events)
        {
            // Each event series repeats every 90 minutes.
            // 16 events * 90 minutes = 24 hours.
            for (int i = 0; i < 16; ++i)
            {
                const int eventMinute =
                    (event.firstEventMinute + i * 90)
                    % MINUTES_PER_DAY;

                // Account for events that start just after midnight.
                const int notificationMinute =
                    (eventMinute - NOTIFY_BEFORE_MINUTES
                        + MINUTES_PER_DAY)
                    % MINUTES_PER_DAY;

                if (currentMinute != notificationMinute)
                    continue;

                const std::string key = event.name;

                if (lastNotifiedDate[key] == dateKey)
                    continue;

                lastNotifiedDate[key] = dateKey;

                Notifications::Push(
                    std::string(event.name) + " is starting in 5 minutes!",
                    NotificationType::Warning,
                    30.0f
                );
            }
        }
    }
}