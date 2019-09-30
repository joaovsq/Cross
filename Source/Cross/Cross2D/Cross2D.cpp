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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Cross2D/AnimatedSprite2D.h"
#include "../Cross2D/AnimationSet2D.h"
#include "../Cross2D/CollisionBox2D.h"
#include "../Cross2D/CollisionChain2D.h"
#include "../Cross2D/CollisionCircle2D.h"
#include "../Cross2D/CollisionEdge2D.h"
#include "../Cross2D/CollisionPolygon2D.h"
#include "../Cross2D/Constraint2D.h"
#include "../Cross2D/ConstraintDistance2D.h"
#include "../Cross2D/ConstraintFriction2D.h"
#include "../Cross2D/ConstraintGear2D.h"
#include "../Cross2D/ConstraintMotor2D.h"
#include "../Cross2D/ConstraintMouse2D.h"
#include "../Cross2D/ConstraintPrismatic2D.h"
#include "../Cross2D/ConstraintPulley2D.h"
#include "../Cross2D/ConstraintRevolute2D.h"
#include "../Cross2D/ConstraintRope2D.h"
#include "../Cross2D/ConstraintWeld2D.h"
#include "../Cross2D/ConstraintWheel2D.h"
#include "../Cross2D/ParticleEffect2D.h"
#include "../Cross2D/ParticleEmitter2D.h"
#include "../Cross2D/PhysicsWorld2D.h"
#include "../Cross2D/Renderer2D.h"
#include "../Cross2D/RigidBody2D.h"
#include "../Cross2D/Sprite2D.h"
#include "../Cross2D/SpriteSheet2D.h"
#include "../Cross2D/TileMap2D.h"
#include "../Cross2D/TileMapLayer2D.h"
#include "../Cross2D/TmxFile2D.h"

// CROSS BEGIN

#include "../Cross2D/Light2D.h"

// CROSS END

#include "../DebugNew.h"

namespace Cross
{

const char* CROSS2D_CATEGORY = "Cross2D";

void RegisterCross2DLibrary(Context* context)
{
    Renderer2D::RegisterObject(context);

    Sprite2D::RegisterObject(context);
    SpriteSheet2D::RegisterObject(context);

    // Must register objects from base to derived order
    Drawable2D::RegisterObject(context);
    StaticSprite2D::RegisterObject(context);

    AnimationSet2D::RegisterObject(context);
    AnimatedSprite2D::RegisterObject(context);

    ParticleEffect2D::RegisterObject(context);
    ParticleEmitter2D::RegisterObject(context);

    TmxFile2D::RegisterObject(context);
    TileMap2D::RegisterObject(context);
    TileMapLayer2D::RegisterObject(context);

    PhysicsWorld2D::RegisterObject(context);
    RigidBody2D::RegisterObject(context);

    CollisionShape2D::RegisterObject(context);
    CollisionBox2D::RegisterObject(context);
    CollisionChain2D::RegisterObject(context);
    CollisionCircle2D::RegisterObject(context);
    CollisionEdge2D::RegisterObject(context);
    CollisionPolygon2D::RegisterObject(context);

    Constraint2D::RegisterObject(context);
    ConstraintDistance2D::RegisterObject(context);
    ConstraintFriction2D::RegisterObject(context);
    ConstraintGear2D::RegisterObject(context);
    ConstraintMotor2D::RegisterObject(context);
    ConstraintMouse2D::RegisterObject(context);
    ConstraintPrismatic2D::RegisterObject(context);
    ConstraintPulley2D::RegisterObject(context);
    ConstraintRevolute2D::RegisterObject(context);
    ConstraintRope2D::RegisterObject(context);
    ConstraintWeld2D::RegisterObject(context);
    ConstraintWheel2D::RegisterObject(context);

// CROSS BEGIN

    Light2DGroup::RegisterObject(context);
    Light2D::RegisterObject(context);
    DirectionalLight2D::RegisterObject(context);
    PositionalLight2D::RegisterObject(context);
    PointLight2D::RegisterObject(context);

// CROSS END
}

}
