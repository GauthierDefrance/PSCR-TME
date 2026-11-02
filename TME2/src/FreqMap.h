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

            if (isSoonFull(0.8f)) grow();
        }

        // max est compris entre 0 et 1
        bool isSoonFull(float max) {
            return static_cast<double>(nbEntries) / buckets.size() >= 0.8;
        }

        // Exporte toutes les entrées dans un vecteur (utile pour trier ensuite)
        std::vector<WordCount> toKeyValuePairs() const {
            std::vector<WordCount> res;
            // On alloue le nombres de mots dont on aura besoin en mémoire.
            res.reserve(nbEntries);

            //Pour chacun des buckets qu'on a,
            for (const Bucket& b : buckets) {

                //Pour chacun des mots présents dans chaque buckets,
                for (const WordCount& e : b) {

                    //On l'ajoute a notre vector.
                    res.push_back(e);
                }
            }

            //On retourne le résultat.
            return res;
        }

        void grow() {
            std::cout << "--- Growing buckets of size " << buckets.size() << std::endl;

            // On alloue un tableau 2 fois plus grand que le précédent en nombre de buckets.
            std::vector<Bucket> newBuckets(buckets.size() * 2);

            // On parcourt chaque Buckets courant.
            for (Bucket& b : buckets) {

                // Pour chaque mots déjà contenu dans les buckets on :
                for (WordCount& e : b) {
                    // Recalcul l'endroit ou on doit ranger le mot, son Hash % le nombre de bucket actuelle
                    size_t idx = std::hash<std::string>{}(e.first) % newBuckets.size();

                    // On a l'index, on déplace la valeur
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