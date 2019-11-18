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
#include <ThirdParty/imgui/imgui.h>

#include "Editor.h"


Editor::Editor(Context* context)
	: Object(context) {

}

void Editor::SubscribeToEvents() {
	SubscribeToEvent(E_SYSTEMUIFRAME, CROSS_HANDLER(Editor, RenderUi));
}

void Editor::RenderUi(StringHash eventType, VariantMap& eventData)
{
	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(200, 300), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Sample SystemUI", 0, ImGuiWindowFlags_NoSavedSettings))
	{
		if (messageBox_.NotNull())
		{
			if (ImGui::Button("Close message box"))
				messageBox_ = nullptr;
		}
		else
		{
			if (ImGui::Button("Show message box"))
			{
				messageBox_ = new MessageBox(context_, "Hello from SystemUI", "Sample Message Box");
				SubscribeToEvent(E_MESSAGEACK, [&](StringHash, VariantMap&) {
					messageBox_ = nullptr;
					}
				);
			}
		}

		if (ImGui::Button("Toggle console"))
			GetSubsystem<Console>()->Toggle();
	}
	ImGui::End();
}


void Editor::ImportAsset()
{

}

void Editor::CreateDefaultScene()
{

}
