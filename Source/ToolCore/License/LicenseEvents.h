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

#pragma once

#include <Cross/Core/Object.h>

using namespace Cross;

namespace ToolCore
{

// requires EULA agreement
CROSS_EVENT(E_LICENSE_EULAREQUIRED, LicenseEulaRequired)
{

}

// EULA agreement accepted
CROSS_EVENT(E_LICENSE_EULAACCEPTED, LicenseEulaAccepted)
{

}

// activation required
CROSS_EVENT(E_LICENSE_ACTIVATIONREQUIRED, LicenseActivationRequired)
{

}

// license verification required
CROSS_EVENT(E_LICENSE_VERIFICATIONREQUIRED, LicenseVerificationRequired)
{

}

// license success
CROSS_EVENT(E_LICENSE_SUCCESS, LicenseSuccess)
{

}

CROSS_EVENT(E_LICENSE_ACTIVATIONSUCCESS, LicenseActivationSuccess)
{
}

CROSS_EVENT(E_LICENSE_ACTIVATIONERROR, LicenseActivationError)
{
    CROSS_PARAM(P_MESSAGE, Message); // String
}

CROSS_EVENT(E_LICENSE_DEACTIVATIONSUCCESS, LicenseDeactivationSuccess)
{
}

CROSS_EVENT(E_LICENSE_DEACTIVATIONERROR, LicenseDeactivationError)
{
    CROSS_PARAM(P_MESSAGE, Message); // String
}


// license error
CROSS_EVENT(E_LICENSE_ERROR, LicenseError)
{

}

}
