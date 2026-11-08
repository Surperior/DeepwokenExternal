#include "Funcs.h"
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <unordered_set>

struct RobloxString
{
    union
    {
        char      buffer[16];
        uintptr_t ptr;
    };                 // +0x00
    size_t length;     // +0x10
    size_t capacity;   // +0x18
};
static_assert(sizeof(RobloxString) == 0x20);

static inline bool IsShortString(const RobloxString& s)
{
    return s.capacity < 16;
}

bool ReadRobloxStringV2(uintptr_t address, std::string& output)
{
    RobloxString s{};
    if (!g_Memory.ReadRaw(address, &s, sizeof(s)))
        return false;

    if (s.length > MAX_STRING_LENGTH)
        return false;

    if (s.length == 0)
    {
        output.clear();
        return true;
    }

    if (IsShortString(s))
    {
        output.assign(s.buffer, s.length);
        return true;
    }

    if (!s.ptr)
        return false;

    output.resize(s.length);
    if (!g_Memory.ReadRaw(s.ptr, output.data(), s.length))
    {
        output.clear();
        return false;
    }

    return true;
}

static bool TryReadStringSlot(uintptr_t slotAddress, std::string& out)
{
    RobloxString probe{};
    if (!g_Memory.ReadRaw(slotAddress, &probe, sizeof(probe)))
        return false;

    if (probe.length == 0 || probe.length > MAX_STRING_LENGTH)
        return false;

    if (probe.capacity >= 16) {
        if (!probe.ptr) return false;
        if (probe.ptr > 0x00007FFFFFFFFFFFULL) return false;
    }

    std::string tmp;
    if (!ReadRobloxStringV2(slotAddress, tmp))
        return false;

    for (unsigned char c : tmp) {
        if (c < 0x20 && c != '\t' && c != '\n' && c != '\r')
            return false;
    }

    out = std::move(tmp);
    return true;
}

static void ReadAttributeValue(uintptr_t slotAddress, AttributeValue& out)
{
    // 1) String
    {
        std::string s;
        if (TryReadStringSlot(slotAddress, s)) {
            out.kind = AttributeValue::Kind::String;
            out.stringValue = std::move(s);
            return;
        }
    }

    // 2) Bool
    {
        uint64_t raw = 0;
        if (g_Memory.ReadRaw(slotAddress, &raw, sizeof(raw))) {
            uint8_t b = static_cast<uint8_t>(raw & 0xFF);
            if ((b == 0 || b == 1) && (raw >> 8) == 0) {
                out.kind = AttributeValue::Kind::Bool;
                out.boolValue = (b != 0);
                return;
            }
        }
    }

    // 3) Number
    {
        double d = 0.0;
        if (g_Memory.ReadRaw(slotAddress, &d, sizeof(d)) &&
            std::isfinite(d) && std::abs(d) < 1e15)
        {
            out.kind = AttributeValue::Kind::Number;
            out.numberValue = d;
            return;
        }
    }
    {
        float f = 0.0f;
        if (g_Memory.ReadRaw(slotAddress, &f, sizeof(f)) &&
            std::isfinite(f) && std::abs(f) < 1e15f)
        {
            out.kind = AttributeValue::Kind::Number;
            out.numberValue = static_cast<double>(f);
            return;
        }
    }
    {
        int32_t i = 0;
        if (g_Memory.ReadRaw(slotAddress, &i, sizeof(i))) {
            out.kind = AttributeValue::Kind::Number;
            out.numberValue = static_cast<double>(i);
            return;
        }
    }

    out.kind = AttributeValue::Kind::Unknown;
}


