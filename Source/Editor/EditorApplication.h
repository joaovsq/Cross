#pragma once

#include <Cross/Engine/Application.h>
#include "Editor.h"

using namespace Cross;

class EditorApplication : public Application 
{
	CROSS_OBJECT(EditorApplication, Application)

public:

	EditorApplication(Context* context);

	/// Setup before engine initialization. Modifies the engine parameters.
	virtual void Setup();
	/// Setup after engine initialization. Creates the logo, console & debug HUD.
	virtual void Start();
	/// Cleanup after the main loop. Called by Application.
	virtual void Stop();

protected:

private:

	/// Defines the main window title and icon
	void SetWindowTitleAndIcon();
	/// Subscribe to all editor events
	void SubscribeToEvents();

	String editorTitle_;
	SharedPtr<Editor> editor_;
};

