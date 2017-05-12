#include "dna.h"

DNA::DNA()
{
    for (int i = 0; i < 11; ++i) {
        genes[i]=0;

    }
}



double DNA::getProbability() const
{
    return probability;
}

void DNA::setProbability(double value)
{
    probability = value;
}

double DNA::getFitness() const
{
    return fitness;
}

void DNA::setFitness(double value)
{
    fitness = value;
}

std::string DNA::getNameHASH() const
{
    return nameHASH;
}

void DNA::setNameHASH(const std::string &value)
{
    nameHASH = value;
}


namespace DNAManager {

int getRandomGene(int geneNumber)
{
    int gene = std::rand() % 101;
    //gene=90;
    //std::cout << gene<< '\n';;
    return gene;
}

DNA createRandomDNA()
{
    DNA randomDNA;
    for (int i = 0; i < 11; ++i) {
        randomDNA.genes[i] = DNAManager::getRandomGene();
        //std::cout<<randomDNA.genes[i]<<"\n";
    }
    return randomDNA;
}

DNA crossover(DNA parent1, DNA parent2, float mutation)
{
    DNA child;
    for (int i = 0; i < 11; ++i) {
        if((float)(rand()) /  (float)(RAND_MAX) < mutation){
            child.genes[i]=DNAManager::getRandomGene();
        }
        else {
        if(i%2==0){
            child.genes[i] = parent1.genes[i];
        }
        else{
            child.genes[i] = parent2.genes[i];
        }
        }
    }
    return child;

}


}
