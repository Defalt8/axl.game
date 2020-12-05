#include <axl.game/input/KeyCodes.hpp>

const char* CStrKeyCode(axl::game::input::KeyCode key_code)
{
	using namespace axl::game::input;
	switch (key_code)
	{
		case KEY_CANCEL: return "KEY_CANCEL";
		case KEY_BACK: return "KEY_BACK";
		case KEY_TAB: return "KEY_TAB";
		case KEY_CLEAR: return "KEY_CLEAR";
		case KEY_RETURN: return "KEY_RETURN";
		case KEY_SHIFT: return "KEY_SHIFT";
		case KEY_LSHIFT: return "KEY_LSHIFT";
		case KEY_RSHIFT: return "KEY_RSHIFT";
		case KEY_CONTROL: return "KEY_CONTROL";
		case KEY_LCONTROL: return "KEY_LCONTROL";
		case KEY_RCONTROL: return "KEY_RCONTROL";
		case KEY_ALT: return "KEY_ALT";
		case KEY_LALT: return "KEY_LALT";
		case KEY_RALT: return "KEY_RALT";
		case KEY_CMD: return "KEY_CMD";
		case KEY_LCMD: return "KEY_LCMD";
		case KEY_RCMD: return "KEY_RCMD";
		case KEY_PAUSE: return "KEY_PAUSE";
		case KEY_CAPITAL: return "KEY_CAPITAL";
		case KEY_ESCAPE: return "KEY_ESCAPE";
		case KEY_SPACE: return "KEY_SPACE";
		case KEY_PAGEUP: return "KEY_PAGEUP";
		case KEY_PAGEDOWN: return "KEY_PAGEDOWN";
		case KEY_END: return "KEY_END";
		case KEY_HOME: return "KEY_HOME";
		case KEY_LEFT: return "KEY_LEFT";
		case KEY_UP: return "KEY_UP";
		case KEY_RIGHT: return "KEY_RIGHT";
		case KEY_DOWN: return "KEY_DOWN";
		case KEY_SELECT: return "KEY_SELECT";
		case KEY_EXEC: return "KEY_EXEC";
		case KEY_SNAPSHOT: return "KEY_SNAPSHOT";
		case KEY_INSERT: return "KEY_INSERT";
		case KEY_DELETE: return "KEY_DELETE";
		case KEY_HELP: return "KEY_HELP";
		case KEY_0: return "KEY_0";
		case KEY_1: return "KEY_1";
		case KEY_2: return "KEY_2";
		case KEY_3: return "KEY_3";
		case KEY_4: return "KEY_4";
		case KEY_5: return "KEY_5";
		case KEY_6: return "KEY_6";
		case KEY_7: return "KEY_7";
		case KEY_8: return "KEY_8";
		case KEY_9: return "KEY_9";
		case KEY_A: return "KEY_A";
		case KEY_B: return "KEY_B";
		case KEY_C: return "KEY_C";
		case KEY_D: return "KEY_D";
		case KEY_E: return "KEY_E";
		case KEY_F: return "KEY_F";
		case KEY_G: return "KEY_G";
		case KEY_H: return "KEY_H";
		case KEY_I: return "KEY_I";
		case KEY_J: return "KEY_J";
		case KEY_K: return "KEY_K";
		case KEY_L: return "KEY_L";
		case KEY_M: return "KEY_M";
		case KEY_N: return "KEY_N";
		case KEY_O: return "KEY_O";
		case KEY_P: return "KEY_P";
		case KEY_Q: return "KEY_Q";
		case KEY_R: return "KEY_R";
		case KEY_S: return "KEY_S";
		case KEY_T: return "KEY_T";
		case KEY_U: return "KEY_U";
		case KEY_V: return "KEY_V";
		case KEY_W: return "KEY_W";
		case KEY_X: return "KEY_X";
		case KEY_Y: return "KEY_Y";
		case KEY_Z: return "KEY_Z";
		case KEY_NUMPAD0: return "KEY_NUMPAD0";
		case KEY_NUMPAD1: return "KEY_NUMPAD1";
		case KEY_NUMPAD2: return "KEY_NUMPAD2";
		case KEY_NUMPAD3: return "KEY_NUMPAD3";
		case KEY_NUMPAD4: return "KEY_NUMPAD4";
		case KEY_NUMPAD5: return "KEY_NUMPAD5";
		case KEY_NUMPAD6: return "KEY_NUMPAD6";
		case KEY_NUMPAD7: return "KEY_NUMPAD7";
		case KEY_NUMPAD8: return "KEY_NUMPAD8";
		case KEY_NUMPAD9: return "KEY_NUMPAD9";
		case KEY_MULTIPLY: return "KEY_MULTIPLY";
		case KEY_ADD: return "KEY_ADD";
		case KEY_SEPARATOR: return "KEY_SEPARATOR";
		case KEY_SUBTRACT: return "KEY_SUBTRACT";
		case KEY_DECIMAL: return "KEY_DECIMAL";
		case KEY_DIVIDE: return "KEY_DIVIDE";
		case KEY_F1: return "KEY_F1";
		case KEY_F2: return "KEY_F2";
		case KEY_F3: return "KEY_F3";
		case KEY_F4: return "KEY_F4";
		case KEY_F5: return "KEY_F5";
		case KEY_F6: return "KEY_F6";
		case KEY_F7: return "KEY_F7";
		case KEY_F8: return "KEY_F8";
		case KEY_F9: return "KEY_F9";
		case KEY_F10: return "KEY_F10";
		case KEY_F11: return "KEY_F11";
		case KEY_F12: return "KEY_F12";
		case KEY_F13: return "KEY_F13";
		case KEY_F14: return "KEY_F14";
		case KEY_F15: return "KEY_F15";
		case KEY_F16: return "KEY_F16";
		case KEY_F17: return "KEY_F17";
		case KEY_F18: return "KEY_F18";
		case KEY_F19: return "KEY_F19";
		case KEY_F20: return "KEY_F20";
		case KEY_F21: return "KEY_F21";
		case KEY_F22: return "KEY_F22";
		case KEY_F23: return "KEY_F23";
		case KEY_F24: return "KEY_F24";
		case KEY_NUMLOCK: return "KEY_NUMLOCK";
		case KEY_SCROLL: return "KEY_SCROLL";
		case KEY_PRINT: return "KEY_PRINT";
		case KEY_APPS: return "KEY_APPS";
		case KEY_SLEEP: return "KEY_SLEEP";
		case KEY_VOLUME_MUTE: return "KEY_VOLUME_MUTE";
		case KEY_VOLUME_DOWN: return "KEY_VOLUME_DOWN";
		case KEY_VOLUME_UP: return "KEY_VOLUME_UP";
		case KEY_MEDIA_NEXT_TRACK: return "KEY_MEDIA_NEXT_TRACK";
		case KEY_MEDIA_PREV_TRACK: return "KEY_MEDIA_PREV_TRACK";
		case KEY_MEDIA_STOP: return "KEY_MEDIA_STOP";
		case KEY_MEDIA_PLAY_PAUSE: return "KEY_MEDIA_PLAY_PAUSE";
		case KEY_LAUNCH_MAIL: return "KEY_LAUNCH_MAIL";
		case KEY_LAUNCH_MEDIA_SELECT: return "KEY_LAUNCH_MEDIA_SELECT";
		case KEY_LAUNCH_APP1: return "KEY_LAUNCH_APP1";
		case KEY_LAUNCH_APP2: return "KEY_LAUNCH_APP2";
		case KEY_TILDE: return "KEY_TILDE";
		case KEY_MINUS: return "KEY_MINUS";
		case KEY_EQUALS: return "KEY_EQUALS";
		case KEY_OPENBRACE: return "KEY_OPENBRACE";
		case KEY_CLOSEBRACE: return "KEY_CLOSEBRACE";
		case KEY_BACKSLASH: return "KEY_BACKSLASH";
		case KEY_FORWARDSLASH: return "KEY_FORWARDSLASH";
		case KEY_SEMICOLON: return "KEY_SEMICOLON";
		case KEY_QUOTE: return "KEY_QUOTE";
		case KEY_COMMA: return "KEY_COMMA";
		case KEY_PERIOD: return "KEY_PERIOD";
	}
	return "KEY_UNKNOWN";
}