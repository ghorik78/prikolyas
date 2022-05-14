#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <d3d9.h>
#include <d3dx9.h>	
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "Vectors.h"

#include "LocalPlayer.h"
#include "GameEngine.h"
#include "Entity.h"
#include "WorldToScreen.h"
#include "CalcAngle.h"

#include "Offsets.h"

#include "BunnyHop.h"
#include "WallHack.h"
#include "TriggerBot.h"
#include "RCS.h"
#include "AimBot.h"
#include "NoFlash.h"
#include "ThirdPerson.h"

#include "Settings.h"
UserSettings Settings;

using namespace hazedumper::signatures;
using namespace hazedumper::netvars;

#define WINDOW_NAME "AbobaHack"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);