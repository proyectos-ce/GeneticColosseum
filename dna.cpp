#include "dna.h"

DNA::DNA()
{

}



float DNA::getProbability() const
{
    return probability;
}

void DNA::setProbability(float value)
{
    probability = value;
}

float DNA::getFitness() const
{
    return fitness;
}

void DNA::setFitness(float value)
{
    fitness = value;
}


namespace DNAManager {

int getRandomGene(int geneNumber)
{
    int gene = std::rand()%101;
    //std::cout << gene<< '\n';;
    return gene;
}

DNA createRandomDNA()
{
    DNA randomDNA;
    for (int i = 0; i < 11; ++i) {
        randomDNA.genes[i] = DNAManager::getRandomGene();
    }
    return randomDNA;
}

DNA crossover(DNA parent1, DNA parent2)
{
    DNA child;
    for (int i = 0; i < 11; ++i) {
        if(i%2==0){
            child.genes[i] = parent1.genes[i];
        }
        else{
            child.genes[i] = parent2.genes[i];
        }
    }
    return child;

}


}
