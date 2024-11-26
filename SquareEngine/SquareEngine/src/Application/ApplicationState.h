#pragma once

namespace Square
{
	enum class ApplicationState
	{
		Edit = 0, Play
	};

	namespace AppStates
	{
		inline ApplicationState appState;
		inline bool hasChanged = false;

		inline ApplicationState GetAppState()
		{
			return appState;
		}

		inline void SetAppState(ApplicationState s)
		{
			hasChanged = true;
			appState = s;
		}

		inline bool IsPlaying() { return GetAppState() == ApplicationState::Play; }
		inline bool IsEditing() { return GetAppState() == ApplicationState::Edit; }

		inline void BeginEditing() { SetAppState(ApplicationState::Edit); }
		inline void BeginPlaying() { SetAppState(ApplicationState::Play); }

		inline bool HasChanged() { return hasChanged; }
		inline void ReceivedChange() { hasChanged = false; }
	}
}