#ifndef POPULATIONMANAGER_H
#define POPULATIONMANAGER_H
#include <vector>
#include "dna.h"
#define MUTATION  0.0005

class PopulationManager
{
public:
    PopulationManager();
    void reset();

    int getGeneration() const;
    void setGeneration(int value);
    void inicializePopulation(int maxPopulation);
    void setProbabilityForEach();
    void sortByFitness();
    std::vector<DNA> getPopulation() const;
    void setPopulation(const std::vector<DNA> &value);
    void updatePopulation(std::vector<DNA> value);
    void createNextGeneration();
    std::vector<DNA> population;


private:
    //std::vector<DNA> population;
    DNA createRandom();
    DNA obtainRandomFromPool();
    int generation = 0;
    int maxPopulation=0;
    int getMaxPopulation() const;
    void setMaxPopulation(int value);
    void sortByFitness(std::vector<DNA> *, int left, int right);
};

#endif // POPULATIONMANAGER_H
