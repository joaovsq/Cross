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

#include <Cross/Core/Object.h>
#include <Cross/IO/FileSystem.h>

using namespace Cross;

namespace ToolCore
{

class ProjectUserPrefs;
class ProjectSettings;

class Project : public Object
{
	friend class ProjectFile;

	CROSS_OBJECT(Project, Object);

public:
	/// Construct.
	Project(Context* context);
	/// Destruct.
	virtual ~Project();

	bool Load(const String& fullpath);
	void Create(const String& fullpath = "");
	void Save(const String& fullpath = "");

	/// Paths
	const String& GetResourcePath() { return resourcePath_; }
	void SetResourcePath(const String& resourcePath)
	{
		resourcePath_ = AddTrailingSlash(resourcePath);
		componentsPath_ = resourcePath_ + "Components";
		scriptsPath_ = resourcePath_ + "Scripts";
		modulesPath_ = resourcePath_ + "Modules";
	}

	const String& GetComponentsPath() { return componentsPath_; }
	const String& GetScriptsPath() { return scriptsPath_; }
	const String& GetModulesPath() { return modulesPath_; }

	bool IsComponentsDirOrFile(const String& fullPath);
	bool IsScriptsDirOrFile(const String& fullPath);
	bool IsModulesDirOrFile(const String& fullPath);

	ProjectUserPrefs* GetUserPrefs() { return userPrefs_; }
	ProjectSettings* GetProjectSettings() { return projectSettings_; }

	const String& GetProjectPath() const { return projectPath_; }
	const String& GetProjectFilePath() { return projectFilePath_; }
	String GetUserPrefsFullPath();

	const String& GetVersion() { return version_; }
	void SetVersion(const String& version) { version_ = version; }

	bool LoadProjectSettings();

	void SaveUserPrefs();
	bool LoadUserPrefs();

private:

	String version_;

	String projectPath_;
	String projectFilePath_;
	String resourcePath_;

	String componentsPath_;
	String scriptsPath_;
	String modulesPath_;

	bool loading_;
	
	SharedPtr<ProjectUserPrefs> userPrefs_;
	SharedPtr<ProjectSettings> projectSettings_;
};

}
