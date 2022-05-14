#include "includes.h"

DWORD GameEngine::moduleBase() {
	return (DWORD)GetModuleHandleA("client.dll");
}

DWORD GameEngine::engineBase() {
	return (DWORD)GetModuleHandleA("engine.dll");
}