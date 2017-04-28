#pragma once

#include "Core.h"
#include <vector>
#include <map>

namespace core
{
    template<class T>
    class CStringArrayMap
    {
    public:
        CStringArrayMap() {}
        virtual ~CStringArrayMap()
        {
            Shutdown();
        }

        inline size_t Size()
        {
            return m_ResourcesVector.size();
        }

        inline bool Exist(const std::string &aName)
        {
            return m_ResourcesMap.find(aName) != m_ResourcesMap.end;
        }

        inline void Remove(const std::string &aName)
        {
            CMapResouceValue l_ResourceValue = m_ResourcesMap[aName];
            size_t index = l_ResourceValue.m_Id;
            delete m_ResourcesVector[index];
            delete m_ResourcesMap[aName];
            m_ResourcesMap.erase(aName);
            m_ResourcesVector.erase(m_ResourcesVector.begin() + index);
            for (TMapResources::iterator lItb = m_ResourcesMap.begin(), lIte = m_ResourcesMap.end(); lItb != lIte; ++lItb)
            {
                if (lItb->second->m_Id > index)
                {
                    lItb->second->m_Id--;
                }
            }
        }

        virtual inline T operator[](size_t aId)
        {
            return m_ResourcesVector[aId];
        }

        virtual inline T Get(const std::string &aName)
        {
            TMapResources::const_iterator lItfind = m_ResourcesMap.find(aName);
            return (lItfind != m_ResourcesMap.end()) ? lItfind->second.m_Value : nullptr;
        }

        virtual inline bool Add(const std::string &aName, T Resource)
        {
            bool lOk = false;
            if (m_ResourcesMap.find(aName) == m_ResourcesMap.end())
            {
                m_ResourcesMap.insert(std::pair<std::string, CMapResourceValue>(aName, CMapResourceValue(Resource, m_ResourcesVector.size())));
                m_ResourcesVector.push_back(Resource);
                lOk = true;
            }
            return lOk;
        }

        virtual inline void Clear()
        {
            m_ResourcesMap.clear();
            m_ResourcesVector.clear();
        }

        virtual inline void Shutdown()
        {
            for (auto i : m_ResourcesVector)
                delete i;
            Clear();
        }

    protected:
        class CMapResourceValue
        {
        public:
            T m_Value;
            size_t m_Id;
            CMapResourceValue() { assert(!"Method must not be called"); }
            CMapResourceValue(T aValue, size_t aId) : m_Value(aValue), m_Id(aId) {}
        };

        typedef std::vector<T> TVectorRes;
        typedef std::map<std::string, CMapResourceValue> TMapResources;

        TVectorRes m_ResourcesVector;
        TMapResources	 m_ResourcesMap;
    };

    template<class T>
    class StringMap
    {
    public:
        StringMap() {}
        virtual ~StringMap()
        {
            Shutdown();
        }

        inline bool Exist(const std::string &_name)
        {
            return mMap.find(_name) != mMap.end;
        }

        inline void Remove(const std::string &_name)
        {
            mMap.erase(_name);
        }

        virtual inline T * Get(const std::string &_name)
        {
            return mMap[_name];
        }

        virtual inline bool Add(const std::string &_name, T *Resource)
        {
            bool lOk = false;
            if (mMap.find(_name) == mMap.end())
            {
                mMap.insert(std::make_pair(_name, Resource));
                lOk = true;
            }
            return lOk;
        }

        virtual inline void Update(const std::string &_name, T *aResource)
        {
            TStringMap::iterator lItFind = mMap.find(_name);
            if (lItFind != mMap.end())
            {
                if (itb->second)
                    delete itb->second;
            }
            mMap[_name] = aResource;
        }

        virtual inline void Clear()
        {
            mMap.clear();
        }

        virtual inline void Shutdown()
        {
            for (TStringMap::iterator itb = mMap.begin(), ite = mMap.end(); itb != ite; ++itb)
            {
                if (itb->second)
                    delete itb->second;
            }

            Clear();
        }

    protected:
        typedef std::map<std::string, T*> TStringMap;
        TStringMap	 mMap;
    };
}