#pragma once

#include "Reclass.h"
#include "Enums.h"

HMODULE hmBase = GetModuleHandle(L"ac_client.exe");

DWORD offEntityList = DWORD(hmBase) + 0x10F4F8;
DWORD offPlayerEntity = DWORD(hmBase) + 0x10F4F4;
DWORD offNumberOfPlayers = DWORD(hmBase) + 0x10f500;
DWORD offViewMatrix = DWORD(hmBase) + 0x101AE8;
DWORD offWindowWidth = DWORD(hmBase) + 0x110C94;
DWORD offWindowHeight = DWORD(hmBase) + 0x110C98;
DWORD offGameMode = DWORD(hmBase) + 0x10f49C;

EntityList* entitylist;
PlayerEntity* localPlayer = (PlayerEntity*)*(DWORD*)offPlayerEntity;
ViewMatrix* viewmatrix = (ViewMatrix*)(DWORD)offViewMatrix;
int* gamemode = (int*)(offGameMode);
int* numberofplayers = (int*)(offNumberOfPlayers);
int* windowwidth = (int*)(offWindowWidth);
int* windowheight = (int*)(offWindowHeight);

Vector3 screenFoot;
Vector3 screenHead;
float flHeight;
float flWidth;
Vector3 namePos;

GL::Font glFont;
GLubyte red[3] = { 255, 0, 0 };


using namespace AssaultCube;

bool GotTeamMates()
{
    return (
        *gamemode == GMODE_BOTTEAMONESHOTONKILL ||
        *gamemode == GMODE_TEAMONESHOTONEKILL ||
        *gamemode == GMODE_BOTTEAMDEATHMATCH ||
        *gamemode == GMODE_TEAMDEATHMATCH ||
        *gamemode == GMODE_TEAMSURVIVOR ||
        *gamemode == GMODE_TEAMLSS ||
        *gamemode == GMODE_CTF ||
        *gamemode == GMODE_TEAMKEEPTHEFLAG ||
        *gamemode == GMODE_HUNTTHEFLAG ||
        *gamemode == GMODE_TEAMPF ||
        *gamemode == GMODE_BOTTEAMSURVIVOR ||
        *gamemode == GMODE_BOTTEAMONESHOTONKILL
        );
}

void DrawESP()
{
    EntityList* entitylist = (EntityList*)*(DWORD*)offEntityList;

    for (int i = 0; i < (*numberofplayers); i++)
    {
        if (!entitylist || !IsValidEntity(entitylist->Entities[i]))
            continue;

        if (!WorldToScreen(entitylist->Entities[i]->FootPosition, screenFoot, viewmatrix->Matrix, *windowwidth, *windowheight))
            continue;

        if (!WorldToScreen(entitylist->Entities[i]->HeadPosition, screenHead, viewmatrix->Matrix, *windowwidth, *windowheight))
            continue;

        if (entitylist->Entities[i]->IsAlive == CS_DEAD)
            continue;

        if (GotTeamMates())
        {
            if (localPlayer->Team == entitylist->Entities[i]->Team) //No Teammates
                continue;
        }

        flHeight = abs(screenFoot.y - screenHead.y);
        flWidth = flHeight / 2.0F;
        namePos.x = screenFoot.x - flWidth / 2;
        namePos.y = screenFoot.y + 10.0f;

        glFont.Print(namePos.x, namePos.y, red, "%s", entitylist->Entities[i]->Name);
        GL::DrawOutline(screenHead.x, screenHead.y, flWidth, flHeight, 1.0f, red);
    }
}

