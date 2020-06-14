#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "BubbleBobbleGame.h"
#include <SDL.h>

int main(int, char* [])
{
	WindowInfo wi{ "BubbleBobble" };
	BubbleBobbleGame game{ wi.pTitle, wi.Width, wi.Height, wi.MsPerFrame };
	game.Start();
	return 0;
}