Attribute ReadAttribute(uintptr_t instance, std::string attributename)
{
    Attribute result;
    if (!instance) return result;

    uintptr_t vecPtr = 0;
    if (!g_Memory.ReadRaw(instance + Offset::InstanceComponentMap, &vecPtr, sizeof(vecPtr)))
        return result;
    if (!vecPtr) return result;

    uintptr_t vecBegin = 0, vecEnd = 0;
    if (!g_Memory.ReadRaw(vecPtr, &vecBegin, sizeof(vecBegin))) return result;
    if (!g_Memory.ReadRaw(vecPtr + sizeof(uintptr_t), &vecEnd, sizeof(vecEnd))) return result;
    if (vecBegin == 0 || vecEnd <= vecBegin) return result;

    const size_t entryStride = sizeof(ComponentMapEntry);
    const size_t count = (vecEnd - vecBegin) / entryStride;
    if (count > 4096) return result;

    uintptr_t attributesComponent = 0;
    for (size_t i = 0; i < count; ++i)
    {
        ComponentMapEntry e{};
        if (!g_Memory.ReadRaw(vecBegin + i * entryStride, &e, sizeof(e)))
            continue;
        if (static_cast<uint16_t>(e.packedId & 0xFFFF) == Offset::ComponentIdAttributes)
        {
            attributesComponent = e.componentData;
            break;
        }
    }
    if (!attributesComponent) return result;

    uint8_t isMap = 0;
    if (!g_Memory.ReadRaw(attributesComponent + Offset::ComponentIsMap, &isMap, sizeof(isMap)))
        return result;

    uint32_t length = 0;
    uintptr_t entries = 0;

    const uintptr_t lenOff = isMap ? Offset::AttributesMapLength : Offset::AttributesArrayLength;
    const uintptr_t arrOff = isMap ? Offset::AttributesMapEntries : Offset::AttributesArrayEntries;

    if (!g_Memory.ReadRaw(attributesComponent + lenOff, &length, sizeof(length))) return result;
    if (length == 0 || length > 4096) return result;
    if (!g_Memory.ReadRaw(attributesComponent + arrOff, &entries, sizeof(entries))) return result;
    if (!entries) return result;

    for (uint32_t i = 0; i < length; ++i)
    {
        const uintptr_t entryAddress = entries + (uintptr_t)i * Offset::AttributeSize;

        Attribute attribute;

        uintptr_t viewAddress = 0;
        if (!g_Memory.ReadRaw(entryAddress + Offset::AttributeKey, &viewAddress, sizeof(viewAddress)))
            continue;
        if (!viewAddress || !ReadRobloxStringV2(viewAddress, attribute.key))
            continue;
        if (attribute.key != attributename) continue;

        ReadAttributeValue(entryAddress + Offset::AttributeValue, attribute.value);

        result = attribute;
    }

    return result;
}

std::vector<Attribute> ReadAttributes(uintptr_t instance)
{
    std::vector<Attribute> result;
    if (!instance) return result;

    uintptr_t vecPtr = 0;
    if (!g_Memory.ReadRaw(instance + Offset::InstanceComponentMap, &vecPtr, sizeof(vecPtr)))
        return result;
    if (!vecPtr) return result;

    uintptr_t vecBegin = 0, vecEnd = 0;
    if (!g_Memory.ReadRaw(vecPtr, &vecBegin, sizeof(vecBegin))) return result;
    if (!g_Memory.ReadRaw(vecPtr + sizeof(uintptr_t), &vecEnd, sizeof(vecEnd))) return result;
    if (vecBegin == 0 || vecEnd <= vecBegin) return result;

    const size_t entryStride = sizeof(ComponentMapEntry);
    const size_t count = (vecEnd - vecBegin) / entryStride;
    if (count > 4096) return result;

    uintptr_t attributesComponent = 0;
    for (size_t i = 0; i < count; ++i)
    {
        ComponentMapEntry e{};
        if (!g_Memory.ReadRaw(vecBegin + i * entryStride, &e, sizeof(e)))
            continue;
        if (static_cast<uint16_t>(e.packedId & 0xFFFF) == Offset::ComponentIdAttributes)
        {
            attributesComponent = e.componentData;
            break;
        }
    }
    if (!attributesComponent) return result;

    uint8_t isMap = 0;
    if (!g_Memory.ReadRaw(attributesComponent + Offset::ComponentIsMap, &isMap, sizeof(isMap)))
        return result;

    uint32_t length = 0;
    uintptr_t entries = 0;

    const uintptr_t lenOff = isMap ? Offset::AttributesMapLength : Offset::AttributesArrayLength;
    const uintptr_t arrOff = isMap ? Offset::AttributesMapEntries : Offset::AttributesArrayEntries;

    if (!g_Memory.ReadRaw(attributesComponent + lenOff, &length, sizeof(length))) return result;
    if (length == 0 || length > 4096) return result;
    if (!g_Memory.ReadRaw(attributesComponent + arrOff, &entries, sizeof(entries))) return result;
    if (!entries) return result;

    for (uint32_t i = 0; i < length; ++i)
    {
        const uintptr_t entryAddress = entries + (uintptr_t)i * Offset::AttributeSize;

        Attribute attribute;

        uintptr_t viewAddress = 0;
        if (!g_Memory.ReadRaw(entryAddress + Offset::AttributeKey, &viewAddress, sizeof(viewAddress)))
            continue;
        if (!viewAddress || !ReadRobloxStringV2(viewAddress, attribute.key))
            continue;

        ReadAttributeValue(entryAddress + Offset::AttributeValue, attribute.value);

        result.push_back(std::move(attribute));
    }

    return result;
}

std::vector<uintptr_t> GetChildren(uintptr_t parent)
{
    std::vector<uintptr_t> result;

    if (!parent)
        return result;


    auto start =
        g_Memory.ReadPtr(
            parent +
            Offsets::Instance::ChildrenStart);

    if (!start)
        return result;


    auto end =
        g_Memory.ReadPtr(
            start +
            Offsets::Instance::ChildrenEnd);


    if (!end)
        return result;



    for (uintptr_t ptr =
        g_Memory.ReadPtr(start);

        ptr != end;

        ptr += 0x10)
    {

        auto child =
            g_Memory.ReadPtr(ptr);

        if (child)
            result.push_back(child);

    }


    return result;
}

