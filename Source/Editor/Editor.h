#pragma once

#include <Cross/Core/Context.h>
#include <Cross/Core/Object.h>
#include <Cross/UI/SystemUI/MessageBox.h>
#include <ToolCore/Project/Project.h>

using namespace Cross;
using namespace ToolCore;

namespace Editor {

class Editor : public Object
{
	CROSS_OBJECT(Editor, Object)

public:
	Editor(Context* context);

	void SubscribeToEvents();

private:

	// Renders the Editor User Interface
	void RenderUi(StringHash eventType, VariantMap& eventData);
	/// Detects when a new asset is dragged to the window
	void ImportAsset(StringHash eventType, VariantMap& eventData);
	/// Create the default Editor Scene
	void CreateDefaultScene();

	SharedPtr<MessageBox> messageBox_;
	SharedPtr<Project> openProject_;
};

}
