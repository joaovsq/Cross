

#include "../Core/Object.h"

namespace Cross
{

CROSS_EVENT(E_PREFABSAVE, PrefabSave)
{
    CROSS_PARAM(P_PREFABCOMPONENT, PrefabComponent); // PrefabComponent Pointer
}

/// Instead of using resource reload system which can be delayed due to file watchers, we explicitly send prefab changes
CROSS_EVENT(E_PREFABCHANGED, PrefabChanged)
{
    CROSS_PARAM(P_GUID, GUID); // String
}

}
