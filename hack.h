#pragma once

#include "includes.h"
#include "csgo.h"
#include <cstdint>

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;};

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

class Entity {
public:
    union {
        // is player far away?
        DEFINE_MEMBER_N(bool, isDormant, m_bDormant);
        DEFINE_MEMBER_N(int, iHealth, m_iHealth);
        DEFINE_MEMBER_N(Vec3, vecOrigin, m_vecOrigin);
        DEFINE_MEMBER_N(int, iTeamNum, m_iTeamNum);
        // where the head is?
        DEFINE_MEMBER_N(uint32_t, dwBoneMatrix, m_dwBoneMatrix);
        // player view from origin
        DEFINE_MEMBER_N(Vec3, vecViewOffset, m_vecViewOffset)
        DEFINE_MEMBER_N(int, armorValue, m_ArmorValue);
        // recoil
        DEFINE_MEMBER_N(Vec3, aimPunchAngle, m_aimPunchAngle);
        DEFINE_MEMBER_N(float, angEyeAnglesX, m_angEyeAnglesX);
        DEFINE_MEMBER_N(float, angEyeAnglesY, m_angEyeAnglesY);
        DEFINE_MEMBER_N(Vec3, vecVelocity, m_vecVelocity);
        DEFINE_MEMBER_N(bool, bHasHelmet, m_bHasHelmet);
        DEFINE_MEMBER_N(uint32_t, bSpottedByMask, m_bSpottedByMask);
    };
    Vec3* GetBonePos(int boneId) const;
};

class EntityListObject {
public:
    struct Entity* entity;
    BYTE padding[12];
};

class EntityList {
public:
    EntityListObject entities[32];
};

class Hack {
public:
    uintptr_t engine;
    uintptr_t client;

    Entity* localEntity;
    EntityList* entityList;
    float viewMatrix[16];

    Vec2 crosshair2D;
    int crosshairSize = 4;

    ID3DXLine* LineL;
    ID3DXFont* FontF;

    ~Hack() {
        LineL->Release();
        FontF->Release();
    }

    void Init();
    // update view matrix
    void Update();
    bool CheckValidEntity(Entity* entity) const;
    int GetLocalPlayerId() const;
    bool WorldToScreen(Vec3 position, Vec2& screen);
    void AimAt(Vec3 *target);
    Vec3* GetViewAngles() const;
    Vec3 TransformVec(Vec3 src, Vec3 dst, float distance);
    // aimbot
    void Run();

    struct Settings {
        bool showTeammates = true;
        bool snapLines = true;
        bool box2D = true;
        bool status2D = true;
        bool statusText = true;
        bool box3D = true;
        bool rcsCrossHair = true;
    } settings;
};