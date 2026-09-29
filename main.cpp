//
//        PRAISE THE CODE
//
//       Nel Nome Del Codice
//
//  The Code Shall Be Open For All
//      My code is your code
//

#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS

//
// # Basic Includes
//

#include <windows.h>
#include <winhttp.h>
#include <d3d11.h>
#include <iostream>
#include <stdio.h>
#include <TlHelp32.h>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <psapi.h>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <atomic>
#include <fstream>

//
// # Insides Includes
//

#include "LogicStructs.h" // LOGIC STRUCTURES eg. Vector
#include "Funcs.h" // Basic Functions eg. FindChild
#include "g_mem.h" // g_Memory
#include "sdk.h" // Unused???
#include "ESP.h" // Esp engine
#include "NpcNames.h" // Npc Bestiary

//
// # prag
//

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "winhttp.lib")

//
// # GUI LIBRARY
//

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

//
// # OFFSETS
//

#include "offsets.h"
#include "Soffsets.h"

//
//
//

//
// GitHub stuff pulling
//

const char* gitpat = getenv("GITPAT");

std::unordered_map<std::string, std::string> NPCNames;

std::unordered_map<std::string, std::string> UselessNPCs;

std::string DownloadOffsets()
{
    const wchar_t* host = L"api.github.com";
    const wchar_t* path = L"/repos/Surperior/External/contents/offsets.h";

    HINTERNET hSession =
        WinHttpOpen(L"MyProgram/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            0);

    if (!hSession)
        return "";

    HINTERNET hConnect =
        WinHttpConnect(hSession, host,
            INTERNET_DEFAULT_HTTPS_PORT, 0);

    if (!hConnect)
    {
        WinHttpCloseHandle(hSession);
        return "";
    }

    HINTERNET hRequest =
        WinHttpOpenRequest(hConnect,
            L"GET",
            path,
            nullptr,
            WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            WINHTTP_FLAG_SECURE);

    if (!hRequest)
        return "";

    std::wstring headers =
        L"Authorization: Bearer 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\r\n"
        L"Accept: application/vnd.github.raw\r\n"
        L"X-GitHub-Api-Version: 2022-11-28\r\n"
        L"User-Agent: ViewX\r\n";

    WinHttpAddRequestHeaders(
        hRequest,
        headers.c_str(),
        (ULONG)-1L,
        WINHTTP_ADDREQ_FLAG_ADD);

    BOOL ok = WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        0,
        0);

    if (!ok)
        return "";

    ok = WinHttpReceiveResponse(hRequest, nullptr);

    if (!ok)
        return "";

    std::string response;

    while (true)
    {
        DWORD available = 0;

        WinHttpQueryDataAvailable(hRequest, &available);

        if (available == 0)
            break;

        std::vector<char> buffer(available);

        DWORD read = 0;

        WinHttpReadData(
            hRequest,
            buffer.data(),
            available,
            &read);

        response.append(buffer.data(), read);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return response;
}

std::string DownloadNPCNames()
{
    const wchar_t* host = L"api.github.com";
    const wchar_t* path = L"/repos/Surperior/External/contents/NpcNames.h";

    HINTERNET hSession =
        WinHttpOpen(L"MyProgram/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            0);

    if (!hSession)
        return "";

    HINTERNET hConnect =
        WinHttpConnect(hSession, host,
            INTERNET_DEFAULT_HTTPS_PORT, 0);

    if (!hConnect)
    {
        WinHttpCloseHandle(hSession);
        return "";
    }

    HINTERNET hRequest =
        WinHttpOpenRequest(hConnect,
            L"GET",
            path,
            nullptr,
            WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            WINHTTP_FLAG_SECURE);

    if (!hRequest)
        return "";

    std::wstring headers =
        L"Authorization: Bearer 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\r\n"
        L"Accept: application/vnd.github.raw\r\n"
        L"X-GitHub-Api-Version: 2022-11-28\r\n"
        L"User-Agent: ViewX\r\n";

    WinHttpAddRequestHeaders(
        hRequest,
        headers.c_str(),
        (ULONG)-1L,
        WINHTTP_ADDREQ_FLAG_ADD);

    BOOL ok = WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        0,
        0);

    if (!ok)
        return "";

    ok = WinHttpReceiveResponse(hRequest, nullptr);

    if (!ok)
        return "";

    std::string response;

    while (true)
    {
        DWORD available = 0;

        WinHttpQueryDataAvailable(hRequest, &available);

        if (available == 0)
            break;

        std::vector<char> buffer(available);

        DWORD read = 0;

        WinHttpReadData(
            hRequest,
            buffer.data(),
            available,
            &read);

        response.append(buffer.data(), read);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return response;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

bool starts_with(const std::string& str, const std::string& prefix) {
    if (str.size() < prefix.size()) return false;
    return str.compare(0, prefix.size(), prefix) == 0;
}

bool LoadOffsets(const std::string& text) {
    std::istringstream iss(text);
    std::string line;
    std::string currentNamespace = "";

    while (std::getline(iss, line)) {
        line = trim(line);
        if (line.empty()) continue;

        // Skip comments
        if (starts_with(line, "//") || starts_with(line, "/*"))
            continue;

        // Detect namespace
        if (starts_with(line, "namespace ")) {
            size_t start = line.find("namespace ") + 10;
            size_t end = line.find('{', start);
            if (end != std::string::npos) {
                currentNamespace = trim(line.substr(start, end - start));
            }
            continue;
        }

        // Parse offset line:   inline  uintptr_t Name = 0x12345678;
        if (line.find("uintptr_t") != std::string::npos &&
            line.find('=') != std::string::npos) {

            size_t eqPos = line.find('=');
            std::string leftPart = trim(line.substr(0, eqPos));
            std::string rightPart = trim(line.substr(eqPos + 1));

            // Remove trailing semicolon
            if (!rightPart.empty() && rightPart.back() == ';')
                rightPart.pop_back();

            rightPart = trim(rightPart);

            // Extract variable name (last word in left part)
            size_t lastSpace = leftPart.find_last_of(" \t");
            if (lastSpace == std::string::npos) continue;

            std::string varName = trim(leftPart.substr(lastSpace + 1));

            // Convert value
            uintptr_t value = 0;
            if (starts_with(rightPart, "0x")) {
                value = std::stoull(rightPart, nullptr, 16);
            }
            else {
                value = std::stoull(rightPart);
            }

            // Apply the offset
            SetOffset(currentNamespace, varName, value);
        }
    }

    return true;
}

bool LoadNPCNames(const std::string& text)
{
    std::istringstream iss(text);
    std::string line;
    bool inNPCNames = false;
    bool inUselessNPCs = false;

    while (std::getline(iss, line))
    {
        line = trim(line);

        if (line.empty()) continue;

        // Detect which map we're in
        if (line.find("NPCNames") != std::string::npos && line.find("=") != std::string::npos)
            inNPCNames = true;
        else if (line.find("UselessNPCs") != std::string::npos && line.find("=") != std::string::npos)
            inUselessNPCs = true;

        if (line.find("};") != std::string::npos)
        {
            inNPCNames = false;
            inUselessNPCs = false;
            continue;
        }

        // Look for lines that look like:     {".key", "Value"},
        if (line.find('"') == std::string::npos) continue;

        // Find the two quoted strings
        size_t firstQuote = line.find('"');
        if (firstQuote == std::string::npos) continue;

        size_t secondQuote = line.find('"', firstQuote + 1);
        if (secondQuote == std::string::npos) continue;

        size_t thirdQuote = line.find('"', secondQuote + 1);
        if (thirdQuote == std::string::npos) continue;

        size_t fourthQuote = line.find('"', thirdQuote + 1);
        if (fourthQuote == std::string::npos) continue;

        std::string key = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
        std::string value = line.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);

        if (inNPCNames)
        {
            NPCNames[key] = value;
            // std::cout << "[NPC] " << key << " -> " << value << std::endl;  // debug
        }
        else if (inUselessNPCs)
        {
            UselessNPCs[key] = value;
            // std::cout << "[Useless] " << key << " -> " << value << std::endl; // debug
        }
    }

    // Final check
    if (NPCNames.empty() && UselessNPCs.empty())
        return false;

    return true;
}

auto DOWOFF = DownloadOffsets();

auto DOWNN = DownloadNPCNames();

//
//
//

struct FPSCounter
{
    int frames = 0;
    float fps = 0.0f;
    std::chrono::steady_clock::time_point lastUpdate =
        std::chrono::steady_clock::now();

    void tick()
    {
        frames++;

        auto now = std::chrono::steady_clock::now();
        float elapsed =
            std::chrono::duration<float>(now - lastUpdate).count();

        if (elapsed >= 1.0f)
        {
            fps = frames / elapsed;
            frames = 0;
            lastUpdate = now;
        }
    }
};

FPSCounter g_espFPS;
FPSCounter g_guiFPS;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcEsp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcGui(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool CreateDeviceD3D(HWND hWnd, HWND hWnd2);
void CleanupDeviceD3D();

HWND g_hwndEsp = nullptr;
HWND g_hwndGui = nullptr;
ImGuiContext* g_espContext = nullptr;
ImGuiContext* g_guiContext = nullptr;
ID3D11Device*            g_pd3dDevice = nullptr;
ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;

IDXGISwapChain*          g_pSwapChainEsp = nullptr;
ID3D11RenderTargetView*  g_pRenderTargetViewEsp = nullptr;

IDXGISwapChain*          g_pSwapChainGui = nullptr;
ID3D11RenderTargetView*  g_pRenderTargetViewGui = nullptr;
bool g_running = true;


struct AutoParrySettings {
    bool Enabled = true;
    float TimingOffset = 0.08f;     // Adjust this (seconds before hit)
    float MaxDistance = 60.0f;
    bool OnlyWhenTargeted = true;   // Only parry if NPC is targeting you
};

AutoParrySettings AutoParry; // Unused ass structure

struct GameCache
{
    Instance dataModel{};
    Instance workspace{};
    Instance players{};
    Instance camera{};
    Instance lighting{};
    Player localPlayer{};
    Instance live{};
    Instance thrown{};
};

inline GameCache g_Game;

struct FishInfo {
    uintptr_t gui{};
    uintptr_t fgui{};
    Instance frame{};
    uintptr_t KeyA{};
    uintptr_t KeyD{};
    uintptr_t KeyS{};
};

inline FishInfo g_Fish;

struct CastInfo {
    uintptr_t gui{};
    uintptr_t spellGui{};
    uintptr_t frame{};
    Instance symbols{};
};

inline CastInfo g_Cast;


struct HealthInfo {
    float health;
    float maxHealth;
};

struct CharacterParts {
    uintptr_t head{};
    uintptr_t torso{};
    uintptr_t rootPart{};
    uintptr_t humanoid{};
    uintptr_t armor{};
    uintptr_t armorBroken{};
};

CharacterParts ResolveCharacter(Instance character) {
    CharacterParts parts{};

    if (!character) return parts;

    uintptr_t children_start = g_Memory.ReadPtr(character + Offsets::Instance::ChildrenStart);
    if (!children_start) return parts;

    uintptr_t children_end = g_Memory.ReadPtr(children_start + Offsets::Instance::ChildrenEnd);
    if (!children_end) return parts;

    for (uintptr_t ptr = g_Memory.ReadPtr(children_start);
        ptr != children_end && ptr != 0; ptr += 0x10) {

        uintptr_t child = g_Memory.ReadPtr(ptr);
        if (!child) continue;

        std::string name = GetInstanceName(child);

        if (name == "Head") {
            if (!parts.head) parts.head = child;
        }
        else if (name == "Torso") {
            if (!parts.torso) parts.torso = child;
        }
        else if (name == "HumanoidRootPart") {
            if (!parts.rootPart) parts.rootPart = child;
        }
        else if (name == "Armor") {
            if (!parts.armor) parts.armor = child;
        }
        else if (name == "ArmorBroken") {
            if (!parts.armorBroken) parts.armorBroken = child;
        }
        else if (!parts.humanoid && GetInstanceClass(child) == "Humanoid") {
            parts.humanoid = child;
        }

        if (parts.head && parts.torso && parts.rootPart && parts.humanoid &&
            parts.armor && parts.armorBroken)
            break;
    }

    return parts;
}

Vector3 GetPartPosition(uintptr_t part) {
    if (!part) return Vector3(0, 0, 0);

    uintptr_t primitive = g_Memory.ReadPtr(part + Offsets::BasePart::Primitive);
    if (primitive)
        return g_Memory.ReadVector3(primitive + Offsets::Primitive::Position);

    return g_Memory.ReadVector3(part + Offsets::Primitive::Position);
}

Vector3 GetRootPosition(const CharacterParts& parts) {
    return GetPartPosition(parts.rootPart);
}

Vector3 GetTorsoPosition(const CharacterParts& parts) {
    if (parts.torso) return GetPartPosition(parts.torso);
    if (parts.rootPart) return GetPartPosition(parts.rootPart);
    return Vector3(0, 0, 0);
}

Vector3 GetHeadPosition(const CharacterParts& parts) {
    if (parts.head) return GetPartPosition(parts.head);

    if (parts.torso) {
        Vector3 pos = GetPartPosition(parts.torso);
        pos.y += 1.5f;
        return pos;
    }

    if (parts.rootPart) {
        Vector3 pos = GetPartPosition(parts.rootPart);
        pos.y += 2.2f;
        return pos;
    }

    return Vector3(0, 0, 0);
}

HealthInfo GetHealth(const CharacterParts& parts) {
    if (!parts.humanoid) return { 0.0f, 0.0f };

    float health = g_Memory.ReadFloat(parts.humanoid + Offsets::Humanoid::Health);
    float maxHealth = g_Memory.ReadFloat(parts.humanoid + Offsets::Humanoid::MaxHealth);

    return { health / maxHealth, maxHealth };
}

DoubleConstraint GetArmor(const CharacterParts& parts) {
    if (!parts.armor) return DoubleConstraint(0, 0, 0);

    double Max = g_Memory.Read<double>(parts.armor + Offsets::Misc::Value);
    double Min = g_Memory.Read<double>(parts.armor + Offsets::Misc::Value + 0x8);
    double Val = g_Memory.Read<double>(parts.armor + Offsets::Misc::Value + 0x10);
    return DoubleConstraint(Max, Min, Val);
}

std::string NormalizeNPCName(std::string name)
{
    while (!name.empty() && isdigit(name.back()))
        name.pop_back();

    return name;
}

/*std::vector<PlayerInfo> GetAllPlayers() {
    std::vector<PlayerInfo> players;
    if (!g_Game.players) return players;

    uintptr_t children_start = g_Memory.ReadPtr(g_Game.players + Offsets::Instance::ChildrenStart);
    if (!children_start) return players;

    uintptr_t children_end = g_Memory.ReadPtr(children_start + Offsets::Instance::ChildrenEnd);
    if (!children_end) return players;

    for (uintptr_t ptr = g_Memory.ReadPtr(children_start);
        ptr != children_end && ptr != 0; ptr += 0x10) {

        uintptr_t player = g_Memory.ReadPtr(ptr);
        if (!player) continue;
        if (GetInstanceClass(player) != "Player") continue;

        std::string playerName = GetInstanceName(player);
        bool isLocal = (player == g_Game.localPlayer);

        if (!g_Game.live)
            return players;

        uintptr_t character;
        character = FindChildByName(g_Game.live, playerName);

        Vector3 headPos = GetHeadPosition(character);
        Vector3 torsoPos = GetTorsoPosition(character);
        Vector3 rootPos = GetRootPosition(character);
        if (rootPos.x == 0.0f && rootPos.y == 0.0f && rootPos.z == 0.0f)
            rootPos = torsoPos;

        HealthInfo hp = GetHealth(character);

        if (headPos.x != 0 || headPos.y != 0 || headPos.z != 0) {
            PlayerInfo info;
            info.playerInstance = player;
            info.character = character;
            info.headPosition = headPos;
            info.torsoPosition = torsoPos;
            info.rootPosition = rootPos;
            info.name = playerName;
            info.health = hp.health;
            info.maxHealth = hp.maxHealth;
            info.isValid = true;
            info.isLocal = isLocal;
            players.push_back(info);
        }
    }
    return players;
}*/

std::vector<PlayerInfo> GetAllPlayers() {
    std::vector<PlayerInfo> players;
    if (!g_Game.players) return players;
    if (!g_Game.live) {
        g_Game.live = g_Game.workspace.FindFirstChild("Live");
    }
    if (!g_Game.live) return players;

    std::vector<uintptr_t> children = g_Game.live.GetChildren();
    if (children.empty()) return players;

    const std::string localPlayerName = g_Game.localPlayer.GetName();

    for (Instance player : children) {
        if (!player) continue;

        std::string playerName = player.GetName();
        bool isLocal = (playerName == localPlayerName);
        if (playerName.find('.') == 0) continue;

        if (!g_Game.live)
            return players;

        CharacterParts parts = ResolveCharacter(player);

        Vector3 headPos = GetHeadPosition(parts);
        Vector3 torsoPos = GetTorsoPosition(parts);
        Vector3 rootPos = GetRootPosition(parts);
        if (rootPos.x == 0.0f && rootPos.y == 0.0f && rootPos.z == 0.0f)
            rootPos = torsoPos;

        HealthInfo hp = GetHealth(parts);

        if (headPos.x != 0 || headPos.y != 0 || headPos.z != 0) {
            PlayerInfo info;
            info.playerInstance = player;
            info.character = player;
            info.headPosition = headPos;
            info.torsoPosition = torsoPos;
            info.rootPosition = rootPos;
            info.name = std::move(playerName);
            info.health = hp.health;
            info.maxHealth = hp.maxHealth;
            info.isValid = true;
            info.isLocal = isLocal;
            players.push_back(info);
        }
    }
    return players;
}

std::vector<NPCInfo> GetAllNPC(bool ignoreuseless) {
    std::vector<NPCInfo> NPCS;
    if (!g_Game.players) return NPCS;
    if (!g_Game.live) {
        g_Game.live = g_Game.workspace.FindFirstChild("Live");
    }
    if (!g_Game.live) return NPCS;

    std::vector<uintptr_t> children = g_Game.live.GetChildren();
    if (children.empty()) return NPCS;

    for (Instance NPC : children) {
        if (!NPC) continue;

        std::string NPCName = NPC.GetName();
        if (!NPCName.find('.') == 0) continue;

        std::string key = NormalizeNPCName(std::move(NPCName));

        if (ignoreuseless and UselessNPCs.find(key) != UselessNPCs.end()) continue;

        if (!g_Game.live)
            return NPCS;

        CharacterParts parts = ResolveCharacter(NPC);

        Vector3 headPos = GetHeadPosition(parts);
        Vector3 torsoPos = GetTorsoPosition(parts);
        Vector3 rootPos = GetRootPosition(parts);
        if (rootPos.x == 0.0f && rootPos.y == 0.0f && rootPos.z == 0.0f)
            rootPos = torsoPos;

        HealthInfo hp = GetHealth(parts);

        DoubleConstraint armor = GetArmor(parts);

        bool canarmorbreak = parts.armorBroken != 0;

        if (headPos.x != 0 || headPos.y != 0 || headPos.z != 0) {
            NPCInfo info;
            info.character = NPC;
            info.headPosition = headPos;
            info.torsoPosition = torsoPos;
            info.rootPosition = rootPos;
            auto displayName = NPCNames.find(key);
            info.name = (displayName != NPCNames.end()) ? displayName->second : key;
            info.health = hp.health;
            info.maxHealth = hp.maxHealth;
            info.armor = armor;
            info.isValid = true;
            info.canArmorBreak = canarmorbreak;
            NPCS.push_back(info);
        }
    }
    return NPCS;
}

std::vector<ChestInfo> GetAllChests() {
    std::vector<ChestInfo> chests;
    if (!g_Game.thrown) {
        g_Game.live = g_Game.workspace.FindFirstChild("Thrown");
    }
    if (!g_Game.thrown) return chests;

    std::vector<uintptr_t> children = g_Game.thrown.GetChildren();
    if (children.empty()) return chests;

    for (Instance chest : children) {
        if (!chest) continue;
        if (chest.GetClass() != "Model") continue;
        if (chest.FindFirstChild("Lid") == false) continue;

        uintptr_t model = chest;

        BasePart base = chest.FindFirstChild("RootPart");

        if (base.get() == 0) {
            base = chest.FindFirstChild("Lid");
        }

        /*uintptr_t primitive = g_Memory.ReadPtr(base + Offsets::BasePart::Primitive);*/
        Vector3 pos = base.Position();
        //if (primitive) {
        //    pos = g_Memory.ReadVector3(primitive + Offsets::Primitive::Position);
        //}
        //else {
        //    pos = g_Memory.ReadVector3(base + Offsets::Primitive::Position);
        //}

        if (pos.x != 0 || pos.y != 0 || pos.z != 0) {
            ChestInfo info;
            info.Instance = chest;
            info.base = base;
            info.Position = pos;
            info.name = "Chest";
            info.isValid = true;
            chests.push_back(info);
        }
    }
    return chests;
}


//
// AUTO PARRY
//

//float CalculateDistance(const Vector3& pos1, const Vector3& pos2) {
//    float dx = pos1.x - pos2.x;
//    float dy = pos1.y - pos2.y;
//    float dz = pos1.z - pos2.z;
//    return sqrtf(dx * dx + dy * dy + dz * dz);
//}
//
//bool IsPlayingAttackAnimation(uintptr_t character) {
//    if (!character) return false;
//
//    uintptr_t humanoid = 0;
//    // Find Humanoid
//    humanoid = FindChildByName(character, "Humanoid");
//    if (!humanoid) return false;
//
//    uintptr_t animator = FindChildByName(humanoid, "Animator"); // Usually Animator is at this offset
//    if (!animator) { std::cout << "NOU ANIMATOR"; return false; }
//
//    uintptr_t activeAnims = g_Memory.ReadPtr(animator + Offsets::Animator::ActiveAnimations);
//    if (!activeAnims) { std::cout << "NO ACTIVE ANIMS"; return false; }
//
//    uintptr_t vector = g_Memory.ReadPtr(animator + Offsets::Animator::ActiveAnimations);
//
//    uintptr_t obj = g_Memory.ReadPtr(animator + 0xA20);
//
//    uintptr_t p = g_Memory.ReadPtr(obj);
//
//    for (int i = 0; i < 0x60; i += 8)
//    {
//        printf("%02X : %p\n", i, (void*)g_Memory.ReadPtr(p + i));
//    }
//
//    // Simple check - if there's any animation playing with high speed, likely attacking
//    // You can improve this later with specific animation IDs
//    //uintptr_t animStart = g_Memory.ReadPtr(activeAnims + Offsets::Instance::ChildrenStart);
//    //uintptr_t animEnd = g_Memory.ReadPtr(activeAnims + Offsets::Instance::ChildrenEnd);
//
//    //for (uintptr_t p = g_Memory.ReadPtr(animStart); p != animEnd; p += 0x10) {
//    //    uintptr_t animTrack = g_Memory.ReadPtr(p);
//    //    std::cout << GetInstanceClass(animTrack) << '\n';
//    //    if (!animTrack) { std::cout << "no anim track"; continue; }
//
//    //    float timePos = g_Memory.ReadFloat(animTrack + Offsets::AnimationTrack::TimePosition);
//    //    float speed = g_Memory.ReadFloat(animTrack + Offsets::AnimationTrack::Speed);
//
//    //    //if (speed > 0.8f && timePos > 0.1f && timePos < 0.9f) {
//    //        return true;
//    //    //}
//    //}
//    return false;
//}
//
//// Simple key simulator
//void SimulateKeyPress(char key, bool down) {
//    INPUT ip = { 0 };
//    ip.type = INPUT_KEYBOARD;
//    ip.ki.wVk = VkKeyScanA(key);
//    ip.ki.dwFlags = down ? 0 : KEYEVENTF_KEYUP;
//    SendInput(1, &ip, sizeof(INPUT));
//}
//
//void SimulateParry() {
//    static bool wasDown = false;
//    if (!wasDown) {
//        SimulateKeyPress('F', true);   // Press F
//        wasDown = true;
//        std::cout << "PRESSED F";
//    }
//}
//
//
//void TryAutoParryNPCs() {
//    if (!AutoParry.Enabled) return;
//    if (!g_Game.live) return;
//
//    uintptr_t localChar = FindChildByName(g_Game.live, GetInstanceName(g_Game.localPlayer));
//    if (!localChar) return;
//
//    Vector3 myPos = GetRootPosition(localChar);
//
//    auto npcs = GetAllNPC(false);
//
//    for (const auto& npc : npcs) {
//        if (!npc.isValid) continue;
//
//        float dist = CalculateDistance(myPos, npc.rootPosition);
//        if (dist > AutoParry.MaxDistance) continue;
//
//        if (IsPlayingAttackAnimation(npc.character)) {
//            // Small randomization to look more legit
//            float finalDelay = AutoParry.TimingOffset + ((rand() % 30) / 1000.0f);
//            std::this_thread::sleep_for(std::chrono::milliseconds((int)(finalDelay * 1000)));
//
//            SimulateParry();
//            return; // Only parry one at a time
//        }
//    }
//}

//
//
//

//
// MACROS
//

void SimulateKeyPress(WORD scanCode, bool down)
{
    INPUT input{};
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = scanCode;
    input.ki.dwFlags = KEYEVENTF_SCANCODE |
        (down ? 0 : KEYEVENTF_KEYUP);

    SendInput(1, &input, sizeof(INPUT));
}

void AutoFish() {
    if (!g_Fish.gui) {
        g_Fish.gui = FindChildByName(g_Game.localPlayer, "PlayerGui");
        g_Fish.fgui = FindChildByName(g_Fish.gui, "FishingGui");
        g_Fish.frame = FindChildByName(g_Fish.fgui, "MainFrame");
        g_Fish.KeyA = FindChildByName(g_Fish.frame, "HoldA");
        g_Fish.KeyD = FindChildByName(g_Fish.frame, "HoldD");
        g_Fish.KeyS = FindChildByName(g_Fish.frame, "HoldS");
    };
    if (!g_Fish.fgui) return;
    if (!g_Fish.frame) return;
    bool keyS = g_Memory.Read<bool>(g_Fish.KeyS + Offsets::GuiObject::Visible);
    if (keyS) { SimulateKeyPress(0x1F, true); SimulateKeyPress(0x1F, false); return; }
    bool keyD = g_Memory.Read<bool>(g_Fish.KeyD + Offsets::GuiObject::Visible);
    if (keyD) { SimulateKeyPress(0x20, true); SimulateKeyPress(0x20, false); return; }
    bool keyA = g_Memory.Read<bool>(g_Fish.KeyA + Offsets::GuiObject::Visible);
    if (keyA) { SimulateKeyPress(0x1E, true); SimulateKeyPress(0x1E, false); return; }
}

std::atomic<bool> autoCastCasting = false;

void AutoCastThread(int castdelay) {
    if (!g_Cast.gui) {
        g_Cast.gui = FindChildByName(g_Game.localPlayer, "PlayerGui");
        g_Cast.spellGui = FindChildByName(g_Cast.gui, "SpellGui");
        if (!g_Cast.spellGui) { g_Cast.gui = {}; return; }
        g_Cast.frame = FindChildByName(g_Cast.spellGui, "SpellFrame");
        if (!g_Cast.frame) { g_Cast.gui = {}; return; }
        g_Cast.symbols = FindChildByName(g_Cast.frame, "Symbols");
        if (!g_Cast.symbols) { g_Cast.gui = {}; return; }
    }

    if (!g_Cast.spellGui || !g_Cast.frame || !g_Cast.symbols) return;

    std::vector<uintptr_t> children = g_Cast.symbols.GetChildren();
    if (children.empty() or autoCastCasting == true) return;


    std::string ritual;
    for (Instance child : children) {
        if (!child) continue;
        if (child.GetName() == "Frame") {
            autoCastCasting = true;
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // to make sure all frames actually appeared and it doesnt take only a couple

    for (Instance child : children) {
        if (!child) continue;
        if (child.GetName() == "Frame") {
            Instance label = child.FindFirstChild("TextLabel");
            if (!label) continue;
            ritual += g_Memory.ReadRobloxString(label + Offsets::GuiObject::Text);
        }
    }
    std::cout << ritual << std::endl;

    for (char x : ritual) {
        std::this_thread::sleep_for(std::chrono::milliseconds(castdelay));
        if (x == 'V') { SimulateKeyPress(0x2F, true); SimulateKeyPress(0x2F, false); }
        if (x == 'C') { SimulateKeyPress(0x2E, true); SimulateKeyPress(0x2E, false); }
        if (x == 'Z') { SimulateKeyPress(0x2C, true); SimulateKeyPress(0x2C, false); }
        if (x == 'X') { SimulateKeyPress(0x2D, true); SimulateKeyPress(0x2D, false); }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    autoCastCasting = false;
}

void AutoCast(int castdelay) {
    if (autoCastCasting) return; // dont start a new one while already casting
    std::thread(AutoCastThread, castdelay).detach();
}

std::atomic<bool> ardoring = false;

//void ardorSpamThread() {
//    ardoring = true;
//    for (int i = 0; i < 20; i++) {
//        SimulateKeyPress(0x2F, true); SimulateKeyPress(0x2F, false);
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//    ardoring = false;
//}

//void ardorSpam() {
//    if (autoCastCasting or ardoring) return; // dont start a new one while already casting
//    std::thread(ardorSpamThread).detach();
//}

static bool g_guiCapturesInput = false;
static bool g_guiVisible = true;

//
//
//

// 
// # Preparations
//

struct UpdateTimer {
    std::chrono::steady_clock::time_point last{};
    int intervalMs = 0;

    UpdateTimer() = default;
    explicit UpdateTimer(int ms) : intervalMs(ms) {}

    bool ready() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
        if (elapsed >= intervalMs) {
            last = now;
            return true;
        }
        return false;
    }
};

UpdateTimer fishUpdate{ 50 };
UpdateTimer castUpdate{ 50 };
UpdateTimer aUpdate{ 100 };
UpdateTimer playerUpdate{ 16 };
UpdateTimer npcUpdate{ 48 };
UpdateTimer chestUpdate{ 100 };
UpdateTimer pointerCheck{ 500 };

bool emptying = false;

void EmptyCaches() {
    emptying = true;
    g_Fish.gui = {};
    g_Fish.fgui = {};
    g_Fish.frame = {};
    g_Fish.KeyA = {};
    g_Fish.KeyD = {};
    g_Fish.KeyS = {};

    g_Cast.gui = {};
    g_Cast.spellGui = {};
    g_Cast.frame = {};
    g_Cast.symbols = {};

    emptying = false;
}

bool GetRobloxClientScreenRect(HWND hwnd, RECT& outRect) {
    if (!hwnd) return false;

    RECT clientRect{};
    if (!GetClientRect(hwnd, &clientRect)) return false;

    POINT topLeft = { clientRect.left, clientRect.top };
    POINT bottomRight = { clientRect.right, clientRect.bottom };
    ClientToScreen(hwnd, &topLeft);
    ClientToScreen(hwnd, &bottomRight);

    outRect.left = topLeft.x;
    outRect.top = topLeft.y;
    outRect.right = bottomRight.x;
    outRect.bottom = bottomRight.y;
    return true;
}

HWND FindRobloxWindow(RECT& outRect) {
    HWND hwnd = FindWindowW(NULL, L"Roblox");
    if (hwnd) {
        GetRobloxClientScreenRect(hwnd, outRect);
        return hwnd;
    }

    hwnd = FindWindowW(L"ApplicationFrameWindow", NULL);
    if (hwnd) {
        HWND childHwnd = FindWindowExW(hwnd, NULL, L"Roblox", NULL);
        if (childHwnd) {
            GetRobloxClientScreenRect(childHwnd, outRect);
            return childHwnd;
        }
        GetRobloxClientScreenRect(hwnd, outRect);
        return hwnd;
    }

    return NULL;
}

bool InitializeGame() {
    const uintptr_t base = g_Memory.GetBaseAddress();


    uintptr_t visualEnginePtr = g_Memory.ReadPtr(base + Offsets::VisualEngine::Pointer);
    if (!visualEnginePtr) return false;

    uintptr_t fakeDataModel = g_Memory.ReadPtr(visualEnginePtr + Offsets::VisualEngine::FakeDataModel);
    if (!fakeDataModel) return false;

    g_Game.dataModel = g_Memory.ReadPtr(fakeDataModel + Offsets::FakeDataModel::RealDataModel);
    if (!g_Game.dataModel) return false;


    g_Game.workspace = g_Memory.ReadPtr(g_Game.dataModel + Offsets::DataModel::Workspace);
    if (!g_Game.workspace) {
        g_Game.workspace = FindChildByClass(g_Game.dataModel, "Workspace");
    }

    g_Game.players = FindChildByClass(g_Game.dataModel, "Players");
    if (!g_Game.players) return false;


    g_Game.localPlayer = g_Memory.ReadPtr(g_Game.players + Offsets::Player::LocalPlayer);
    if (!g_Game.localPlayer) return false;

    //printf("Players service : %p\n", (void*)g_Game.players);
    //printf("LocalPlayer ptr : %p\n", (void*)g_Game.localPlayer);

    if (g_Game.workspace) {
        g_Game.camera = g_Memory.ReadPtr(g_Game.workspace + Offsets::Workspace::CurrentCamera);
    }

    g_Game.live = FindChildByName(g_Game.workspace, "Live");
    //if (!g_Game.live) return false;

    g_Game.thrown = FindChildByName(g_Game.workspace, "Thrown");
    //if (!g_Game.thrown) return false;

    EmptyCaches();

    std::cout << "[+] Game initialized successfully!" << std::endl;
    return true;
}

void runPrep(HWND* robloxWindow, RECT* robloxRect, HWND* g_hwndEsp, HWND* g_hwndGui) {

    std::cout << "=========================================" << std::endl;
    std::cout << "Deepwoken External" << std::endl;
    std::cout << "=========================================" << std::endl;

    if (!LoadOffsets(DOWOFF))
    {
        MessageBoxA(nullptr,
            "[!] Couldn't load offsets!",
            "Error",
            MB_ICONERROR);
        system("pause");
    }

    std::cout << "[+] Offsets Loaded!" << std::endl;

    if (!LoadNPCNames(DOWNN))
    {
        MessageBoxA(nullptr,
            "[!] Couldn't load names!",
            "Error",
            MB_ICONERROR);
        system("pause");
    }

    std::cout << "[+] Names Loaded!" << std::endl;

    std::cout << "[!] Waiting for game..." << std::endl;
    while (!(*robloxWindow)) {
        *robloxWindow = FindRobloxWindow(*robloxRect);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "[+] Game found!" << std::endl;
    std::cout << "[+] Game client area at: (" << robloxRect->left << ", " << robloxRect->top
        << ") size: " << (robloxRect->right - robloxRect->left) << " x "
        << (robloxRect->bottom - robloxRect->top) << std::endl;


    if (!g_Memory.Initialize()) {
        std::cout << "[-] Failed to attach to game." << std::endl;
        system("pause");
    }

    if (!InitializeGame()) {
        std::cout << "[-] Failed to initialize game state!" << std::endl;
        system("pause");
    }

    *g_hwndEsp = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE,
        L"ESPClass",
        L"ESP Overlay",
        WS_POPUP,
        robloxRect->left, robloxRect->top,
        robloxRect->right - robloxRect->left,
        robloxRect->bottom - robloxRect->top,
        NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!g_hwndEsp) {
        std::cout << "[-] Failed to create ESP window\n";
        return;
    }

    SetLayeredWindowAttributes(*g_hwndEsp, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(*g_hwndEsp, SW_SHOW);
    UpdateWindow(*g_hwndEsp);

    *g_hwndGui = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED,
        L"GUIClass",
        L"Menu",
        WS_POPUP,
        robloxRect->left, robloxRect->top, //robloxRect->left + 50, robloxRect->top + 50,   // slightly offset so you can see it
        robloxRect->right - robloxRect->left, robloxRect->bottom - robloxRect->top, //420, 520,                                      // reasonable default size
        NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!g_hwndGui) {
        std::cout << "[-] Failed to create GUI window\n";
        return;
    }

    SetLayeredWindowAttributes(*g_hwndGui, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(*g_hwndGui, SW_SHOW);
    SetForegroundWindow(*g_hwndGui);
    BringWindowToTop(*g_hwndGui);
    UpdateWindow(*g_hwndGui);

    // Create D3D
    if (!CreateDeviceD3D(*g_hwndEsp, *g_hwndGui)) {
        std::cout << "[-] Failed to create D3D11 device\n";
    }

    std::cout << "\n=========================================" << std::endl;
    std::cout << "Ready!" << std::endl;
    std::cout << "=========================================\n" << std::endl;
}

void CheckGamePointers(std::vector<PlayerInfo>* players) {
    uintptr_t newFakeDM =
        g_Memory.ReadPtr(
            g_Memory.ReadPtr(g_Memory.GetBaseAddress() + Offsets::VisualEngine::Pointer)
            + Offsets::VisualEngine::FakeDataModel);

    uintptr_t newDM =
        g_Memory.ReadPtr(newFakeDM + Offsets::FakeDataModel::RealDataModel);

    if (newDM != g_Game.dataModel)
    {
        std::cout << "[!] Teleport detected\n";
        players->clear();
        while (!InitializeGame())
        {
            std::cout << "[-] Initialize failed retrying..." << std::endl;
            Sleep(500);
        }
    }
}

bool ShouldRenderESP()
{
    static auto lastTime = std::chrono::high_resolution_clock::now();
    constexpr float targetFPS = 120.0f;
    constexpr auto frameDuration = std::chrono::duration<float>(1.0f / targetFPS);

    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = now - lastTime;

    if (elapsed < frameDuration)
    {
        // Sleep the remaining time (optional, reduces CPU/GPU a bit more)
        std::this_thread::sleep_for(frameDuration - elapsed);
        now = std::chrono::high_resolution_clock::now();
    }

    lastTime = now;
    return true;
}

//
//
//

//uintptr_t lighting = FindChildByClass(g_datamodel, "Lighting");

ESP* g_esp = nullptr;
WorldToScreenConverter* g_W2S = nullptr;

int main() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    SetConsoleTitle(L"the thing");

    HWND robloxWindow = NULL;
    RECT robloxRect = { 0 };

    g_W2S = new WorldToScreenConverter();
    g_esp = new ESP(g_W2S);


    WNDCLASSEXW wcEsp = {};
    wcEsp.cbSize = sizeof(WNDCLASSEXW);
    wcEsp.style = CS_HREDRAW | CS_VREDRAW;
    wcEsp.lpfnWndProc = WndProcEsp;               // Esp
    wcEsp.hInstance = GetModuleHandle(NULL);
    wcEsp.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wcEsp.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
    wcEsp.lpszClassName = L"ESPClass";

    if (!RegisterClassExW(&wcEsp)) {
        std::cout << "[-] Failed to register window class" << std::endl;
        system("pause");
    }

    WNDCLASSEXW wcGui = {};
    wcGui.cbSize = sizeof(WNDCLASSEXW);
    wcGui.style = CS_HREDRAW | CS_VREDRAW;
    wcGui.lpfnWndProc = WndProcGui;               // Gui
    wcGui.hInstance = GetModuleHandle(NULL);
    wcGui.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wcGui.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
    wcGui.lpszClassName = L"GUIClass";

    if (!RegisterClassExW(&wcGui)) {
        std::cout << "[-] Failed to register window class" << std::endl;
        system("pause");
    }

    g_hwndEsp;
    g_hwndGui;

    runPrep(&robloxWindow, &robloxRect, &g_hwndEsp, &g_hwndGui);

    IMGUI_CHECKVERSION();

    // ESP context
    g_espContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(g_espContext);
    ImGuiIO& ioEsp = ImGui::GetIO();
    ioEsp.IniFilename = nullptr;
    ImGui_ImplWin32_Init(g_hwndEsp);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
    ImGui::StyleColorsDark();

    // GUI context
    g_guiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(g_guiContext);
    ImGuiIO& ioGui = ImGui::GetIO();
    ioGui.IniFilename = nullptr;
    ImGui_ImplWin32_Init(g_hwndGui);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
    ImGui::StyleColorsDark();

    MSG msg;
    int updateCounter = 0;
    RECT lastRect = robloxRect;
    std::vector<PlayerInfo> players;
    std::vector<NPCInfo> NPCS;
    std::vector<ChestInfo> chests;

    if (g_Game.localPlayer.GetName() == "ERROR463247") { g_esp->GetConfig().testFuns = true; }

    std::cout << "\n[!] Trying to load config...\n";
    g_esp->GetConfig().load();

    using clock = std::chrono::steady_clock;
    constexpr auto frameTime = std::chrono::microseconds(8333);

    auto frameStart = clock::now();

    while (g_running) {

        if (GetAsyncKeyState(VK_INSERT) & 1)
            g_guiVisible = !g_guiVisible;
        if (GetRobloxClientScreenRect(robloxWindow, robloxRect))
        {
            int newWidth = robloxRect.right - robloxRect.left;
            int newHeight = robloxRect.bottom - robloxRect.top;

            // ESP always follows the game and stays topmost
            SetWindowPos(g_hwndEsp, HWND_TOPMOST,
                robloxRect.left, robloxRect.top, newWidth, newHeight,
                SWP_NOACTIVATE);

            // GUI must be ABOVE the ESP window
            if (g_guiVisible)
            {
                SetWindowPos(g_hwndGui, HWND_TOPMOST,
                    0, 0, 0, 0,
                    SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

                // Force GUI above ESP
                SetWindowPos(g_hwndGui, g_hwndEsp,
                    0, 0, 0, 0,
                    SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            }
        }


        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                g_running = false;
            }
        }

        if (!g_running) break;


        g_W2S->Update(robloxWindow);

        if (pointerCheck.ready())
        {
            CheckGamePointers(&players);
        }

        // Update players less frequently
        //static auto lastPlayerUpdate = std::chrono::high_resolution_clock::now();
        //auto now = std::chrono::high_resolution_clock::now();
        //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPlayerUpdate).count();
        bool plrupdpause = false;

        //if (AutoParry.Enabled && elapsed > 8) {
        //    TryAutoParryNPCs();
        //} I hate this AP func

        if (ShouldRenderESP())
        {
            if (fishUpdate.ready() and g_esp->GetConfig().autoFishing and (!emptying)) {
                AutoFish();
            }

            if (castUpdate.ready() and g_esp->GetConfig().autoCast and (!autoCastCasting) and (!emptying)) {
                AutoCast(g_esp->GetConfig().castDelay);
            }

            //if (aUpdate.ready() and g_esp->GetConfig().ardourSpam and (!autoCastCasting) and (!ardoring)) {
            //    if (GetAsyncKeyState('V') & 0x8000) {
            //        ardorSpam();
            //    }
            //}

            if (chestUpdate.ready() and g_esp->GetConfig().enableChestESP) {
                chests = GetAllChests();
            }

            if (npcUpdate.ready() and g_esp->GetConfig().enableNPCESP) {
                NPCS = GetAllNPC(g_esp->GetConfig().hideUselessNPC);
            }

            if (playerUpdate.ready() and plrupdpause == false) {
                players = GetAllPlayers();
                //lastPlayerUpdate = now;
            }

            // ImGui frame
            ImGui::SetCurrentContext(g_espContext);
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // Render ESP
            if (g_esp->GetConfig().enableESP) {
                ImDrawList* drawList = ImGui::GetBackgroundDrawList();
                g_esp->RenderPlayers(players, drawList);
            }

            if (g_esp->GetConfig().enableNPCESP) {
                ImDrawList* drawList = ImGui::GetBackgroundDrawList();
                g_esp->RenderNPC(players, NPCS, drawList);
            }

            if (g_esp->GetConfig().enableChestESP) {
                ImDrawList* drawList = ImGui::GetBackgroundDrawList();
                g_esp->RenderChests(players, chests, drawList);
            }

            char bufff[64];
            snprintf(bufff, sizeof(bufff), "ESP: %.0f FPS | GUI: %.0f FPS",
                g_espFPS.fps, g_guiFPS.fps);

            ImGui::GetBackgroundDrawList()->AddText(
                ImVec2(10.0f, 10.0f),
                IM_COL32(255, 255, 255, 255),
                bufff
            );

            ImGui::Render();

            float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetViewEsp, nullptr);
            g_pd3dDeviceContext->ClearRenderTargetView(g_pRenderTargetViewEsp, clearColor);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            g_pSwapChainEsp->Present(0, 0);   // 0 = no vsync for lowest latency on ESP
            g_espFPS.tick();


            // --- GUI pass (only when visible) ---
            if (g_guiVisible)
            {
                ShowWindow(g_hwndGui, SW_SHOW);

                ImGui::SetCurrentContext(g_guiContext);
                ImGui_ImplDX11_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();

                g_esp->RenderMenu(&g_guiVisible);   // existing menu

                ImGui::Render();

                g_pd3dDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetViewGui, nullptr);
                g_pd3dDeviceContext->ClearRenderTargetView(g_pRenderTargetViewGui, clearColor);
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
                g_pSwapChainGui->Present(1, 0);
                g_guiFPS.tick();
            }
            else
            {
                // hide the window completely when menu is closed
                ShowWindow(g_hwndGui, SW_HIDE);
            }
        }

        //auto elapseded = clock::now() - frameStart;
        //if (elapseded < frameTime)
        //    std::this_thread::sleep_for(frameTime - elapseded);

        if (GetAsyncKeyState(VK_END) & 1) {
            g_running = false;
        }

    }

    ImGui::SetCurrentContext(g_espContext);
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext(g_espContext);

    ImGui::SetCurrentContext(g_guiContext);
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext(g_guiContext);

    CleanupDeviceD3D();
    DestroyWindow(g_hwndEsp);
    DestroyWindow(g_hwndGui);

    g_esp->GetConfig().save();

    delete g_esp;
    delete g_W2S;

    std::cout << "\nCleanup complete. Press any key to exit..." << std::endl;
    system("pause");
    FreeConsole();

    return 0;
}

//
// # Direct3D
//

LRESULT CALLBACK WndProcEsp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DESTROY) {
        g_running = false;
        PostQuitMessage(0);
        return 0;
    }
    if (msg == WM_NCHITTEST)
        return HTTRANSPARENT;

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WndProcGui(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_DESTROY:
        g_running = false;
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CreateDeviceD3D(HWND hwndEsp, HWND hwndGui)
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 2;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // Create device + ESP swap chain
    sd.OutputWindow = hwndEsp;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        nullptr, 0, D3D11_SDK_VERSION,
        &sd, &g_pSwapChainEsp, &g_pd3dDevice, nullptr, &g_pd3dDeviceContext);

    if (FAILED(hr)) return false;

    // Create GUI swap chain sharing the same device
    sd.OutputWindow = hwndGui;

    IDXGIDevice* pDXGIDevice = nullptr;
    g_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);

    IDXGIAdapter* pAdapter = nullptr;
    pDXGIDevice->GetAdapter(&pAdapter);

    IDXGIFactory* pFactory = nullptr;
    pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

    hr = pFactory->CreateSwapChain(g_pd3dDevice, &sd, &g_pSwapChainGui);

    pFactory->Release();
    pAdapter->Release();
    pDXGIDevice->Release();

    if (FAILED(hr)) return false;

    // Create render target views
    ID3D11Texture2D* pBackBuffer = nullptr;

    g_pSwapChainEsp->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetViewEsp);
    pBackBuffer->Release();

    g_pSwapChainGui->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetViewGui);
    pBackBuffer->Release();

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pRenderTargetViewEsp) { g_pRenderTargetViewEsp->Release(); g_pRenderTargetViewEsp = nullptr; }
    if (g_pRenderTargetViewGui) { g_pRenderTargetViewGui->Release(); g_pRenderTargetViewGui = nullptr; }
    if (g_pSwapChainEsp) { g_pSwapChainEsp->Release();        g_pSwapChainEsp = nullptr; }
    if (g_pSwapChainGui) { g_pSwapChainGui->Release();        g_pSwapChainGui = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release();    g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release();           g_pd3dDevice = nullptr; }
}

//
//
//