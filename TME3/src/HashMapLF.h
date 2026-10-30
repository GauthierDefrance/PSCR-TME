#pragma once

#include <vector>
#include <utility>
#include <cstddef>
#include "ListLF.h"

template<typename K, typename V>
class HashMapLF {
public:

    using Table  = std::vector<ListLF>;

    // Construct with a number of buckets (must be >= 1)
    HashMapLF(std::size_t nbuckets = 20000) : buckets_(nbuckets) {}

    // Increment frequency for the given word
    void incrementFrequency(const K& key, V delta = 1) {
        std::atomic<size_t> idx = std::hash<K>{}(key) % buckets_.size();
        buckets_[idx].incrementCount(key, delta);
    }

    // Convert table contents to a vector of key/value pairs.
    std::vector<std::pair<K,V>> toKeyValuePairs() const {
        std::vector<std::pair<K,V>> out;
        for (const auto &bucket : buckets_) {
            auto temp = bucket.toKeyValuePairs();
            for (const auto &e : temp) {
                out.emplace_back(e.first, e.second);
            }
        }
        return out;
    }

private:
    Table buckets_;
};
