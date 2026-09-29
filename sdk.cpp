#include "sdk.h"
#include "Offsets.h"
namespace rbx
{
    std::string instance_t::name() const
    {
        if (!is_valid()) return {};
        auto name_ptr = Memory->read<std::uintptr_t>(address + Offsets::Instance::Name);
        if (!name_ptr) return {};
        return Memory->read_string(name_ptr);
    }
    std::string instance_t::class_name() const
    {
        if (!is_valid()) return {};
        auto class_desc = Memory->read<std::uintptr_t>(address + Offsets::Instance::ClassDescriptor);
        if (!class_desc) return {};
        auto name_ptr = Memory->read<std::uintptr_t>(class_desc + Offsets::Instance::ClassDescriptorToClassName);
        if (!name_ptr) return {};
        return Memory->read_string(name_ptr);
    }
    instance_t instance_t::parent() const
    {
        if (!is_valid()) return {};
        return instance_t(Memory->read<std::uintptr_t>(address + Offsets::Instance::Parent));
    }
    std::vector<instance_t> instance_t::children() const
    {
        std::vector<instance_t> result;
        if (!is_valid()) return result;
        auto children_start = Memory->read<std::uintptr_t>(address + Offsets::Instance::ChildrenStart);
        if (!children_start) return result;
        auto children_end = Memory->read<std::uintptr_t>(children_start + Offsets::Instance::ChildrenEnd);
        if (!children_end) return result;
        result.reserve(32);
        int count = 0;
        for (auto child = Memory->read<std::uintptr_t>(children_start);
             child != children_end && count < 100000; child += 0x10, count++)
        {
            auto child_addr = Memory->read<std::uintptr_t>(child);
            if (child_addr)
                result.emplace_back(child_addr);
        }
        return result;
    }
    instance_t instance_t::find_first_child(const std::string& target_name) const
    {
        for (const auto& child : children())
        {
            if (child.name() == target_name)
                return child;
        }
        return {};
    }
    instance_t instance_t::find_first_child_of_class(const std::string& target_class) const
    {
        for (const auto& child : children())
        {
            if (child.class_name() == target_class)
                return child;
        }
        return {};
    }
    types::vector3_t instance_t::position() const
    {
        if (!is_valid()) return {};
        auto primitive = Memory->read<std::uintptr_t>(address + Offsets::BasePart::Primitive);
        if (!primitive) return {};
        return Memory->read<types::vector3_t>(primitive + Offsets::Primitive::Position);
    }  
}

