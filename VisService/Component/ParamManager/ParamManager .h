#pragma once
#include <memory>
#include "ParamStorage.h"
#include "LRUCache.h"

template<typename ParamType>
class ParamManager 
{
public:
	ParamManager(ParamStorage<ParamType> storage, size_t cacheSize = 10)
        : storage_(storage), cache_(cacheSize) 
    {
    }

    // ��ȡ���Ȳ黺�棬û������Ӵ洢����
    std::optional<ParamType> Get(const std::string& key) 
    {
        if (auto cached = cache_.Get(key))
        {
            return cached;
        }
        auto loaded = storage_.Load(key);
        if (loaded) 
        {
            cache_.InsertOrAssign(key, *loaded);
        }
        return loaded;
    }

    // �����������ɹ���д�뻺��
    bool Add(const std::string& key, const ParamType& value) 
    {
        if (!storage_.Save(key, value)) return false;
        cache_.InsertOrAssign(key, value);
        return true;
    }

    // ���²������ɹ���ˢ�»���
    bool Update(const std::string& key, const ParamType& value) 
    {
        if (!storage_.Update(key, value)) return false;
        cache_.InsertOrAssign(key, value);
        return true;
    }

    // ɾ���������ɹ���������
    bool Remove(const std::string& key) 
    {
        if (!storage_.Remove(key)) return false;
        cache_.Erase(key);  // ��Ҫ��LRUCache����remove�ӿ�
        return true;
    }

private:
    ParamStorage<ParamType> storage_;
    LRUCache<std::string, ParamType> cache_;

};
