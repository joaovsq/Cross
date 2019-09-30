//
// Copyright (c) 2008-2017 the Urho3D project.
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

#include "../Core/Object.h"

namespace Cross
{

/// Frame begin event.
CROSS_EVENT(E_BEGINFRAME, BeginFrame)
{
    CROSS_PARAM(P_FRAMENUMBER, FrameNumber);      // unsigned
    CROSS_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Application-wide logic update event.
CROSS_EVENT(E_UPDATE, Update)
{
    CROSS_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Application-wide logic post-update event.
CROSS_EVENT(E_POSTUPDATE, PostUpdate)
{
    CROSS_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Render update event.
CROSS_EVENT(E_RENDERUPDATE, RenderUpdate)
{
    CROSS_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Post-render update event.
CROSS_EVENT(E_POSTRENDERUPDATE, PostRenderUpdate)
{
    CROSS_PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Frame end event.
CROSS_EVENT(E_ENDFRAME, EndFrame)
{
}

// CROSS BEGIN
/// Updating paused or resumed event.
CROSS_EVENT(E_UPDATESPAUSEDRESUMED, UpdatesPaused)
{
    CROSS_PARAM(P_PAUSED, Paused);            // bool
}
// CROSS END

}
