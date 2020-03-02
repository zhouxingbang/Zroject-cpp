#pragma once
#include <string>
#include "zkernel/zkernelglobal.h"

namespace REFLECT
{
    class IReflectObject
    {
    public:
        virtual ~IReflectObject() {}

    protected:
        IReflectObject() {}
    };

    class IReflectHolder
    {
    public:
        virtual ~IReflectHolder() {}

        class placeholder
        {
        public:
            ~placeholder() {}

        public:
            virtual IReflectObject* CreateType() = 0;

        protected:
            placeholder() {}
        };

        template<class Type>
        class holder : public placeholder
        {
        public:
            IReflectObject* CreateType() override
            {
                return new Type();
            }
        };

    public:
        virtual const std::wstring& GetName() const = 0;

        template<typename Type>
        auto CreateObject() -> Type*
        {
            std::unique_ptr<placeholder> uptrHolder(CreateHolder());
            return dynamic_cast<Type*>(uptrHolder->CreateType());
        }

    protected:
        IReflectHolder() {}

        virtual placeholder* CreateHolder() = 0;
    };

    template <typename Type>
    class CReflectHolder : public IReflectHolder
    {
    public:
        const std::wstring& GetName() const override
        {
            return m_name;
        }
        void SetName(const std::wstring& name)
        {
            m_name = name;
        }

    protected:
        placeholder* CreateHolder() override
        {
            return new holder<Type>();
        }

    private:
        std::wstring m_name;
    };

    ZKERNEL_EXPORT void RegisterReflect(IReflectHolder* pHolder);
    ZKERNEL_EXPORT void UnRegisterReflect(IReflectHolder* pHolder);
    ZKERNEL_EXPORT IReflectHolder* GetReflectHolder(const std::wstring& classId);

    template<typename Type>
    auto Ref_DynCreate_Object(const std::wstring& classId) -> Type*
    {
        IReflectHolder* pReflectHolder = GetReflectHolder(classId);
        if (nullptr == pReflectHolder) return nullptr;
        return pReflectHolder->CreateObject<Type>();
    }

#define REF_DECLARE_DYNCREATE(class_name) \
    public: \
    static REFLECT::CReflectHolder<class_name> class##class_name;

#define REF_IMPLEMENT_DYNCREATE(class_name, class_id) \
    REFLECT::CReflectHolder<class_name> class_name::class##class_name; \
    struct RelectHolder##class_name \
    { \
        RelectHolder##class_name() \
        { \
            class_name::class##class_name.SetName(class_id); \
            RegisterReflect(&class_name::class##class_name); \
        }\
        ~RelectHolder##class_name() \
        {\
            UnRegisterReflect(&class_name::class##class_name); \
        }\
    };\
    static RelectHolder##class_name s_relectHolder##class_name;
}