#pragma once

#include "Core.h"
#include <vector>
#include <map>
#include <memory>

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

        inline size_t Length()
        {
            return mArray.size();
        }

        inline bool Exist(const std::string &_name)
        {
            return mMap.find(_name) != mMap.end;
        }

        inline void Remove(const std::string &_name)
        {
            TMap::const_iterator _find = mMap.find(_name);
            if (_find != mMap.end())
            {
                const size_t lIdx = _find->second;
                mMap.erase(_find);
                mArray.erase(mArray.begin() + index);
                for ( auto& it : mMap )
                {
                    if (it.second > lIdx)
                        it.second = it.second - 1;
                }
            }
        }

        virtual std::shared_ptr<T> operator[](size_t _idx) const
        {
            return mArray[_idx];
        }

        virtual std::shared_ptr<T> Get(const std::string &_name) const
        {
            TMap::const_iterator _find = mMap.find(_name);
            return (_find != mMap.end()) ? mArray[_find->second] : nullptr;
        }

        virtual bool Add( const std::string& _name, std::shared_ptr<T> _resource )
        {
            bool lOk = false;
            if (mMap.find(_name) == mMap.end())
            {
                mMap[_name] = mArray.size();
                mArray.push_back(_resource);
                lOk = true;
            }
            return lOk;
        }

        virtual void Clear()
        {
            mArray.clear();
            mMap.clear();
        }

        virtual void Shutdown()
        {
            Clear();
        }

    protected:
        typedef std::vector< std::shared_ptr<T> > TArray;
        typedef std::map< const std::string, size_t > TMap;

        TArray mArray;
        TMap   mMap;
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