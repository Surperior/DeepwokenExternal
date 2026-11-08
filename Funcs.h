#pragma once

#include <iostream>
#include <string>
#include "offsets.h"
#include "LogicStructs.h"
#include "g_mem.h"
#include <windows.h>
#include <variant>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

struct MSVCString
{
    union
    {
        char buffer[16];
        uintptr_t data;
    };

    size_t size;
    size_t capacity;
};

static_assert(sizeof(MSVCString) == 0x20);

constexpr size_t MAX_STRING_LENGTH = 4096;

bool ReadRobloxStringV2(uintptr_t address, std::string& output);

struct AttributeValue
{
    enum class Kind { Unknown, String, Bool, Number } kind = Kind::Unknown;

    std::string stringValue;
    bool        boolValue = false;
    double      numberValue = 0.0;

    std::string ToString() const
    {
        switch (kind)
        {
        case Kind::String: return stringValue;
        case Kind::Bool:   return boolValue ? "true" : "false";
        case Kind::Number: {
            // Print integers without a trailing ".0"
            if (numberValue == std::floor(numberValue) &&
                std::abs(numberValue) < 1e15)
            {
                char buf[32];
                std::snprintf(buf, sizeof(buf), "%.0f", numberValue);
                return buf;
            }
            char buf[64];
            std::snprintf(buf, sizeof(buf), "%g", numberValue);
            return buf;
        }
        default: return "<unknown>";
        }
    }
};

struct Attribute
{
    std::string    key;
    AttributeValue value;
};

namespace Offset
{
    constexpr uintptr_t InstanceComponentMap = 0x38;
    constexpr uintptr_t ComponentIdAttributes = 0x9;

    constexpr uintptr_t ComponentIsMap = 0x0;

    constexpr uintptr_t AttributesMapLength = 0x8;
    constexpr uintptr_t AttributesMapEntries = 0x18;

    constexpr uintptr_t AttributesArrayLength = 0x10;
    constexpr uintptr_t AttributesArrayEntries = 0x8;

    constexpr uintptr_t AttributeKey = 0x0;
    constexpr uintptr_t AttributeValue = 0x18;
    constexpr uintptr_t AttributeSize = 0x58;
}

struct ComponentMapEntry
{
    uintptr_t componentData;   // +0x00
    uintptr_t packedId;        // +0x08
};
static_assert(sizeof(ComponentMapEntry) == 0x10);

std::vector<Attribute> ReadAttributes(uintptr_t instance);
Attribute ReadAttribute(uintptr_t instance, std::string attributename);

std::vector<uintptr_t> GetChildren(uintptr_t parent);
std::vector<uintptr_t> GetDescendants(uintptr_t parent);
uintptr_t FindChildByClass(uintptr_t parent, const std::string& class_name);
uintptr_t FindChildByName(uintptr_t parent, const std::string& name);
uintptr_t FindDescendantByName(uintptr_t instance, const std::string& name);
uintptr_t FindDescendantByClass(uintptr_t instance, const std::string& className);
uintptr_t GetInstanceParent(uintptr_t instance);
std::string ReadRobloxString(uintptr_t name_ptr);
std::string GetInstanceName(uintptr_t addr);
std::string GetInstanceClass(uintptr_t addr);

class Instance {
protected:
    uintptr_t address = 0;

public:
    Instance() = default;
    Instance(uintptr_t addr) : address(addr) {}

    // conversions
    operator uintptr_t() const { return address; }
    explicit operator bool() const { return address != 0; }

    uintptr_t get() const { return address; }
    bool valid() const { return address != 0; }

    // comparisons
    bool operator==(const Instance& other) const { return address == other.address; }
    bool operator!=(const Instance& other) const { return address != other.address; }
    bool operator==(uintptr_t other) const { return address == other; }
    bool operator!=(uintptr_t other) const { return address != other; }

    // info storage ig
    //std::string name = ::GetInstanceName(address);
    //std::string iclass = ::GetInstanceClass(address);

    // methods
    std::string class_name() const { return ::GetInstanceClass(address); }
    std::string name() const { return ::GetInstanceName(address); }
    Instance parent() const { return ::GetInstanceParent(address); }
    Instance FindFirstChild(std::string name) const { return ::FindChildByName(address, name); }
    Instance FindFirstChildByClass(std::string class_name) const { return ::FindChildByClass(address, class_name); }
    Instance FindDescendant(std::string name) const { return ::FindDescendantByName(address, name); }
    Instance FindDescendantByClass(std::string class_name) const { return ::FindDescendantByClass(address, class_name); }
    std::vector<uintptr_t> GetChildren() const { return ::GetChildren(address); }
    std::vector<uintptr_t> GetDescendants() const { return ::GetDescendants(address); }
    std::vector<Attribute> attributes() const { auto attributes = ReadAttributes(address); return attributes; }
    Attribute attribute(std::string attributename) const { return ::ReadAttribute(address, attributename); }
};

class Player : public Instance {
public:
    using Instance::Instance;

    Player(const Instance& other) : Instance(other.get()) {}

    Instance character(const Instance& workspace) const
    {
        std::cout << name();
        return workspace.FindFirstChild(name());
    }
};

class Value : public Instance {
public:
    using Instance::Instance;

    Value(const Instance& other) : Instance(other.get()) {}

    using ValueType = std::variant<std::monostate, bool, int, double, std::string, DoubleConstraint>;

