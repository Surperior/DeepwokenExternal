#pragma once
#include <windows.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include "LogicStructs.h"
#include "imgui.h"
#include <iostream>
#include <fstream>

//
// ESP Configuration
//

struct ESPConfig {
    bool testFuns = false;

    bool enableESP = true;
    float boxSize = 125.0f;
    float opacity = 1.0f;
    int dist = 6000;

    bool showLocalPlayer = false;
    bool showOtherPlayers = true;
    bool allPlayersMode = true;

    bool showHealth = true;
    bool showHealthText = true;
    bool showHealthBar = true;
    bool ColoredBar = true;

    bool enableNPCESP = true;
    int distNPC = 1000;
    float opacityNPC = 1.0f;

    bool showHealthNPC = true;
    bool showHealthBarNPC = false;
    bool showHealthTextNPC = true;
    bool showArmorTextNPC = true;
    bool hideUselessNPC = true;

    bool enableChestESP = false;
    int distChest = 1000;
    float opacityChest = 1.0f;

    // Macro Related
    bool autoFishing = false;
    bool autoCast = false;
    int castDelay = 120;
    bool ardourSpam = false;

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, last - first + 1);
    }

    void save() {
        std::ofstream out("snakesmybeloved");

        if (!out) {
            std::cout << "[-] Failed to save config\n";
            return;
        }

        out << "enableESP=" << enableESP << '\n';
        out << "boxSize=" << boxSize << '\n';
        out << "opacity=" << opacity << '\n';
        out << "dist=" << dist << '\n';
        out << "showLocalPlayer=" << showLocalPlayer << '\n';
        out << "showOtherPlayers=" << showOtherPlayers << '\n';
        out << "showHealth=" << showHealth << '\n';
        out << "showHealthText=" << showHealthText << '\n';
        out << "showHealthBar=" << showHealthBar << '\n';
        out << "ColoredBar=" << ColoredBar << '\n';
        out << "enableNPCESP=" << enableNPCESP << '\n';
        out << "distNPC=" << distNPC << '\n';
        out << "opacityNPC=" << opacityNPC << '\n';
        out << "showHealthNPC=" << showHealthNPC << '\n';
        out << "showHealthBarNPC=" << showHealthBarNPC << '\n';
        out << "showHealthTextNPC=" << showHealthTextNPC << '\n';
        out << "showArmorTextNPC=" << showArmorTextNPC << '\n';
        out << "hideUselessNPC=" << hideUselessNPC << '\n';
        out << "enableChestESP=" << enableChestESP << '\n';
        out << "distChest=" << distChest << '\n';
        out << "opacityChest=" << opacityChest << '\n';
        // Macros
        out << "autoFishing=" << autoFishing << "\n";
        out << "autoCast=" << autoCast << "\n";
        out << "castDelay=" << castDelay << "\n";
        std::cout << "[+] Config saved successfully\n";
    }

    void load() {
        std::ifstream in("snakesmybeloved");
        if (!in) {
            std::cout << "[-] Failed to load config\n";
            return;
        }

        std::string line;
        while (std::getline(in, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#' || line[0] == ';') continue;

            auto eq = line.find('=');
            if (eq == std::string::npos) continue;

            std::string key = trim(line.substr(0, eq));
            std::string val = trim(line.substr(eq + 1));

            if (key == "enableESP")               enableESP = (val == "1" || val == "true");
            else if (key == "boxSize")            boxSize = std::stof(val);
            else if (key == "opacity")            opacity = std::stof(val);
            else if (key == "dist")               dist = std::stof(val);
            else if (key == "showLocalPlayer")    showLocalPlayer = (val == "1" || val == "true");
            else if (key == "showOtherPlayers")   showOtherPlayers = (val == "1" || val == "true");
            else if (key == "showHealth")         showHealth = (val == "1" || val == "true");
            else if (key == "showHealthText")     showHealthText = (val == "1" || val == "true");
            else if (key == "showHealthBar")      showHealthBar = (val == "1" || val == "true");
            else if (key == "ColoredBar")         ColoredBar = (val == "1" || val == "true");
            else if (key == "enableNPCESP")       enableNPCESP = (val == "1" || val == "true");
            else if (key == "distNPC")            distNPC = std::stof(val);
            else if (key == "opacityNPC")         opacityNPC = std::stof(val);
            else if (key == "showHealthNPC")      showHealthNPC = (val == "1" || val == "true");
            else if (key == "showHealthBarNPC")   showHealthBarNPC = (val == "1" || val == "true");
            else if (key == "showHealthTextNPC")  showHealthTextNPC = (val == "1" || val == "true");
            else if (key == "showArmorTextNPC")   showArmorTextNPC = (val == "1" || val == "true");
            else if (key == "hideUselessNPC")     hideUselessNPC = (val == "1" || val == "true");
            else if (key == "enableChestESP")     enableChestESP = (val == "1" || val == "true");
            else if (key == "distChest")          distChest = std::stof(val);
            else if (key == "opacityChest")       opacityChest = std::stof(val);
            // Macros
            else if (key == "autoFishing")        autoFishing = (val == "1" || val == "true");
            else if (key == "autoCast")           autoCast = (val == "1" || val == "true");
            else if (key == "castDelay")          castDelay = std::stof(val);
        }
        std::cout << "[+] Config loaded successfully\n";
    }
};

