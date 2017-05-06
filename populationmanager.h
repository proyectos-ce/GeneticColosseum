#ifndef POPULATIONMANAGER_H
#define POPULATIONMANAGER_H
#include <vector>
#include "dna.h"

class PopulationManager
{
public:
    PopulationManager();
    void reset();

    int getGeneration() const;
    void setGeneration(int value);
    void inicializePopulation(int maxPopulation);
    void calcFitnessForEach();
    void setProbabilityForEach();
    void sortByFitness();

    std::vector<DNA> getPopulation() const;
    void setPopulation(const std::vector<DNA> &value);
    void updatePopulation(std::vector<DNA> value);
    void createNextGeneration();


private:
    std::vector<DNA> population;
    DNA createRandom();
    DNA obtainRandomFromPool();
    int generation;
    int maxPopulation;
    int getMaxPopulation() const;
    void setMaxPopulation(int value);
    void sortByFitness(std::vector<DNA> *, int left, int right);





};

#endif // POPULATIONMANAGER_H
