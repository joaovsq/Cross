#pragma once

#include <Cross/Core/Context.h>
#include <Cross/Core/Object.h>
#include <ToolCore/Project/Project.h>
#include <Cross/UI/ImGuiFileBrowser.h>

using namespace Cross;
using namespace ToolCore;

namespace CrossEditor {

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
	/// Process a key input
	void HandleKeyDown(StringHash eventType, VariantMap& eventData);

	/// Creates the scene management menu
	void SceneMenu();
	/// Creates a new scene
	void SaveScene();
	/// Opens a existing scene  
	void OpenScene(const String& filepath);

	/// Creates a new project
	void SaveProject();
	/// Loads a existing project
	void LoadProject(const String& path);

	SharedPtr<Project> project_;
	ImGui::FileBrowser fileBrowser_;
};

}
