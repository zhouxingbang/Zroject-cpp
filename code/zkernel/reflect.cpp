#include "stdafx.h"
#include "zkernel/reflect.h"

#include <map>
#include <cassert>

namespace REFLECT
{
    std::map<std::wstring, IReflectHolder*>& GetRefMap()
    {
        static std::map<std::wstring, IReflectHolder*> s_mapReflect;
        return s_mapReflect;
    }

    void RegisterReflect(IReflectHolder* pHolder)
    {
        auto itr = GetRefMap().find(pHolder->GetName());
        assert(itr == GetRefMap().end());
        GetRefMap()[pHolder->GetName()] = pHolder;
    }

    void UnRegisterReflect(IReflectHolder* pHolder)
    {
        GetRefMap().erase(pHolder->GetName());
    }

    IReflectHolder* GetReflectHolder(const std::wstring& classId)
    {
        auto itr = GetRefMap().find(classId);
        return itr == GetRefMap().end() ? nullptr : itr->second;
    }
}