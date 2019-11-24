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

#include <Cross/Core/Context.h>
#include <Cross/Core/CoreEvents.h>
#include <Cross/IO/FileSystem.h>
#include <Cross/Resource/ResourceCache.h>

#include "Assets/AssetDatabase.h"
#include "Subprocess/SubprocessSystem.h"

#include "ToolSystem.h"
#include "ToolEnvironment.h"
#include "ToolEvents.h"

#include "Project/Project.h"
#include "Project/ProjectEvents.h"
#include "Project/ProjectUserPrefs.h"

namespace ToolCore
{

ToolSystem::ToolSystem(Context* context) : Object(context),
    updateDelta_(0.0f)
{
    context_->RegisterSubsystem(new AssetDatabase(context_));
    context_->RegisterSubsystem(new SubprocessSystem(context_));

    SubscribeToEvent(E_UPDATE, CROSS_HANDLER(ToolSystem, HandleUpdate));
}

ToolSystem::~ToolSystem()
{

}

void ToolSystem::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    updateDelta_ += eventData[P_TIMESTEP].GetFloat();
    
    if (updateDelta_ >= 0.5f)
    {
        updateDelta_ = 0.0f;
        SendEvent(E_TOOLUPDATE);
    }

}

bool ToolSystem::LoadProject(const String& fullpath)
{

    String pathName, fileName, ext;

    SplitPath(fullpath, pathName, fileName, ext);

    String path;

    if (ext == ".cross")
    {
        path = RemoveTrailingSlash(GetPath(AddTrailingSlash(pathName)));
    }
    else
    {
        path = RemoveTrailingSlash(GetPath(AddTrailingSlash(fullpath)));
    }

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Do NOT add the root project path as a resource path, otherwise
    // it will introduce a situation where there are nested resource paths
    // which will confuse the ResourceCache and can cause resources referenced
    // by various paths to be seen as unique resources
    //cache->AddResourceDir(path, 0);

    String resourcePath = path;
    resourcePath += "/Resources";
    cache->AddResourceDir(resourcePath, 0);

    project_ = new Project(context_);
    project_->SetResourcePath(resourcePath);

    bool result = project_->Load(fullpath);

    return result;
}

void ToolSystem::CloseProject()
{
    if (project_.Null())
        return;

    SendEvent(E_PROJECTUNLOADED);

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    String projectPath = project_->GetProjectPath();
    String resourcePath = project_->GetResourcePath();

    project_ = 0;

    cache->RemoveResourceDir(resourcePath);
    cache->RemoveResourceDir(projectPath);

    cache->ReleaseAllResources(true);

}

}
