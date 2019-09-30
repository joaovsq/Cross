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
#include <Cross/IO/FileSystem.h>
#include <Cross/IO/File.h>

#include "ToolEnvironment.h"


namespace ToolCore
{

bool ToolEnvironment::bootstrapping_ = false;

ToolEnvironment::ToolEnvironment(Context* context) : Object(context),
    cli_(false),
    toolPrefs_(new ToolPrefs(context))
{

}

ToolEnvironment::~ToolEnvironment()
{

}

bool ToolEnvironment::InitFromDistribution()
{
    toolPrefs_->Load();

    FileSystem* fileSystem = GetSubsystem<FileSystem>();

#ifdef CROSS_PLATFORM_WINDOWS
    editorBinary_ = fileSystem->GetProgramDir() + "CrossEditor.exe";
    String resourcesDir = fileSystem->GetProgramDir() + "Resources/";
    playerBinary_ = resourcesDir + "ToolData/Deployment/Windows/x64/CrossPlayer.exe";
#elif CROSS_PLATFORM_LINUX
    editorBinary_ = fileSystem->GetProgramDir() + "CrossEditor";
    String resourcesDir = fileSystem->GetProgramDir() + "Resources/";
    playerBinary_ = resourcesDir + "ToolData/Deployment/Linux/CrossPlayer";
#else
    editorBinary_ = fileSystem->GetProgramDir() + "CrossEditor";
    String resourcesDir = GetPath(RemoveTrailingSlash(fileSystem->GetProgramDir())) + "Resources/";
    playerAppFolder_ = resourcesDir + "ToolData/Deployment/MacOS/CrossPlayer.app/";
#endif

    resourceCoreDataDir_ = resourcesDir + "CoreData";
    resourcePlayerDataDir_ = resourcesDir + "PlayerData";

    toolDataDir_ =  resourcesDir + "ToolData/";

    // CrossNET

#ifdef CROSS_DEBUG
    String config = "Debug";
#else
    String config = "Release";
#endif

    crossNETRootDir_ = resourcesDir + "ToolData/CrossNET/";
    crossNETCoreAssemblyDir_ = crossNETRootDir_ + config + "/";

#ifdef CROSS_PLATFORM_OSX
    monoExecutableDir_ = "/Library/Frameworks/Mono.framework/Versions/Current/Commands/";
    crossNETNuGetBinary_ = monoExecutableDir_ + "nuget";
#endif

    return true;
}

bool ToolEnvironment::Initialize(bool cli)
{
    bool result = true;

    cli_ = cli;
    toolPrefs_->Load();

#ifdef CROSS_DEV_BUILD

    SetRootSourceDir(CROSS_ROOT_SOURCE_DIR);
    SetRootBuildDir(CROSS_ROOT_BUILD_DIR, true);

#else

    if (!bootstrapping_)
    {
        result = InitFromDistribution();

    }
    else
    {
        SetRootSourceDir(CROSS_ROOT_SOURCE_DIR);
        SetRootBuildDir(CROSS_ROOT_BUILD_DIR, true);

    }
#endif

    return result;

}

void ToolEnvironment::SetRootSourceDir(const String& sourceDir)
{
    rootSourceDir_ = AddTrailingSlash(sourceDir);
    resourceCoreDataDir_ = rootSourceDir_ + "Resources/CoreData";
    resourcePlayerDataDir_ = rootSourceDir_ + "Resources/PlayerData";
    resourceEditorDataDir_ = rootSourceDir_ + "Resources/EditorData";
    toolDataDir_ = rootSourceDir_ + "Data/CrossEditor/";

    // CrossNET

#ifdef CROSS_DEBUG
    String config = "Debug";
#else
    String config = "Release";
#endif

    crossNETRootDir_ = rootSourceDir_ + "Artifacts/CrossNET/";
    crossNETCoreAssemblyDir_ = rootSourceDir_ + "Artifacts/CrossNET/" + config + "/";

#if defined CROSS_PLATFORM_WINDOWS || defined CROSS_PLATFORM_LINUX
    crossNETNuGetBinary_ = ToString("%sBuild/Managed/nuget/nuget.exe", rootSourceDir_.CString());
#endif

#ifdef CROSS_PLATFORM_OSX
    monoExecutableDir_ = "/Library/Frameworks/Mono.framework/Versions/Current/Commands/";
    crossNETNuGetBinary_ = monoExecutableDir_ + "nuget";
#endif

}

void ToolEnvironment::SetRootBuildDir(const String& buildDir, bool setBinaryPaths)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    rootBuildDir_ = AddTrailingSlash(buildDir);