    ValueType value() const
    {
        std::string cls = class_name();
        if (cls == "BoolValue") { bool v = g_Memory.Read<bool>(address + Offsets::Misc::Value); return v; }
        else if (cls == "IntValue") { int v = g_Memory.Read<int>(address + Offsets::Misc::Value); return v; }
        else if (cls == "NumberValue") { double v = g_Memory.Read<double>(address + Offsets::Misc::Value); return v; }
        else if (cls == "StringValue") { std::string s = g_Memory.ReadRobloxString(address + Offsets::Misc::Value); return s; }
        else if (cls == "ObjectValue")
        {
            std::string obj = GetInstanceName(address + Offsets::Misc::Value).c_str();
            if (obj != "")
                return obj;
            else
                return "null";
        }
        else if (cls == "DoubleConstrainedValue")
        {
            double max = g_Memory.Read<double>(address + Offsets::Misc::Value);
            double min = g_Memory.Read<double>(address + Offsets::Misc::Value + 0x8);
            double cur = g_Memory.Read<double>(address + Offsets::Misc::Value + 0x10);
            return DoubleConstraint(max, min, cur);
        }
        return std::monostate{};
    }

};

class BasePart : public Instance {
public:
    using Instance::Instance;

    BasePart(const Instance& other) : Instance(other.get()) {}

    bool cancollide() const {

        uintptr_t primitive = g_Memory.ReadPtr(address + Offsets::BasePart::Primitive);

        uintptr_t flagAddress = primitive + Offsets::Primitive::Flags;

        uint32_t flags = g_Memory.Read<uint32_t>(flagAddress);

        return (flags & Offsets::PrimitiveFlags::CanCollide) != 0;
    }
    /*uintptr_t CanCollide(bool wantbool = false) const {
        return address + Offsets::PrimitiveFlags::CanCollide;
    }
    bool SetCanCollide(bool enabled)
    {
        uintptr_t primitive = g_Memory.ReadPtr(address + Offsets::BasePart::Primitive);

        if (!primitive) {
            std::cout << "NO PRIMITIV";
            return false;
        }

        uintptr_t flagsPtr = g_Memory.ReadPtr(primitive + Offsets::Primitive::Flags);

        if (!flagsPtr) {
            std::cout << "NO FLAG";
            return false;
        }

        uintptr_t flags = g_Memory.Read<uintptr_t>(flagsPtr);

        uintptr_t flagAddress2 =
            primitive + Offsets::Primitive::Flags;

        uint32_t flags2 =
            g_Memory.Read<uint32_t>(flagAddress2);

        std::cout << std::hex
            << "Primitive:    0x" << primitive << '\n'
            << "Flag address: 0x" << flagAddress2 << '\n'
            << "Flags:        0x" << flags2 << '\n'
            << std::dec;

        if (enabled)
            flags |= Offsets::PrimitiveFlags::CanCollide;
        else
            flags &= ~Offsets::PrimitiveFlags::CanCollide;

        uint32_t modified = flags2 | Offsets::PrimitiveFlags::CanCollide;

        SetFlags(flagsPtr, modified);

        // Write the modified flags back
        return g_Memory.write<uintptr_t>(flagsPtr, flags);
    }*/
    bool SetCanCollide(bool enabled)
    {
        uintptr_t primitive = g_Memory.ReadPtr(address + Offsets::BasePart::Primitive);

        if (!primitive) {
            std::cout << "NO PRIMITIVE\n";
            return false;
        }

        uintptr_t flagAddress = primitive + Offsets::Primitive::Flags;

        uint32_t flags = g_Memory.Read<uint32_t>(flagAddress);

        uint32_t oldFlags = flags;

        if (enabled)
            flags |= static_cast<uint32_t>(Offsets::PrimitiveFlags::CanCollide);
        else
            flags &= ~static_cast<uint32_t>(Offsets::PrimitiveFlags::CanCollide);

        if (!g_Memory.write<uint32_t>(flagAddress, flags)) {
            std::cout << "Write failed\n";
            return false;
        }

        uint32_t verify =
            g_Memory.Read<uint32_t>(flagAddress);


        return verify == flags;
    }

    bool anchored() const {

        uintptr_t primitive = g_Memory.ReadPtr(address + Offsets::BasePart::Primitive);

        uintptr_t flagAddress = primitive + Offsets::Primitive::Flags;

        uint32_t flags = g_Memory.Read<uint32_t>(flagAddress);

        return (flags & Offsets::PrimitiveFlags::Anchored) != 0;
    }

    bool SetAnchored(bool enabled)
    {
        uintptr_t primitive = g_Memory.ReadPtr(address + Offsets::BasePart::Primitive);

        if (!primitive) {
            std::cout << "NO PRIMITIVE\n";
            return false;
        }

        uintptr_t flagAddress = primitive + Offsets::Primitive::Flags;

        uint32_t flags = g_Memory.Read<uint32_t>(flagAddress);

        uint32_t oldFlags = flags;

        if (enabled)
            flags |= static_cast<uint32_t>(Offsets::PrimitiveFlags::Anchored);
        else
            flags &= ~static_cast<uint32_t>(Offsets::PrimitiveFlags::Anchored);

        if (!g_Memory.write<uint32_t>(flagAddress, flags)) {
            std::cout << "Write failed\n";
            return false;
        }

        uint32_t verify =
            g_Memory.Read<uint32_t>(flagAddress);


        return verify == flags;
    }

    float transparency() const {
        return g_Memory.ReadFloat(address + Offsets::BasePart::Transparency);
    }

    bool castShadow() const {
        return g_Memory.ReadBool(address + Offsets::BasePart::CastShadow);
    }

    Vector3 position() const {
        uintptr_t primitive = g_Memory.ReadPtr(address + Offsets::BasePart::Primitive);
        return g_Memory.ReadVector3(primitive + Offsets::Primitive::Position);
    }

    Vector3 color() const {
        return g_Memory.ReadVector3(address + Offsets::BasePart::Color3);
    }
};
