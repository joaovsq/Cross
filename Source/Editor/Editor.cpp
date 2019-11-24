#include <Cross/Graphics/Graphics.h>
#include <Cross/Engine/Engine.h>
#include <Cross/Engine/EngineDefs.h>
#include <Cross/IO/FileSystem.h>
#include <Cross/Graphics/Renderer.h>
#include <Cross/Resource/ResourceCache.h>
#include <Cross/IO/Log.h>
#include <Cross/Core/CoreEvents.h>
#include <Cross/UI/SystemUI/SystemUI.h>
#include <Cross/UI/SystemUI/SystemUIEvents.h>
#include <Cross/UI/SystemUI/Console.h>
#include <Cross/Input/Input.h>
#include <Cross/Input/InputEvents.h>
#include <ThirdParty/imgui/imgui.h>

#include "Editor.h"

namespace CEditor {

ImGui::FileBrowser projectBrowser_;

Editor::Editor(Context* context)
	: Object(context) {

	project_ = new Project(context);

	projectBrowser_.SetTitle("Select a Folder or .cross file");
}

void Editor::SubscribeToEvents() {
	SubscribeToEvent(E_SYSTEMUIFRAME, CROSS_HANDLER(Editor, RenderUi));
	SubscribeToEvent(E_DROPFILE, CROSS_HANDLER(Editor, ImportAsset));
	SubscribeToEvent(E_KEYDOWN, CROSS_HANDLER(Editor, HandleKeyDown));
}

void Editor::RenderUi(StringHash eventType, VariantMap& eventData)
{
	ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(15, 15), ImGuiCond_FirstUseEver);
	CreateProject();
}


void Editor::ImportAsset(StringHash eventType, VariantMap& eventData)
{
	using namespace DropFile;

	// Get the file path
	Variant file = eventData[P_FILENAME];
	String filePath = file.GetString();

	CROSS_LOGINFOF("Importing file: %s", filePath);

}

void Editor::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
	if (eventData[KeyDown::P_KEY].GetUInt() == KEY_QUOTE)
		GetSubsystem<Console>()->Toggle();
}

void Editor::CreateProject()
{
	if (ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoSavedSettings))
	{
		if (ImGui::Button("New Project"))
		{
			projectBrowser_.Open();
		}
	}
	ImGui::End();

	projectBrowser_.Display();

	// if a folder or file was selected
	if (projectBrowser_.HasSelected())
	{
		const String path(projectBrowser_.GetSelected().string().c_str());
	
		// save a open project before creating a new one
		if (!project_->GetProjectFilePath().Empty() && !project_->GetProjectPath().Empty()) {
			CROSS_LOGWARNING("There are already a Open Project. Saving the current open project... ");
			project_->Save();
			delete project_;
			project_ = new Project(context_);
		}

		CROSS_LOGINFOF("Loading or creating a new project in path: %s", path);
		project_->Save(path);

		projectBrowser_.ClearSelected();
	}
}

void Editor::LoadProject(const String& path)
{
}

void Editor::CreateDefaultScene()
{



}

}