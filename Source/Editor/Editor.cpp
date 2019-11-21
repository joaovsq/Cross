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
#include <Cross/UI/ImGuiFileBrowser.h>

#include "Editor.h"

namespace CEditor {


Editor::Editor(Context* context)
	: Object(context) {

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
	if (ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoSavedSettings))
	{

		if (ImGui::Button("New Project"))
		{

		}

	}
	ImGui::End();
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

void Editor::CreateDefaultScene()
{



}

}