#pragma once

namespace Square
{
	class GameLayer
	{
	public:
		GameLayer() = default;
		virtual ~GameLayer() {};
		virtual void Run(int argc, char** argv) {};
	};
}