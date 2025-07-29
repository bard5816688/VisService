#pragma once
#include <memory>
#include "ParamStorage.h"
#include "LRUCache.h"

template<typename ParamType>
class ParamManager 
{
public:
	ParamManager(std::string storagePath, size_t cacheSize = 10)
        : cache_(cacheSize)
    {
		storage_ = std::make_shared<ParamStorage<ParamType>>(QString::fromStdString(storagePath));
    }

    // 读取，先查缓存，没命中则从存储加载
    std::optional<ParamType> Get(const std::string& key) 
    {
        if (auto cached = cache_.Get(key))
        {
            return cached;
        }
        auto loaded = storage_->Load(key);
        if (loaded) 
        {
            cache_.InsertOrAssign(key, *loaded);
        }
        return loaded;
    }

    // 新增参数，成功后写入缓存
    bool Add(const std::string& key, const ParamType& value) 
    {
        if (!storage_->Save(key, value)) return false;
        cache_.InsertOrAssign(key, value);
        return true;
    }

    // 更新参数，成功后刷新缓存
    bool Update(const std::string& key, const ParamType& value) 
    {
        if (!storage_->Update(key, value)) return false;
        cache_.InsertOrAssign(key, value);
        return true;
    }

    // 删除参数，成功后清理缓存
    bool Remove(const std::string& key) 
    {
        if (!storage_->Remove(key)) return false;
        cache_.Erase(key);  // 需要给LRUCache增加remove接口
        return true;
    }

private:
	std::shared_ptr<ParamStorage<ParamType>> storage_;
    LRUCache<std::string, ParamType> cache_;

};
