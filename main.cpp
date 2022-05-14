#include "includes.h"


#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

bool showMenu = false;
static int tab = 0;

std::vector<std::string> AcceptedHWIDs;

bool checkHWID(HW_PROFILE_INFO hwid) {
	for (int i = 0; i < AcceptedHWIDs.size(); ++i) {
		if (AcceptedHWIDs[i] == hwid.szHwProfileGuid) return true;
	}
	return false;
}

void addHWID(std::string szHWID) {
	AcceptedHWIDs.push_back(szHWID);
}

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

bool init = false;

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	HW_PROFILE_INFO hwid;

	if (GetCurrentHwProfile(&hwid)) {};

	//ïåðåòàùèòü â ëîàäåð
	addHWID(hwid.szHwProfileGuid);
	addHWID("{5fffa4c0-29de-11eb-9669-806e6f6e6963}");

	//if (!checkHWID(hwid)) kiero::shutdown();

	if (!init)
	{
		InitImGui(pDevice);
		init = true;
	}

	if (GetAsyncKeyState(VK_END)) {
		kiero::shutdown();
		return 0;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) showMenu = !showMenu;



	if (showMenu) {
		Sleep(1);
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hack", 0, ImGuiWindowFlags_NoTitleBar);
		
		if (ImGui::Button("Visuals", ImVec2(125.f, 0.f))) tab = 0;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button("AimBot", ImVec2(125.f, 0.f))) tab = 1;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button("Misc", ImVec2(125.f, 0.f))) tab = 2;

		switch (tab)
		{
		case 0:
			ImGui::Checkbox("Wallhack", &Settings.enableWH);
			ImGui::Checkbox("Show teammates", &Settings.enableWH_team);
			ImGui::Separator();
			ImGui::Text("Enemy color (RABOTAET CHEREZ PIZDU)");
			ImGui::SliderInt("Enemy R", &Settings.enemyColorR, 0, 255);
			ImGui::SliderInt("Enemy G", &Settings.enemyColorG, 0, 255);
			ImGui::SliderInt("Enemy B", &Settings.enemyColorB, 0, 255);
			ImGui::Text("Teammate color");
			ImGui::SliderInt("Team R", &Settings.teammateColorR, 0, 255);
			ImGui::SliderInt("Team G", &Settings.teammateColorG, 0, 255);
			ImGui::SliderInt("Team B", &Settings.teammateColorB, 0, 255);
			break;
		case 1:
			ImGui::Checkbox("AimBoba", &Settings.enableAimBot);
			ImGui::SliderInt("Aim FOV", &Settings.aimFOV, 0, 360);
			ImGui::SliderFloat("Smooth", &Settings.smooth, 0.01f, 1.f);
			ImGui::Checkbox("TriggerBot", &Settings.enableTriggerBot);
			ImGui::Checkbox("TriggerBot v2", &Settings.enableTriggerBotV2);
			break;
		case 2:
			ImGui::Checkbox("BunnyHop", &Settings.enableBunnyHop);
			ImGui::Checkbox("RCS", &Settings.enableRCS);
			ImGui::Checkbox("NoFlash", &Settings.enableNoFlash);
			break;
		default:
			break;
		}

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE;

	window = handle;
	return FALSE;
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)& oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}

//ÇÀÊÐÈÏÒÎÂÀÒÜ DLL
BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr); //ÍÅ ÒÐÎÃÀÒÜ
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)WallHackThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)TriggerBotThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)BunnyHopThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)RCSThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)AimBotThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)NoFlashThread, hMod, 0, nullptr);
		//CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ThirdPersonThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
