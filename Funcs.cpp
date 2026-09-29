#include "Funcs.h"

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