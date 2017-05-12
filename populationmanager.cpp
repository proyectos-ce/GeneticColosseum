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
    double prob =  (double)(rand()) /  (double)(RAND_MAX);
    DNA randomMate;
    for (int i = 0; i < population.size(); ++i) {
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
    sortByFitness();
    setProbabilityForEach();
    std::vector<DNA> nextGeneration;
    for (int i = 0; i < maxPopulation; ++i) {
        DNA parent1 = obtainRandomFromPool();
        DNA parent2 = obtainRandomFromPool();
        DNA child = DNAManager::crossover(parent1, parent2, mutation);
        nextGeneration.push_back(child);
    }
    updatePopulation(nextGeneration);
    generation++;
}

float PopulationManager::getMutation() const
{
    return mutation;
}

void PopulationManager::setMutation(float value)
{
    mutation = value;
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
    sortByFitness( &population, 0, population.size()-1);
}

void PopulationManager::sortByFitness(std::vector<DNA> *list, int left, int right)
{
    int i = left, j = right;
    DNA tmp;
    double pivot = list->operator []((left + right) / 2).getFitness();
    while (i <= j) {
          while (list->operator [](i).getFitness() < pivot)
                i++;
          while (list->operator [](j).getFitness() > pivot)
                j--;
          if (i <= j) {
                tmp = list->operator [](i);
                list->operator [](i) = list->operator [](j);
                list->operator [](j) = tmp;
                i++;
                j--;
          }
    };
    if (left < j)
          sortByFitness(list, left, j);
    if (i < right)
          sortByFitness(list, i, right);
    }

/*
    int i = left, j = right;
    DNA tmp;
    int pivot = list->operator []((left + right) / 2).getFitness();

    while (i <= j) {
        while (list->operator [](i).getFitness() < pivot)
            i++;
        while (list->operator [](j).getFitness() > pivot)
            j--;
        if (i <= j) {
            tmp = list->operator [](i);
            list->operator [](i) = list->operator [](j);
            list->operator [](j)= tmp;
            i++;
            j--;
        }
    };
    if (left < j)
        sortByFitness(list, left, j);
    if (i < right)
        sortByFitness(list, i, right);

*/
