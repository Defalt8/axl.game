#pragma once
#include "../lib.hpp"

namespace axl {
namespace game {
namespace input {

class AXLGAMECXXAPI Touch 
{
	public:
		static bool isPresent();
	private:
		Touch();
		~Touch();
};

} // namespace axl.game.input
} // namespace axl.game
} // namespace axl