//
// Sctructures
//

struct PlayerInfo {
    uintptr_t playerInstance;
    uintptr_t character;
    Vector3 headPosition;
    Vector3 torsoPosition;
    Vector3 rootPosition;
    std::string name;
    float health;
    float maxHealth;
    bool isValid;
    bool isLocal;

    PlayerInfo() : playerInstance(0), character(0), isValid(false), isLocal(false),
        health(1.0f), maxHealth(100.0f) {}
};

struct NPCInfo {
    uintptr_t character;
    Vector3 headPosition;
    Vector3 torsoPosition;
    Vector3 rootPosition;
    DoubleConstraint armor;
    DoubleConstraint breakMeter;
    DoubleConstraint hemorrage;
    std::string name;
    float health;
    float maxHealth;
    bool isValid;
    bool canArmorBreak;

    NPCInfo() : character(0), isValid(false),
        health(1.0f), maxHealth(100.0f), canArmorBreak(false) {}
};

struct ChestInfo {
    uintptr_t Instance;
    uintptr_t base;
    Vector3 Position;
    std::string name;
    bool isValid;

    ChestInfo() : Instance(0), base(0), isValid(false) {}
};

class WorldToScreenConverter {
private:
    Matrix4x4 viewProjectionMatrix;
    Vector2 gameDimensions;
    Vector2 overlayDimensions;
    bool hasValidMatrix;

    Vector2 MapGameToOverlay(const Vector2& gameScreen) const;

public:
    WorldToScreenConverter();
    void Update(HWND robloxWindow);
    Vector2 Project(const Vector3& worldPos);
    Vector2 GetGameDimensions() const { return gameDimensions; }
    Vector2 GetOverlayDimensions() const { return overlayDimensions; }
};

struct ESPBounds {
    float left;
    float top;
    float right;
    float bottom;
    bool valid;
};

//
// Main ESP Class
//

class ESP {
private:
    ESPConfig config;
    WorldToScreenConverter* w2s;

    // Internal ESP functions
    ESPBounds ComputeBounds(const Vector2& head, const Vector2& root, const Vector2& foot, float sizeScale);
    float CalculateDistance(const Vector3& pos1, const Vector3& pos2);
    ImU32 GetHealthColor(float healthPercent);

public:
    ESP(WorldToScreenConverter* converter);

    // Configuration
    ESPConfig& GetConfig() { return config; }
    void SetConfig(const ESPConfig& newConfig) { config = newConfig; }

    // Rendering
    void RenderPlayers(const std::vector<PlayerInfo>& players, ImDrawList* drawList);
    void RenderPlayerBox(const PlayerInfo& player, ImDrawList* drawList);
    void RenderPlayerHealth(const PlayerInfo& player, ImDrawList* drawList, const ESPBounds& bounds, const float distance);
    void RenderPlayerInfo(const PlayerInfo& player, ImDrawList* drawList, const ESPBounds& bounds);
    void RenderNPC(const std::vector<PlayerInfo>& players, const std::vector<NPCInfo>& NPC, ImDrawList* drawList);
    void RenderNPCInfo(const NPCInfo& NPC, ImDrawList* drawList, const ESPBounds& bounds);
    void RenderNPCHealth(const NPCInfo& NPC, ImDrawList* drawList, const ESPBounds& bounds);
    void RenderChests(const std::vector<PlayerInfo>& players, const std::vector<ChestInfo>& items, ImDrawList* drawList);
    void RenderChestInfo(const ChestInfo& items, ImDrawList* drawList, const ESPBounds& bounds);

    // Menu
    void RenderMenu(bool* p_open = nullptr);
};