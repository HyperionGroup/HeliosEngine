#pragma once

#include "Types.h"

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

        virtual inline T * operator[](size_t aId)
        {
            return m_ResourcesVector[aId];
        }

        virtual inline T * Get(const std::string &aName)
        {
            TMapResources::const_iterator lItfind = m_ResourcesMap.find(aName);
            return (lItfind != m_ResourcesMap.end()) ? lItfind->second.m_Value : nullptr;
        }

        virtual inline bool Add(const std::string &aName, T *Resource)
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
            T *m_Value;
            size_t m_Id;
            CMapResourceValue() { assert(!"Method must not be called"); }
            CMapResourceValue(T *aValue, size_t aId) : m_Value(aValue), m_Id(aId) {}
        };

        typedef std::vector<T *> TVectorRes;
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

    template<typename T>
    class Array
    {

    protected:

        uint64 size = 0;
        T* data = nullptr;

    public:

        Array()
        {
        }

        explicit Array(uint64 numElements)
        {
            Init(numElements);
        }

        explicit Array(uint64 numElements, T fillValue)
        {
            Init(numElements, fillValue);
        }

        ~Array()
        {
            Shutdown();
        }

        void Init(uint64 numElements)
        {
            Shutdown();

            size = numElements;
            if (size > 0)
                data = new T[size];
        }

        void Shutdown()
        {
            if (data)
            {
                delete[] data;
                data = nullptr;
            }
            size = 0;
        }

        void Init(uint64 numElements, T fillValue)
        {
            Init(numElements);
            Fill(fillValue);
        }

        void Resize(uint64 numElements)
        {
            if (numElements == size)
                return;

            if (numElements == 0)
            {
                Shutdown();
                return;
            }

            T* newData = new T[numElements];
            for (uint64 i = 0; i < size; ++i)
                newData[i] = data[i];

            Shutdown();
            data = newData;
            size = numElements;
        }

        uint64 Size() const
        {
            return size;
        }

        uint64 ElementSize() const
        {
            return sizeof(T);
        }

        uint64 MemorySize() const
        {
            return size * sizeof(T);
        }

        const T& operator[](uint64 idx) const
        {
            assert(idx < size);
            assert(data != nullptr);
            return data[idx];
        }

        T& operator[](uint64 idx)
        {
            assert(idx < size);
            assert(data != nullptr);
            return data[idx];
        }

        const T* Data() const
        {
            return data;
        }

        T* Data()
        {
            return data;
        }

        void Fill(T value)
        {
            for (uint64 i = 0; i < size; ++i)
                data[i] = value;
        }
    };

    template<typename T> class FixedList
    {

    protected:

        Array<T> array;
        uint64 count = 0;

    public:

        FixedList()
        {
        }

        explicit FixedList(uint64 maxCount, uint64 initialCount = 0)
        {
            Init(maxCount, initialCount);
        }

        FixedList(uint64 maxCount, uint64 initialCount, T fillValue)
        {
            Init(maxCount, initialCount, fillValue);
        }

        void Init(uint64 maxCount, uint64 initialCount = 0)
        {
            assert(initialCount < maxCount);
            assert(maxCount > 0);
            array.Init(maxCount);
            count = initialCount;
        }

        void Init(uint64 maxCount, uint64 initialCount, T fillValue)
        {
            Init(maxCount, initialCount);
            array.Fill(fillValue);
        }

        void Shutdown()
        {
            array.Shutdown();
            count = 0;
        }

        uint64 Count() const
        {
            return count;
        }

        uint64 MaxCount() const
        {
            return array.Size();
        }

        const T& operator[](uint64 idx) const
        {
            assert(idx < count);
            return array[idx];
        }

        T& operator[](uint64 idx)
        {
            assert(idx < count);
            return array[idx];
        }

        const T* Data() const
        {
            return array.Data();
        }

        T* Data()
        {
            return array.Data();
        }

        void Fill(T value)
        {
            for (uint64 i = 0; i < count; ++i)
                array[i] = value;
        }

        uint64 Add(T item)
        {
            assert(count < array.Size());
            array[count] = item;
            return count++;
        }

        T& Add()
        {
            assert(count < array.Size());
            const uint64 idx = count++;
            new (&array[idx]) T;
            return array[idx];
        }

        void AddMultiple(T item, uint64 itemCount)
        {
            if (itemCount == 0)
                return;

            assert(count + (itemCount - 1) < array.Size());
            for (uint64 i = 0; i < itemCount; ++i)
                array[i + count] = item;
            count += itemCount;
        }

        void Append(const T* items, uint64 itemCount)
        {
            if (itemCount == 0)
                return;

            assert(count + (itemCount - 1) < array.Size());
            for (uint64 i = 0; i < itemCount; ++i)
                array[i + count] = items[i];
            count += itemCount;
        }

        void Insert(T item, uint64 idx)
        {
            assert(count < array.Size());
            assert(idx <= count);
            if (idx == count)
            {
                Add(item);
                return;
            }

            for (int64 i = count; i > int64(idx); --i)
                array[i] = array[i - 1];

            array[idx] = item;
            ++count;
        }

        void Remove(uint64 idx)
        {
            assert(idx < count);
            for (uint64 i = idx; i < count - 1; ++i)
                array[i] = array[i + 1];
            --count;
        }

        void Remove(uint64 idx, T fillValue)
        {
            Remove(idx);
            array[count] = fillValue;
        }

        void RemoveMultiple(uint64 idx, uint64 numItems)
        {
            assert(idx < count);
            assert(idx + numItems <= count);
            for (uint64 i = idx + numItems; i < count; ++i)
                array[i - numItems] = array[i];
            count -= numItems;
        }

        void RemoveAll()
        {
            count = 0;
        }

        void RemoveAll(T fillValue)
        {
            uint64 oldCount = count;
            RemoveAll();
            for (uint64 i = 0; i < oldCount; ++i)
                array[i] = fillValue;
        }
    };

    template<typename T> class GrowableList
    {

    protected:

        Array<T> array;
        uint64 count = 0;

    public:

        GrowableList()
        {
        }

        explicit GrowableList(uint64 initialMaxCount, uint64 initialCount = 0)
        {
            Init(initialMaxCount, initialCount);
        }

        GrowableList(uint64 initialMaxCount, uint64 initialCount, T fillValue)
        {
            Init(initialMaxCount, initialCount, fillValue);
        }

        void Init(uint64 initialMaxCount, uint64 initialCount = 0)
        {
            array.Init(initialMaxCount);
            count = initialCount;
        }

        void Init(uint64 initialMaxCount, uint64 initialCount, T fillValue)
        {
            Init(initialMaxCount, initialCount);
            array.Fill(fillValue);
        }

        void Shutdown()
        {
            array.Shutdown();
            count = 0;
        }

        uint64 Count() const
        {
            return count;
        }

        uint64 CurrentMaxCount() const
        {
            return array.Size();
        }

        const T& operator[](uint64 idx) const
        {
            assert(idx < count);
            return array[idx];
        }

        T& operator[](uint64 idx)
        {
            assert(idx < count);
            return array[idx];
        }

        const T* Data() const
        {
            return array.Data();
        }

        T* Data()
        {
            return array.Data();
        }

        void Fill(T value)
        {
            for (uint64 i = 0; i < count; ++i)
                array[i] = value;
        }

        void Reserve(uint64 newMaxSize)
        {
            if (newMaxSize <= array.Size())
                return;

            uint64 arraySize = array.Size();
            if (arraySize == 0)
                arraySize = 16;

            while (newMaxSize > arraySize)
                arraySize *= 2;

            array.Resize(arraySize);
        }

        uint64 Add(T item)
        {
            Reserve(count + 1);

            array[count] = item;
            return count++;
        }

        void AddMultiple(T item, uint64 itemCount)
        {
            if (itemCount == 0)
                return;

            Reserve(count + itemCount);

            for (uint64 i = 0; i < itemCount; ++i)
                array[i + count] = item;
            count += itemCount;
        }

        void Append(const T* items, uint64 itemCount)
        {
            if (itemCount == 0)
                return;

            Reserve(count + itemCount);

            for (uint64 i = 0; i < itemCount; ++i)
                array[i + count] = items[i];
            count += itemCount;
        }

        void Insert(T item, uint64 idx)
        {
            assert(idx <= count);
            if (idx == count)
            {
                Add(item);
                return;
            }

            Reserve(count + 1);

            for (int64 i = count; i > int64(idx); --i)
                array[i] = array[i - 1];

            array[idx] = item;
            ++count;
        }

        void Remove(uint64 idx)
        {
            assert(idx < count);
            for (uint64 i = idx; i < count - 1; ++i)
                array[i] = array[i + 1];
            --count;
        }

        void Remove(uint64 idx, T fillValue)
        {
            Remove(idx);
            array[count] = fillValue;
        }

        void RemoveMultiple(uint64 idx, uint64 numItems)
        {
            assert(idx < count);
            assert(idx + numItems <= count);
            for (uint64 i = idx + numItems; i < count; ++i)
                array[i - numItems] = array[i];
            count -= numItems;
        }

        void RemoveAll()
        {
            count = 0;
        }

        void RemoveAll(T fillValue)
        {
            uint64 oldCount = count;
            RemoveAll();
            for (uint64 i = 0; i < oldCount; ++i)
                array[i] = fillValue;
        }
    };
}