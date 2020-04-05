#pragma once

#include <Windows.h>
#include <iostream>
#include "calcs.h"


/*
LocalPlayer: ac_client.exe+10F4F4
ProjectionMatrix: ac_client.exe+101AE8
Entitylist:  ac_client.exe+10f4f8
NumberOfPlayers: ac_client.exe+10f500
Window width: ac_client.exe + 110C94
Window height: ac_client.exe + 110C98
Game mode: ac_client.exe + 10f49C
*/


class PlayerEntity
{
public:
	uint32_t vTable; //0x0000
	Vector3 HeadPosition; //0x0004
	char pad_0010[36]; //0x0010
	Vector3 FootPosition; //0x0034
	Vector3 Angles; //0x0040
	char pad_004C[172]; //0x004C
	int32_t Health; //0x00F8
	int32_t Shield; //0x00FC
	char pad_0100[20]; //0x0100
	int32_t PistolAmmo2; //0x0114
	char pad_0118[16]; //0x0118
	int32_t RifleAmmo2; //0x0128
	char pad_012C[16]; //0x012C
	int32_t PistolAmmo1; //0x013C
	char pad_0140[16]; //0x0140
	int32_t RifleAmmo1; //0x0150
	char pad_0154[4]; //0x0154
	int32_t GrenadeAmmo; //0x0158
	char pad_015C[36]; //0x015C
	int32_t GrenadeWaitTime; //0x0180
	char pad_0184[161]; //0x0184
	char Name[16]; //0x0225
	char pad_0235[247]; //0x0235
	int32_t Team; //0x032C
	char pad_0330[8]; //0x0330
	int32_t IsAlive; //0x0338
	char pad_033C[1345]; //0x033C
}; //Size: 0x087D


class ViewMatrix
{
public:
	float Matrix[16]; //0x0000
}; //Size: 0x0040


class EntityList
{
public:
	PlayerEntity* Entities[31];
};


bool IsValidEntity(PlayerEntity* Entity)
{
	if (Entity)
	{
		if (Entity->vTable == 0x4E4A98 || Entity->vTable == 0x4E4AC0)
		{
			return true;
		}
	}
	return false;
}