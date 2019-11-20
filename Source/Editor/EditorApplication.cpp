#include <Cross/Graphics/Graphics.h>
#include <Cross/Engine/EngineDefs.h>
#include <Cross/IO/FileSystem.h>
#include <Cross/Resource/ResourceCache.h>
#include <Cross/IO/Log.h>

#include "EditorApplication.h"


CROSS_DEFINE_APPLICATION_MAIN(EditorApplication)

EditorApplication::EditorApplication(Context* context)
	:Application(context) {

	editorTitle_ = "Cross Application";
	editor_ = new Editor(context);
}

void EditorApplication::Setup()
{
	// Modify engine startup parameters
	engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
	engineParameters_[EP_WINDOW_WIDTH] = 1280;
	engineParameters_[EP_WINDOW_HEIGHT] = 720;
	engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("cross", "logs") + GetTypeName() + ".log";
	engineParameters_[EP_FULL_SCREEN] = false;
	engineParameters_[EP_HEADLESS] = false;
	engineParameters_[EP_SOUND] = false;
	engineParameters_[EP_RESOURCE_PATHS] = "PlayerData;CoreData";

	// Construct a search path to find the resource prefix with two entries:
	// The first entry is an empty path which will be substituted with program/bin directory -- this entry is for binary when it is still in build tree
	// The second and third entries are possible relative paths from the installed program/bin directory to the asset directory -- these entries are for binary when it is in the Cross SDK installation location
	if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
	{
		// TODO: This is dependent on a source build
		String resourcePrefix = ToString("%s/Resources", CROSS_ROOT_SOURCE_DIR);
		engineParameters_[EP_RESOURCE_PREFIX_PATHS] = resourcePrefix;
	}

}

void EditorApplication::Start()
{
	SetWindowTitleAndIcon();
	SubscribeToEvents();

	editor_->SubscribeToEvents();
}

void EditorApplication::Stop()
{
	engine_->DumpResources(true);
}

void EditorApplication::SetWindowTitleAndIcon()
{
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Graphics* graphics = GetSubsystem<Graphics>();
	Image* icon = cache->GetResource<Image>("Images/favicon.png");
	graphics->SetWindowIcon(icon);
	graphics->SetWindowTitle(editorTitle_);
}

void EditorApplication::SubscribeToEvents()
{
	// TODO
}

