#pragma once
#include <engine/sv_main.h>

enum class PaintMode_t
{
	PAINT_UIPANELS     = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
};

namespace
{
	/* ==== CENGINEVGUI ===================================================================================================================================================== */
#if defined (GAMEDLL_S0) || defined (GAMEDLL_S1)
	ADDRESS p_CEngineVGui_Paint = g_mGameDll.FindPatternSIMD((std::uint8_t*)"\x89\x54\x24\x10\x55\x56\x41\x55\x48\x81\xEC\x00\x00\x00\x00", "xxxxxxxxxxx????");
	int (*CEngineVGui_Paint)(void* thisptr, PaintMode_t mode) = (int (*)(void*, PaintMode_t))p_CEngineVGui_Paint.GetPtr(); /*41 55 41 56 48 83 EC 78 44 8B EA*/

	ADDRESS p_CEngineVGui_Unknown = g_mGameDll.FindPatternSIMD((std::uint8_t*)"\x4C\x8B\x81\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00\x4C\x3B\xC0\x74\x1F", "xxx????xxx????xxxxx");
	void** (*CEngineVGui_Unknown)(void* thisptr) = (void** (*)(void*))p_CEngineVGui_Unknown.GetPtr(); /*4C 8B 81 ?? ?? ?? ?? 48 8D 05 ?? ?? ?? ?? 4C 3B C0 74 1F*/
#elif defined (GAMEDLL_S2) || defined (GAMEDLL_S3)
	ADDRESS p_CEngineVGui_Paint = g_mGameDll.FindPatternSIMD((std::uint8_t*)"\x41\x55\x41\x56\x48\x83\xEC\x78\x44\x8B\xEA", "xxxxxxxxxxx");
	int (*CEngineVGui_Paint)(void* thisptr, PaintMode_t mode) = (int (*)(void*, PaintMode_t))p_CEngineVGui_Paint.GetPtr(); /*41 55 41 56 48 83 EC 78 44 8B EA*/

	ADDRESS p_CEngineVGui_Unknown = g_mGameDll.FindPatternSIMD((std::uint8_t*)"\x40\x53\x48\x83\xEC\x20\x48\x8D\x05\x00\x00\x00\x00\x48\x8B\xD9\x48\x39\x81\x00\x00\x00\x00\x74\x29", "xxxxxxxxx????xxxxxx????xx");
	void** (*CEngineVGui_Unknown)(void* thisptr) = (void** (*)(void*))p_CEngineVGui_Unknown.GetPtr(); /*40 53 48 83 EC 20 48 8D 05 ?? ?? ?? ?? 48 8B D9 48 39 81 ?? ?? ?? ?? 74 29*/
#endif
	void* g_pEngineVGui = CGameServer__SpawnServer.Offset(0x18).FindPatternSelf("48 ?? ?? ?? ?? ?? 01", ADDRESS::Direction::DOWN, 150).ResolveRelativeAddressSelf(0x3, 0x7).RCast<void*>();
}

///////////////////////////////////////////////////////////////////////////////
class HEngineVGui : public IDetour
{
	virtual void debugp()
	{
		std::cout << "| FUN: CEngineVGui::Paint                   : 0x" << std::hex << std::uppercase << p_CEngineVGui_Paint.GetPtr()   << std::setw(npad) << " |" << std::endl;
		std::cout << "| FUN: CEngineVGui::Unknown                 : 0x" << std::hex << std::uppercase << p_CEngineVGui_Unknown.GetPtr() << std::setw(npad) << " |" << std::endl;
		std::cout << "| VAR: g_pEngineVGui                        : 0x" << std::hex << std::uppercase << g_pEngineVGui                  << std::setw(0)    << " |" << std::endl;
		std::cout << "+----------------------------------------------------------------+" << std::endl;
	}
};
///////////////////////////////////////////////////////////////////////////////

REGISTER(HEngineVGui);