#include "populationmanager.h"

PopulationManager::PopulationManager()
{

}

void PopulationManager::reset()
{

}

int PopulationManager::getGeneration() const
{
    return generation;
}

void PopulationManager::setGeneration(int value)
{
    generation = value;
}

std::vector<DNA> PopulationManager::getPopulation() const
{
    return population;
}

void PopulationManager::setPopulation(const std::vector<DNA> &value)
{
    population = value;
}

void PopulationManager::updatePopulation(std::vector<DNA> value)
{
    population.clear();
    for (int i = 0; i < value.size(); ++i) {
        population.push_back(value.operator [](i));
    }
}


DNA PopulationManager::createRandom()
{
    return DNAManager::createRandomDNA();
}

DNA PopulationManager::obtainRandomFromPool()
{
    float prob =  (float)(rand()) /  (float)(RAND_MAX);
    DNA randomMate;
    for (int i = population.size(); i >=0; --i) {
        prob-=population[i].getProbability();
        if(prob<=0){
            randomMate = population[i];
            break;
        }
    }
    return randomMate;
}

void PopulationManager::inicializePopulation(int maxPopulation)
{
    this->maxPopulation=maxPopulation;
    population.clear();
    for (int i = 0; i < maxPopulation; ++i) {
        population.push_back(createRandom());
    }
}

int PopulationManager::getMaxPopulation() const
{
    return maxPopulation;
}

void PopulationManager::setMaxPopulation(int value)
{
    maxPopulation = value;
}

void PopulationManager::createNextGeneration()
{
    //calcFitnessForEach();
    sortByFitness();
    setProbabilityForEach();
    std::vector<DNA> nextGeneration;
    for (int i = 0; i < maxPopulation-1; ++i) {
        DNA parent1 = obtainRandomFromPool();
        DNA parent2 = obtainRandomFromPool();
        DNA child = DNAManager::crossover(parent1, parent2);
        nextGeneration.push_back(child);
    }
    nextGeneration.push_back(createRandom());
    updatePopulation(nextGeneration);
    generation++;
}

void PopulationManager::setProbabilityForEach()
{
    int sumFitness;
    for (int i = 0; i < population.size(); ++i) {
        sumFitness+=population[i].getFitness();
    }
    for (int i = 0; i < population.size(); ++i) {
        population[i].setProbability(population[i].getFitness()/sumFitness);
    }
}
void PopulationManager::sortByFitness(){
    sortByFitness( &population, 0, population.size());
}

void PopulationManager::sortByFitness( std::vector<DNA> *arr, int left, int right)
{
    int i = left, j = right;
    DNA tmp;
    int pivot = arr->operator []((left + right) / 2).getFitness();
    /* partition */
    while (i <= j) {
        while (arr->operator [](i).getFitness() < pivot)
            i++;
        while (arr->operator [](j).getFitness() > pivot)
            j--;
        if (i <= j) {
            tmp = arr->operator [](i);
            arr->operator [](i) = arr->operator [](j);
            arr->operator [](j)= tmp;
            i++;
            j--;
        }
    };
    /* recursion */
    if (left < j)
        sortByFitness(arr, left, j);
    if (i < right)
        sortByFitness(arr, i, right);

}

void PopulationManager::calcFitnessForEach()
{
    int fitness = 0;
    for (int i = 0; i < population.size(); ++i) {
        fitness=0;
        for (int j = 0; j < 11; ++j) {
            fitness+=population[i].genes[j];
        }
        population[i].setFitness(fitness);
        if(fitness>1300){
            std::cout<<"error"<<fitness<<std::endl;
        }
    }
}
