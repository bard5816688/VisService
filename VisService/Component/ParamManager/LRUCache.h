#pragma once
#include <list>
#include <unordered_map>
#include <optional>
#include <chrono>
#include <shared_mutex>
#include <utility>
#include <concepts>
#include <stdexcept>

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>requires std::equality_comparable<Key>
class LRUCache
{
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    struct Entry
    {
        Key key;
        Value value;
        TimePoint timestamp;
    };

    using ListType = std::list<Entry>;
    using ListIterator = typename ListType::iterator;
    using MapType = std::unordered_map<Key, ListIterator, Hash, KeyEqual>;
    using MapIterator = typename MapType::iterator;

    explicit LRUCache(size_t capacity = 10, std::chrono::seconds ttl = std::chrono::seconds(0))
        : maxCapacity_(capacity), ttlDuration_(ttl) {
    }

    [[nodiscard]] std::optional<Value> Get(const Key& key)
    {
        std::shared_lock lock(mutex_);
        auto it = cacheMap_.find(key);
        if (it == cacheMap_.end())
            return std::nullopt;

        if (IsExpired(it->second->timestamp))
        {
            lock.unlock();
            Erase(key); // 清理过期数据
            return std::nullopt;
        }

        // 提升到独占锁以修改顺序
        lock.unlock();
        std::unique_lock uniqueLock(mutex_);
        MoveToFront(it->second);
        it->second->timestamp = Clock::now();
        return it->second->value;
    }

    [[nodiscard]] bool Contains(const Key& key) const
    {
        std::shared_lock lock(mutex_);
        auto it = cacheMap_.find(key);
        return it != cacheMap_.end() && !IsExpired(it->second->timestamp);
    }

    std::pair<MapIterator, bool> InsertOrAssign(const Key& key, const Value& value)
    {
        std::unique_lock lock(mutex_);
        return DoInsert(key, value);
    }

    void Erase(const Key& key)
    {
        std::unique_lock lock(mutex_);
        auto it = cacheMap_.find(key);
        if (it != cacheMap_.end())
        {
            cacheList_.erase(it->second);
            cacheMap_.erase(it);
        }
    }

    void Clear()
    {
        std::unique_lock lock(mutex_);
        cacheList_.clear();
        cacheMap_.clear();
    }

    size_t Size() const
    {
        std::shared_lock lock(mutex_);
        return cacheMap_.size();
    }

    size_t Capacity() const
    {
        return maxCapacity_;
    }

    std::vector<std::pair<Key, Value>> Snapshot() const
    {
        std::shared_lock lock(mutex_);
        std::vector<std::pair<Key, Value>> result;
        for (const auto& entry : cacheList_)
        {
            if (!IsExpired(entry.timestamp))
            {
                result.emplace_back(entry.key, entry.value);
            }
        }
        return result;
    }

private:
    bool IsExpired(const TimePoint& time) const
    {
        if (ttlDuration_.count() == 0)
            return false;
        return Clock::now() - time > ttlDuration_;
    }

    void MoveToFront(ListIterator it)
    {
        cacheList_.splice(cacheList_.begin(), cacheList_, it);
    }

    std::pair<MapIterator, bool> DoInsert(const Key& key, const Value& value)
    {
        auto it = cacheMap_.find(key);
        if (it != cacheMap_.end())
        {
            it->second->value = value;
            it->second->timestamp = Clock::now();
            MoveToFront(it->second);
            return { it, false };
        }

        if (cacheList_.size() >= maxCapacity_)
        {
            const auto& oldKey = cacheList_.back().key;
            cacheMap_.erase(oldKey);
            cacheList_.pop_back();
        }

        cacheList_.emplace_front(Entry{ key, value, Clock::now() });
        auto inserted = cacheMap_.emplace(key, cacheList_.begin());
        return { inserted.first, true };
    }

private:
    size_t maxCapacity_;
    std::chrono::seconds ttlDuration_;
    mutable std::shared_mutex mutex_;
    ListType cacheList_;
    MapType cacheMap_;

};