std::vector<uintptr_t> GetDescendants(uintptr_t parent)
{
    std::vector<uintptr_t> result;
    if (!parent)
        return result;

    auto children = GetChildren(parent);

    for (uintptr_t child : children)
    {
        result.push_back(child);

        auto deeper = GetDescendants(child);
        result.insert(result.end(), deeper.begin(), deeper.end());
    }

    return result;
}

uintptr_t FindChildByClass(uintptr_t parent, const std::string& class_name) {
    if (!parent) return 0;

    uintptr_t children_start = g_Memory.ReadPtr(parent + Offsets::Instance::ChildrenStart);
    if (!children_start) return 0;

    uintptr_t children_end = g_Memory.ReadPtr(children_start + Offsets::Instance::ChildrenEnd);
    if (!children_end) return 0;

    for (uintptr_t ptr = g_Memory.ReadPtr(children_start);
        ptr != children_end && ptr != 0; ptr += 0x10) {

        uintptr_t child = g_Memory.ReadPtr(ptr);
        if (!child) continue;

        if (GetInstanceClass(child) == class_name)
            return child;
    }
    return 0;
}

uintptr_t FindChildByName(uintptr_t parent, const std::string& name) {
    if (!parent) return 0;

    uintptr_t children_start = g_Memory.ReadPtr(parent + Offsets::Instance::ChildrenStart);
    if (!children_start) return 0;

    uintptr_t children_end = g_Memory.ReadPtr(children_start + Offsets::Instance::ChildrenEnd);
    if (!children_end) return 0;

    for (uintptr_t ptr = g_Memory.ReadPtr(children_start);
        ptr != children_end && ptr != 0; ptr += 0x10) {

        uintptr_t child = g_Memory.ReadPtr(ptr);
        if (!child) continue;

        if (GetInstanceName(child) == name)
            return child;
    }
    return 0;
}

uintptr_t FindDescendantByName(uintptr_t instance, const std::string& name)
{
    if (!instance)
        return 0;

    uintptr_t childrenStart = g_Memory.ReadPtr(instance + Offsets::Instance::ChildrenStart);
    if (!childrenStart)
        return 0;

    uintptr_t childrenEnd = g_Memory.ReadPtr(childrenStart + Offsets::Instance::ChildrenEnd);
    if (!childrenEnd)
        return 0;

    for (uintptr_t ptr = g_Memory.ReadPtr(childrenStart);
        ptr != childrenEnd;
        ptr += 0x10)
    {
        uintptr_t child = g_Memory.ReadPtr(ptr);
        if (!child)
            continue;

        if (GetInstanceName(child) == name)
            return child;

        uintptr_t result = FindDescendantByName(child, name);
        if (result)
            return result;
    }

    return 0;
}

uintptr_t FindDescendantByClass(uintptr_t instance, const std::string& className)
{
    if (!instance)
        return 0;

    uintptr_t childrenStart = g_Memory.ReadPtr(instance + Offsets::Instance::ChildrenStart);
    if (!childrenStart)
        return 0;

    uintptr_t childrenEnd = g_Memory.ReadPtr(childrenStart + Offsets::Instance::ChildrenEnd);
    if (!childrenEnd)
        return 0;

    for (uintptr_t ptr = g_Memory.ReadPtr(childrenStart);
        ptr != childrenEnd;
        ptr += 0x10)
    {
        uintptr_t child = g_Memory.ReadPtr(ptr);
        if (!child)
            continue;

        if (GetInstanceClass(child) == className)
            return child;

        uintptr_t result = FindDescendantByClass(child, className);
        if (result)
            return result;
    }

    return 0;
}

uintptr_t GetInstanceParent(uintptr_t instance) {
    return g_Memory.ReadPtr(instance + Offsets::Instance::Parent);
}

std::string ReadRobloxString(uintptr_t name_ptr)
{

    return g_Memory.ReadRobloxString(name_ptr);
}

std::string GetInstanceName(uintptr_t addr) {
    if (!addr) return "<null>";
    uintptr_t namec_ptr = g_Memory.ReadPtr(addr + Offsets::Instance::NameContainer);
    uintptr_t name_ptr = namec_ptr + Offsets::Instance::Name;

    return ReadRobloxString(name_ptr);
}

std::string GetInstanceClass(uintptr_t addr) {
    if (!addr) return "<null>";
    uintptr_t desc = g_Memory.ReadPtr(addr + Offsets::Instance::ClassDescriptor);
    if (!desc) return "<null>";
    uintptr_t name_ptr = g_Memory.ReadPtr(desc + Offsets::Instance::ClassDescriptorToClassName);
    return ReadRobloxString(name_ptr);
}
