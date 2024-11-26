#pragma once
#include <chrono>
#include <filesystem>
#include <functional>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "../../Coral.Native/Include/Coral/Array.hpp"
#include "../../Coral.Native/Include/Coral/Attribute.hpp"
#include "../../Coral.Native/Include/Coral/GC.hpp"
#include "../../Coral.Native/Include/Coral/HostInstance.hpp"

#include <memory>
#include <Window.h>

namespace Square
{
	inline std::string truncate(const std::string& input, size_t maxLength) {
		if (input.length() > maxLength) {
			return input.substr(0, maxLength - 3) + "...";
		}
		else {
			return input;
		}
	}

	inline std::vector<std::string> console;

	inline void ClearConsole()
	{
		console.clear();
	}

	inline void AddMessageToConsole(const std::string& message)
	{
		console.push_back(truncate(message, 250) + " : " + std::to_string(GetActiveWindow()->GetTime()));
	}

	struct Assembly
	{
		Coral::ManagedAssembly& coralAssembly;
		std::string assemblyPath;
		Coral::AssemblyLoadContext context;
		Coral::HostInstance host;

		inline Assembly(Coral::ManagedAssembly& coralAsm, const std::string& asmPath, Coral::AssemblyLoadContext ctx, Coral::HostInstance h)
			: coralAssembly(coralAsm), assemblyPath(asmPath), context(ctx), host(h) {}

		inline Assembly operator =(const Assembly& other) {
			return Assembly(other.coralAssembly, other.assemblyPath, other.context, other.host);
		}
	};

	inline void ExceptionCallback(std::string_view InMessage) { AddMessageToConsole(InMessage.data()); };

	Assembly LoadAssembly(int argc, char** argv, const std::string& assemblyDLL);
	Assembly LoadAssembly(int argc, char** argv, const std::string& assemblyDLL, Coral::AssemblyLoadContext& context, Coral::HostInstance& host);
}