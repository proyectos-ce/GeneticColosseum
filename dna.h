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
    std::string getNameHASH() const;
    void setNameHASH(const std::string &value);

private:
    std::string nameHASH;
    float fitness;
    float probability;
};


namespace DNAManager {
int getRandomGene(int geneNumber=0);
DNA createRandomDNA();
DNA crossover(DNA parent1, DNA parent2, float mutation=0.05);
}
enum genes {
    HorizontalCost,
    VericalCost,
    AtractionToGladiators,
   AtractionToEnemies,
   EnemyDetectionRadius,
   GladiatorDetectionRadius,
   Attack,
   Shield,
   Weight
};
#endif // DNA_H
