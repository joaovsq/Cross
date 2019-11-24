#include <Cross/IO/Log.h>
#include <Cross/IO/File.h>
#include <Cross/IO/FileSystem.h>
#include <Cross/Resource/JSONFile.h>

#include "ProjectSettings.h"

namespace ToolCore
{

    ProjectSettings::ProjectSettings(Context* context) : Object(context),
        desktopSettings_(new DesktopProjectSettings()),
        androidSettings_(new AndroidProjectSettings())
    {
        SetDefault();
    }

    ProjectSettings::~ProjectSettings()
    {

    }

    void ProjectSettings::SetDefault()
    {
        name_ = "CrossProject";
    }
    
    bool ProjectSettings::Load(const String& path)
    {
        FileSystem* fileSystem = GetSubsystem<FileSystem>();

        if (!fileSystem->FileExists(path))
        {
            CROSS_LOGERRORF("No settings specified, using default: %s", path.CString());
            SetDefault();
            return true;
        }

        SharedPtr<File> file(new File(context_, path));
        if (!file->IsOpen())
        {
            CROSS_LOGERRORF("Unable to open settings: %s", path.CString());
            return false;
        }

        SharedPtr<JSONFile> jsonFile(new JSONFile(context_));
        bool result = jsonFile->Load(*file);
        file->Close();

        if (!result)
        {
            CROSS_LOGERRORF("Unable to load settings: %s", path.CString());
            return false;
        }

        JSONValue& root = jsonFile->GetRoot();
        if (!root.IsObject())
        {
            CROSS_LOGERRORF("No root object in settings: %s", path.CString());
            return false;
        }

        name_ = root["name"].GetString();

        if (!name_.Length())
            name_ = "CrossProject";

        desktopSettings_->Read(root);
        androidSettings_->Read(root);

        return true;
    }

    void ProjectSettings::Save(const String& path)
    {
        SharedPtr<JSONFile> jsonFile(new JSONFile(context_));

        JSONValue& root = jsonFile->GetRoot();

        SharedPtr<File> file(new File(context_, path, FILE_WRITE));

        desktopSettings_->Write(root);
        androidSettings_->Write(root);

        jsonFile->Save(*file, String("   "));

        file->Close();
    }

}
