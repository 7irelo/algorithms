using System;
using System.Collections.Generic;
using System.Linq;

class GeneticAlgorithm
{
    private Random random;
    private int populationSize;
    private double mutationRate;

    public GeneticAlgorithm(int populationSize, double mutationRate)
    {
        this.populationSize = populationSize;
        this.mutationRate = mutationRate;
        this.random = new Random();
    }

    // Representation of an individual solution (Chromosome)
    class Individual
    {
        public int[] Genes { get; private set; }
        public double Fitness { get; private set; }

        public Individual(int[] genes)
        {
            Genes = genes;
            Fitness = CalculateFitness();
        }

        // Calculate fitness based on the problem domain
        private double CalculateFitness()
        {
            // Example fitness function: sum of genes
            return Genes.Sum();
        }

        // Crossover operation to produce offspring
        public Individual Crossover(Individual partner)
        {
            int crossoverPoint = random.Next(Genes.Length);
            int[] childGenes = new int[Genes.Length];

            for (int i = 0; i < Genes.Length; i++)
            {
                childGenes[i] = i < crossoverPoint ? Genes[i] : partner.Genes[i];
            }

            return new Individual(childGenes);
        }

        // Mutation operation to introduce genetic diversity
        public void Mutate(double mutationRate)
        {
            for (int i = 0; i < Genes.Length; i++)
            {
                if (random.NextDouble() < mutationRate)
                {
                    Genes[i] = 1 - Genes[i]; // Flip the bit
                }
            }
        }
    }

    // Initialize a population of individuals with random genes
    private List<Individual> InitializePopulation(int geneLength)
    {
        List<Individual> population = new List<Individual>();

        for (int i = 0; i < populationSize; i++)
        {
            int[] genes = new int[geneLength];
            for (int j = 0; j < geneLength; j++)
            {
                genes[j] = random.Next(2); // Binary genes
            }
            population.Add(new Individual(genes));
        }

        return population;
    }

    // Select parents for crossover using tournament selection
    private Individual SelectParent(List<Individual> population)
    {
        int tournamentSize = 5;
        List<Individual> tournament = new List<Individual>();

        for (int i = 0; i < tournamentSize; i++)
        {
            tournament.Add(population[random.Next(population.Count)]);
        }

        return tournament.OrderByDescending(individual => individual.Fitness).First();
    }

    // Perform genetic algorithm to find the best solution
    public Individual FindSolution(int geneLength, int maxGenerations)
    {
        List<Individual> population = InitializePopulation(geneLength);

        for (int generation = 0; generation < maxGenerations; generation++)
        {
            List<Individual> newPopulation = new List<Individual>();

            for (int i = 0; i < populationSize; i++)
            {
                Individual parent1 = SelectParent(population);
                Individual parent2 = SelectParent(population);

                Individual offspring = parent1.Crossover(parent2);

                offspring.Mutate(mutationRate);

                newPopulation.Add(offspring);
            }

            population = newPopulation;
        }

        return population.OrderByDescending(individual => individual.Fitness).First();
    }
}

class Program
{
    static void Main(string[] args)
    {
        int geneLength = 10; // Length of each individual's gene sequence
        int populationSize = 100; // Size of the population
        double mutationRate = 0.01; // Probability of mutation

        GeneticAlgorithm ga = new GeneticAlgorithm(populationSize, mutationRate);
        Individual bestSolution = ga.FindSolution(geneLength, maxGenerations: 1000);

        Console.WriteLine("Best solution found:");
        Console.WriteLine("Genes: " + string.Join("", bestSolution.Genes));
        Console.WriteLine("Fitness: " + bestSolution.Fitness);
    }
}