    if (setBinaryPaths)
    {
#ifdef CROSS_PLATFORM_WINDOWS

#ifdef _DEBUG
        playerBinary_ = rootBuildDir_ + "Source/CrossPlayer/Application/Debug/CrossPlayer.exe";
        editorBinary_ = rootBuildDir_ + "Source/CrossEditor/Debug/CrossEditor.exe";
#else
        playerBinary_ = rootBuildDir_ + "Source/CrossPlayer/Application/Release/CrossPlayer.exe";
        editorBinary_ = rootBuildDir_ + "Source/CrossEditor/Release/CrossEditor.exe";
#endif

        // some build tools like ninja don't use Release/Debug folders
        if (!fileSystem->FileExists(playerBinary_))
                playerBinary_ = rootBuildDir_ + "Source/CrossPlayer/Application/CrossPlayer.exe";
        if (!fileSystem->FileExists(editorBinary_))
                editorBinary_ = rootBuildDir_ + "Source/CrossEditor/CrossEditor.exe";

        playerAppFolder_ = rootSourceDir_ + "Data/CrossEditor/Deployment/MacOS/CrossPlayer.app";

#elif CROSS_PLATFORM_OSX

#ifdef CROSS_XCODE
        playerBinary_ = rootBuildDir_ + "Source/CrossPlayer/" + CMAKE_INTDIR + "/CrossPlayer.app/Contents/MacOS/CrossPlayer";
        editorBinary_ = rootBuildDir_ + "Source/CrossEditor/" + CMAKE_INTDIR + "/CrossEditor.app/Contents/MacOS/CrossEditor";
#else
        playerBinary_ = rootBuildDir_ + "Source/CrossPlayer/Application/CrossPlayer.app/Contents/MacOS/CrossPlayer";
        playerAppFolder_ = rootBuildDir_ + "Source/CrossPlayer/Application/CrossPlayer.app/";
        editorBinary_ = rootBuildDir_ + "Source/CrossEditor/CrossEditor.app/Contents/MacOS/CrossEditor";
#endif

#else
        playerBinary_ = rootBuildDir_ + "Source/CrossPlayer/Application/CrossPlayer";
        editorBinary_ = rootBuildDir_ + "Source/CrossEditor/CrossEditor";

#endif
    }

}

String ToolEnvironment::GetIOSDeployBinary()
{
    return GetToolDataDir() + "Deployment/IOS/ios-deploy/ios-deploy";
}

void ToolEnvironment::Dump()
{
    CROSS_LOGINFOF("Root Source Dir: %s", rootSourceDir_.CString());
    CROSS_LOGINFOF("Root Build Dir: %s", rootBuildDir_.CString());

    CROSS_LOGINFOF("Core Resource Dir: %s", resourceCoreDataDir_.CString());
    CROSS_LOGINFOF("Player Resource Dir: %s", resourcePlayerDataDir_.CString());
    CROSS_LOGINFOF("Editor Resource Dir: %s", resourceEditorDataDir_.CString());

    CROSS_LOGINFOF("Editor Binary: %s", editorBinary_.CString());
    CROSS_LOGINFOF("Player Binary: %s", playerBinary_.CString());
    CROSS_LOGINFOF("Tool Binary: %s", toolBinary_.CString());


    CROSS_LOGINFOF("Tool Data Dir: %s", toolDataDir_.CString());

    CROSS_LOGINFOF("Deployment Data Dir: %s", deploymentDataDir_.CString());

}

}
