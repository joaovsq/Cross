
#include <Cross/Core/StringUtils.h>
#include "CrossGitSHA.h"
#include "CrossBuildInfo.h"

namespace Cross
{

String CrossBuildInfo::GetBuildString()
{
    return ToString("(%s): %s %s Git: %s", GetBuildName().CString(), GetBuildDate().CString(), GetBuildTime().CString(), GetGitSHA().CString());
}

String CrossBuildInfo::GetGitSHA()
{
    return CROSS_BUILDINFO_GITSHA;
}

String CrossBuildInfo::GetBuildDate()
{
    return __DATE__;
}

String CrossBuildInfo::GetBuildTime()
{
    return __TIME__;
}

String CrossBuildInfo::GetBuildName()
{
#ifdef CROSS_BUILD_NAME
    return CROSS_BUILD_NAME;
#else
    return "The Unamable";
#endif
}

bool CrossBuildInfo::GetDevBuild()
{
#ifdef CROSS_DEV_BUILD
    return true;
#else
    return false;
#endif
}

bool CrossBuildInfo::GetDistBuild()
{
#ifdef CROSS_BUILD_DIST
    return true;
#else
    return false;
#endif
}

#ifndef CROSS_BUILD_VENDOR
static String buildVendor("Unknown Vendor");
#else
static String buildVendor(CROSS_BUILD_VENDOR);
#endif

const String& CrossBuildInfo::GetBuildVendor()
{
    return buildVendor;
}



}
