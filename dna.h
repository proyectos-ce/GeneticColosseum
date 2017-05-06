#ifndef DNA_H
#define DNA_H
#include <random>
#include "iostream"
class DNA
{
public:
    DNA();
    int genes[11];
    float getProbability() const;
    void setProbability(float value);

    float getFitness() const;
    void setFitness(float value);

private:
    float fitness;
    float probability;
};


namespace DNAManager {
int getRandomGene(int geneNumber=0);
DNA createRandomDNA();
DNA crossover(DNA parent1,DNA parent2);
}

#endif // DNA_H
