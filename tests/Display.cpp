#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <axl.game/Application.hpp>

const char* rotationStr(axl::game::DisplaySetting::Rotation rot)
{
	switch (rot)
	{
		case axl::game::DisplaySetting::ROT_DEFAULT: return "DEFAULT|CCW_0";
		case axl::game::DisplaySetting::ROT_CCW_90: return "CCW_90";
		case axl::game::DisplaySetting::ROT_CCW_180: return "CCW_180";
		case axl::game::DisplaySetting::ROT_CCW_270: return "CCW_270";
	}
	return "-";
}

void terminating()
{
	// restore default display setting
	axl::game::Application::restoreDisplaySettings();
}

int main()
{
	using namespace axl::game;
	std::atexit(terminating);
	DisplaySetting ds;
	int index = 0;
	while(Application::enumDisplaySettings(&ds, index++))
	{
		char buffer[256];
		printf("%d: BPP(%d) SIZE(%dx%d) FREQ(%d) ROT(%s)\n", index, ds.bits_per_pixel, ds.width, ds.height, ds.frequency, rotationStr(ds.rotation));
GET_INPUT_1:
		printf("Try setting(Y) | Skip(*) | Reset(R) | Reset and Quit(Q): ");
		scanf("%s", buffer);
		if(0 == strnicmp(buffer, "R", 256))
		{
			Application::restoreDisplaySettings();
			goto GET_INPUT_1;
		}
		else if(0 == strnicmp(buffer, "Q", 256))
		{
			return 0;
		}
		else if(0 != strnicmp(buffer, "Y", 256))
			continue;
		if(!Application::setDisplaySettings(ds, true))
			puts("Failed!");
		else
		{
			Application::setDisplaySettings(ds, false);
		}
	}
	return 0;
}