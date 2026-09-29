#pragma once

#include <iostream>
#include <string>
#include "offsets.h"
#include "LogicStructs.h"
#include "g_mem.h"
#include <windows.h>
#include <variant>

std::vector<uintptr_t> GetChildren(uintptr_t parent);
std::vector<uintptr_t> GetDescendants(uintptr_t parent);
uintptr_t FindChildByClass(uintptr_t parent, const std::string& class_name);
uintptr_t FindChildByName(uintptr_t parent, const std::string& name);
uintptr_t FindDescendantByName(uintptr_t instance, const std::string& name);
uintptr_t FindDescendantByClass(uintptr_t instance, const std::string& className);
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
    std::string GetClass() const { return ::GetInstanceClass(address); }
    std::string GetName() const { return ::GetInstanceName(address); }
    uintptr_t FindFirstChild(std::string name) const { return ::FindChildByName(address, name); }
    uintptr_t FindFirstChildByClass(std::string class_name) const { return ::FindChildByClass(address, class_name); }
    uintptr_t FindDescendant(std::string name) const { return ::FindDescendantByName(address, name); }
    uintptr_t FindDescendantByClass(std::string class_name) const { return ::FindDescendantByClass(address, class_name); }
    std::vector<uintptr_t> GetChildren() const { return ::GetChildren(address); }
    std::vector<uintptr_t> GetDescendants() const { return ::GetDescendants(address); }

};

class Player : public Instance {
public:
    using Instance::Instance;

    Player(const Instance& other) : Instance(other.get()) {}

    Instance Character(const Instance& live) const
    {
        std::cout << GetName();
        return live.FindFirstChild(GetName());
    }
};

class Value : public Instance {
public:
    using Instance::Instance;

    Value(const Instance& other) : Instance(other.get()) {}

    using ValueType = std::variant<std::monostate, bool, int, double, std::string, DoubleConstraint>;

    ValueType value() const
    {
        std::string cls = GetClass();
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

    Vector3 Position() const {
        uintptr_t primitive = g_Memory.ReadPtr(address + Offsets::BasePart::Primitive);
        return g_Memory.ReadVector3(primitive + Offsets::Primitive::Position);
    }

    bool CanCollide() const {

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

    bool Anchored() const {

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

    float Transparency() const {
        return g_Memory.ReadFloat(address + Offsets::BasePart::Transparency);
    }

    bool CastShadow() const {
        return g_Memory.ReadBool(address + Offsets::BasePart::CastShadow);
    }
};