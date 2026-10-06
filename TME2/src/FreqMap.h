#pragma once

#include <string>
#include <vector>
#include <forward_list>
#include <utility>
#include <functional>
#include <cstddef>

// un mot et son nombre d'occurrences
using WordCount = std::pair<std::string, int>;

// Table de hash dédiée au comptage : associe à chaque mot son nombre d'occurrences.
class FreqMap {

public:
    // Un bucket est une liste simplement chaînée de (mot, compteur).
    using Bucket = std::forward_list<WordCount>;

    // Constructeur : alloue nbBuckets listes vides
    explicit FreqMap(size_t nbBuckets = 1024)
        : buckets(nbBuckets), nbEntries(0) {}

    // Nombre d'entrées (mots distincts)
    size_t size() const {
        return nbEntries;
    }

    // Incrémente le compteur du mot, ou l'insère avec 1 s'il est absent.
    // Un seul parcours du bucket.
    void incrementFrequency(const std::string& word) {
        size_t idx = std::hash<std::string>{}(word) % buckets.size();
        Bucket& b = buckets[idx];

        for (WordCount& e : b) {
            if (e.first == word) {
                e.second++;
                return;
            }
        }
        // absent : insertion en tête, O(1)
        b.emplace_front(word, 1);
        nbEntries++;
    }

    // Exporte toutes les entrées dans un vecteur (utile pour trier ensuite)
    std::vector<WordCount> toKeyValuePairs() const {
        std::vector<WordCount> res;
        res.reserve(nbEntries);
        for (const Bucket& b : buckets) {
            for (const WordCount& e : b) {
                res.push_back(e);
            }
        }
        return res;
    }

    // Bonus : double le nombre de buckets et redistribue les entrées
    void grow() {
        std::vector<Bucket> newBuckets(buckets.size() * 2);
        for (Bucket& b : buckets) {
            for (WordCount& e : b) {
                // le modulo change avec la nouvelle taille : on recalcule l'index
                size_t idx = std::hash<std::string>{}(e.first) % newBuckets.size();
                newBuckets[idx].push_front(std::move(e));
            }
        }
        buckets = std::move(newBuckets);
        // nbEntries ne change pas
    }

private:
    std::vector<Bucket> buckets; // les buckets
    size_t nbEntries;            // le nombre d'entrées
};