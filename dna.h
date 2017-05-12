#ifndef DNA_H
#define DNA_H
#include <random>
#include "iostream"
class DNA
{
public:
    DNA();
    int genes[11];
    double getProbability() const;
    void setProbability(double value);
    double getFitness() const;
    void setFitness(double value);
    std::string getNameHASH() const;
    void setNameHASH(const std::string &value);

private:
    std::string nameHASH;
    double fitness =0;
    double probability=0;
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
