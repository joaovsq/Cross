//
// Copyright (c) 2014-2016 THUNDERBEAST GAMES LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <Cross/IO/Log.h>
#include <Cross/IO/File.h>
#include <Cross/IO/FileSystem.h>

#include <Cross/Resource/JSONFile.h>

#include "../ToolSystem.h"
#include "../ToolEnvironment.h"
#include "../ToolEvents.h"

#include "ProjectEvents.h"
#include "ProjectFile.h"
#include "ProjectSettings.h"
#include "ProjectUserPrefs.h"
#include "Project.h"

namespace ToolCore
{

Project::Project(Context* context) :
	Object(context),
	loading_(false)
{
	version_ = "1.0.0";

	projectSettings_ = new ProjectSettings(context_);
	userPrefs_ = new ProjectUserPrefs(context_);
}

Project::~Project()
{

}

void Project::SaveUserPrefs()
{
	String path = GetProjectPath() + "UserPrefs.json";

	userPrefs_->Save(path);
}

bool Project::LoadUserPrefs()
{
	ToolEnvironment* tenv = GetSubsystem<ToolEnvironment>();

	String path = GetProjectPath() + "UserPrefs.json";

	userPrefs_->Load(path);

	// If we're in CLI mode, the Build folder is always relative to project
	if (tenv != nullptr && tenv->GetCLI())
	{
		String path = GetPath(projectFilePath_) + "Build";
		userPrefs_->SetLastBuildPath(path);
	}

	return true;
}

bool Project::LoadProjectSettings()
{
	projectSettings_->Load(GetProjectPath() + "Settings/Project.json");
	return true;
}

bool Project::Load(const String& fullpath)
{
	loading_ = true;

	if (fullpath.Contains(".cross")) {

		projectPath_ = AddTrailingSlash(GetPath(fullpath));
		projectFilePath_ = fullpath;

	}
	else
	{
		projectPath_ = AddTrailingSlash(fullpath);

		FileSystem* fileSystem = GetSubsystem<FileSystem>();
		StringVector results;
		fileSystem->ScanDir(results, projectPath_, "*.cross", SCAN_FILES, false);

		if (!results.Size())
		{
			// no cross file, so use the parent path name
			projectFilePath_ = projectPath_ + GetFileName(RemoveTrailingSlash(projectPath_)) + ".cross";
		}
		else
		{
			String result = projectPath_ + results[0];

			if (results.Size() > 1)
			{
				// multiple *.cross files, use newest, and report

				unsigned newest = 0xFFFFFFFF;

				for (unsigned i = 0; i < results.Size(); i++)
				{
					String crossFilePath = projectPath_ + results[i];

					unsigned modtime = fileSystem->GetLastModifiedTime(crossFilePath);

					if (!modtime)
						continue;

					if (newest > modtime)
					{
						newest = modtime;
						result = crossFilePath;
					}

				}

				CROSS_LOGERRORF("Project::Load - Multiple .cross files found in project, selecting newest: %s", result.CString());

			}

			projectFilePath_ = result;
		}

	}

	VariantMap data;
	data[ProjectBeginLoad::P_PROJECTPATH] = projectFilePath_;
	data[ProjectBeginLoad::P_PROJECT] = this;
	SendEvent(E_PROJECTBEGINLOAD, data);

	SharedPtr<ProjectFile> pfile(new ProjectFile(context_));
	bool result = pfile->Load(this);

	loading_ = false;

	LoadProjectSettings();
	LoadUserPrefs();

	if (true /*result*/) {
		VariantMap data;
		data[ProjectLoaded::P_PROJECTPATH] = projectFilePath_;
		data[ProjectLoaded::P_PROJECT] = this;
		data[ProjectLoaded::P_RESULT] = result;
		SendEvent(E_PROJECTLOADED, data);
	}

	return result;
}

void Project::Create(const String& fullpath)
{
	if (fullpath.Contains(".cross")) {
		projectPath_ = AddTrailingSlash(GetPath(fullpath));
		projectFilePath_ = fullpath;
		Save(fullpath);
	}
	else {
		SharedPtr<ProjectFile> pfile(new ProjectFile(context_));
		pfile->WriteNewProject(fullpath);

		projectPath_ = AddTrailingSlash(GetPath(fullpath));
		projectFilePath_ = fullpath;
	}
}

void Project::Save(const String& fullpath)
{
	SharedPtr<ProjectFile> pfile(new ProjectFile(context_));
	pfile->Save(this);
}

String Project::GetUserPrefsFullPath()
{
	String path = GetPath(projectFilePath_);
	String filename = GetFileName(projectFilePath_);
	String prefsPath = path + filename + ".userprefs";
	return prefsPath;
}

bool Project::IsComponentsDirOrFile(const String& fullPath)
{
	String pathName;
	String fileName;
	String extension;

	SplitPath(fullPath, pathName, fileName, extension);

	if (extension.Length() && extension != ".js")
		return false;

	if (IsAbsoluteParentPath(componentsPath_, pathName))
		return true;

	return false;

}

bool Project::IsScriptsDirOrFile(const String& fullPath)
{
	String pathName;
	String fileName;
	String extension;

	SplitPath(fullPath, pathName, fileName, extension);

	if (extension.Length() && extension != ".js")
		return false;

	if (IsAbsoluteParentPath(scriptsPath_, pathName))
		return true;

	return false;

}

bool Project::IsModulesDirOrFile(const String& fullPath)
{
	String pathName;
	String fileName;
	String extension;

	SplitPath(fullPath, pathName, fileName, extension);

	if (extension.Length() && extension != ".js")
		return false;

	if (IsAbsoluteParentPath(modulesPath_, pathName))
		return true;

	return false;

}


}
