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

/// Complete rebuild of navigation mesh.
CROSS_EVENT(E_NAVIGATION_MESH_REBUILT, NavigationMeshRebuilt)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_MESH, Mesh); // NavigationMesh pointer
}

/// Partial bounding box rebuild of navigation mesh.
CROSS_EVENT(E_NAVIGATION_AREA_REBUILT, NavigationAreaRebuilt)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_MESH, Mesh); // NavigationMesh pointer
    CROSS_PARAM(P_BOUNDSMIN, BoundsMin); // Vector3
    CROSS_PARAM(P_BOUNDSMAX, BoundsMax); // Vector3
}

/// Mesh tile is added to navigation mesh.
CROSS_EVENT(E_NAVIGATION_TILE_ADDED, NavigationTileAdded)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_MESH, Mesh); // NavigationMesh pointer
    CROSS_PARAM(P_TILE, Tile); // IntVector2
}

/// Mesh tile is removed from navigation mesh.
CROSS_EVENT(E_NAVIGATION_TILE_REMOVED, NavigationTileRemoved)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_MESH, Mesh); // NavigationMesh pointer
    CROSS_PARAM(P_TILE, Tile); // IntVector2
}

/// All mesh tiles are removed from navigation mesh.
CROSS_EVENT(E_NAVIGATION_ALL_TILES_REMOVED, NavigationAllTilesRemoved)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_MESH, Mesh); // NavigationMesh pointer
}
/// Crowd agent formation.
CROSS_EVENT(E_CROWD_AGENT_FORMATION, CrowdAgentFormation)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    CROSS_PARAM(P_INDEX, Index); // unsigned
    CROSS_PARAM(P_SIZE, Size); // unsigned
    CROSS_PARAM(P_POSITION, Position); // Vector3 [in/out]
}

/// Crowd agent formation specific to a node.
CROSS_EVENT(E_CROWD_AGENT_NODE_FORMATION, CrowdAgentNodeFormation)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    CROSS_PARAM(P_INDEX, Index); // unsigned
    CROSS_PARAM(P_SIZE, Size); // unsigned
    CROSS_PARAM(P_POSITION, Position); // Vector3 [in/out]
}

/// Crowd agent has been repositioned.
CROSS_EVENT(E_CROWD_AGENT_REPOSITION, CrowdAgentReposition)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    CROSS_PARAM(P_POSITION, Position); // Vector3
    CROSS_PARAM(P_VELOCITY, Velocity); // Vector3
    CROSS_PARAM(P_ARRIVED, Arrived); // bool
    CROSS_PARAM(P_TIMESTEP, TimeStep); // float
}

/// Crowd agent has been repositioned, specific to a node
CROSS_EVENT(E_CROWD_AGENT_NODE_REPOSITION, CrowdAgentNodeReposition)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    CROSS_PARAM(P_POSITION, Position); // Vector3
    CROSS_PARAM(P_VELOCITY, Velocity); // Vector3
    CROSS_PARAM(P_ARRIVED, Arrived); // bool
    CROSS_PARAM(P_TIMESTEP, TimeStep); // float
}

/// Crowd agent's internal state has become invalidated. This is a special case of CrowdAgentStateChanged event.
CROSS_EVENT(E_CROWD_AGENT_FAILURE, CrowdAgentFailure)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    CROSS_PARAM(P_POSITION, Position); // Vector3
    CROSS_PARAM(P_VELOCITY, Velocity); // Vector3
    CROSS_PARAM(P_CROWD_AGENT_STATE, CrowdAgentState); // int
    CROSS_PARAM(P_CROWD_TARGET_STATE, CrowdTargetState); // int
}

/// Crowd agent's internal state has become invalidated. This is a special case of CrowdAgentStateChanged event.
CROSS_EVENT(E_CROWD_AGENT_NODE_FAILURE, CrowdAgentNodeFailure)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    CROSS_PARAM(P_POSITION, Position); // Vector3
    CROSS_PARAM(P_VELOCITY, Velocity); // Vector3
    CROSS_PARAM(P_CROWD_AGENT_STATE, CrowdAgentState); // int
    CROSS_PARAM(P_CROWD_TARGET_STATE, CrowdTargetState); // int
}

/// Crowd agent's state has been changed.
CROSS_EVENT(E_CROWD_AGENT_STATE_CHANGED, CrowdAgentStateChanged)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    CROSS_PARAM(P_POSITION, Position); // Vector3
    CROSS_PARAM(P_VELOCITY, Velocity); // Vector3
    CROSS_PARAM(P_CROWD_AGENT_STATE, CrowdAgentState); // int
    CROSS_PARAM(P_CROWD_TARGET_STATE, CrowdTargetState); // int
}

/// Crowd agent's state has been changed.
CROSS_EVENT(E_CROWD_AGENT_NODE_STATE_CHANGED, CrowdAgentNodeStateChanged)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_CROWD_AGENT, CrowdAgent); // CrowdAgent pointer
    CROSS_PARAM(P_POSITION, Position); // Vector3
    CROSS_PARAM(P_VELOCITY, Velocity); // Vector3
    CROSS_PARAM(P_CROWD_AGENT_STATE, CrowdAgentState); // int
    CROSS_PARAM(P_CROWD_TARGET_STATE, CrowdTargetState); // int
}

/// Addition of obstacle to dynamic navigation mesh.
CROSS_EVENT(E_NAVIGATION_OBSTACLE_ADDED, NavigationObstacleAdded)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_OBSTACLE, Obstacle); // Obstacle pointer
    CROSS_PARAM(P_POSITION, Position); // Vector3
    CROSS_PARAM(P_RADIUS, Radius); // float
    CROSS_PARAM(P_HEIGHT, Height); // float
}

/// Removal of obstacle from dynamic navigation mesh.
CROSS_EVENT(E_NAVIGATION_OBSTACLE_REMOVED, NavigationObstacleRemoved)
{
    CROSS_PARAM(P_NODE, Node); // Node pointer
    CROSS_PARAM(P_OBSTACLE, Obstacle); // Obstacle pointer
    CROSS_PARAM(P_POSITION, Position); // Vector3
    CROSS_PARAM(P_RADIUS, Radius); // float
    CROSS_PARAM(P_HEIGHT, Height); // float
}

}
