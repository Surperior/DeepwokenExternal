#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "memory.h"
#include "types.h"
namespace rbx
{
    using visualengine_t = std::uintptr_t;
    using camera_t = std::uintptr_t;
    class instance_t
    {
    public:
        std::uintptr_t address = 0;
        instance_t() = default;
        explicit instance_t(std::uintptr_t addr) : address(addr) {}
        [[nodiscard]] bool is_valid() const { return address != 0; }
        explicit operator bool() const { return is_valid(); }
        [[nodiscard]] std::string          name() const;
        [[nodiscard]] std::string          class_name() const;
        [[nodiscard]] instance_t           parent() const;
        [[nodiscard]] std::vector<instance_t> children() const;
        [[nodiscard]] instance_t find_first_child(const std::string& name) const;
        [[nodiscard]] instance_t find_first_child_of_class(const std::string& class_name) const;
        [[nodiscard]] types::matrix4_t     cframe() const;
        [[nodiscard]] types::vector3_t     position() const;
        [[nodiscard]] types::vector3_t     size() const;
        [[nodiscard]] types::vector3_t     velocity() const;
        bool operator==(const instance_t& other) const { return address == other.address; }
        bool operator!=(const instance_t& other) const { return address != other.address; }
    };
    struct player_data_t
    {
        std::uintptr_t address = 0;
        std::string    name;
        std::string    display_name;
        std::string    tool_name;
        int            rig_type = 0;
        int            humanoid_state = 8;
        float          health = 0.f;
        float          max_health = 0.f;
        std::uintptr_t team = 0;
        std::string    team_name;
        struct { float r = 1.f, g = 1.f, b = 1.f; } team_color;
        instance_t     character;
        instance_t     humanoid;
        instance_t     root_part;
        instance_t     head;
        instance_t     torso;
        instance_t     left_arm;
        instance_t     right_arm;
        instance_t     left_leg;
        instance_t     right_leg;
        instance_t     upper_torso;
        instance_t     lower_torso;
        instance_t     left_upper_arm;
        instance_t     left_lower_arm;
        instance_t     left_hand;
        instance_t     right_upper_arm;
        instance_t     right_lower_arm;
        instance_t     right_hand;
        instance_t     left_upper_leg;
        instance_t     left_lower_leg;
        instance_t     left_foot;
        instance_t     right_upper_leg;
        instance_t     right_lower_leg;
        instance_t     right_foot;
    };
    struct vehicle_data_t
    {
        std::uintptr_t address = 0;
        std::string    name;
        std::string    short_name;
        std::string    owner;
        std::string    license_plate;
        bool           is_emergency = false;
        instance_t     collision_part;
    };
}

