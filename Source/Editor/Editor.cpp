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

namespace CrossEditor {


Editor::Editor(Context* context)
	: Object(context) {

	project_ = new Project(context);
}

void Editor::SubscribeToEvents()
{
	SubscribeToEvent(E_SYSTEMUIFRAME, CROSS_HANDLER(Editor, RenderUi));
	SubscribeToEvent(E_DROPFILE, CROSS_HANDLER(Editor, ImportAsset));
	SubscribeToEvent(E_KEYDOWN, CROSS_HANDLER(Editor, HandleKeyDown));
}

void Editor::RenderUi(StringHash eventType, VariantMap& eventData)
{
	ImGui::SetNextWindowSize(ImVec2(250, 400), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(15, 15), ImGuiCond_FirstUseEver);

	SceneMenu();
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

void Editor::SceneMenu() {
	ImGui::Begin("Scene Controls", nullptr, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Scenes"))
		{
			if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
			{

			}

			if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {
				CROSS_LOGDEBUG("OPEN scene menu clicked !!!!!");
				// TODO
			}
			if (ImGui::MenuItem("Close Scene", "Ctrl+W")) {
				CROSS_LOGDEBUG("CLOSE scene menu clicked !!!!!");
				// TODO
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::FileBrowser fileBrowser_;
	fileBrowser_.SetTitle("Select a Scene file to save or create");

	if (ImGui::Button("Save Scene"))
		fileBrowser_.Open();
	fileBrowser_.Display();

	// if a folder or file was selected
	if (fileBrowser_.HasSelected())
	{
		const String path(fileBrowser_.GetSelected().string().c_str());
		
		CROSS_LOGINFOF("Scene path selected: %s", path);
		
		//fileBrowser_.ClearSelected();
	}

	ImGui::End();
}

void Editor::SaveScene()
{
	
}

void Editor::OpenScene(const String& filepath)
{
}


void Editor::SaveProject()
{
	ImGui::FileBrowser fileBrowser_;
	fileBrowser_.SetTitle("Select a Project .cross file to save or create");

	if (ImGui::Button("Save Project"))
	{
		fileBrowser_.Open();
	}

	fileBrowser_.Display();

	// if a folder or file was selected
	if (fileBrowser_.HasSelected())
	{
		const String path(fileBrowser_.GetSelected().string().c_str());

		// save a open project before creating a new one
		if (!project_->GetProjectFilePath().Empty() && !project_->GetProjectPath().Empty()) {
			CROSS_LOGWARNING("There are already a Open Project. Saving the current open project... ");
			project_->Save();
			delete project_;
			project_ = new Project(context_);
		}

		CROSS_LOGINFOF("Loading or creating a new project in path: %s", path);
		project_->Save(path);

		fileBrowser_.ClearSelected();
	}
}

void Editor::LoadProject(const String& path)
{
	// TODO
}

}