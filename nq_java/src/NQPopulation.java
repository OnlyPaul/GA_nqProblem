import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

/**
 * Test
 */
public class NQPopulation extends Population {
    NQChromosome best;
    NQChromosome[] individuals;

    public NQPopulation(int _size, int geneCount) {
        super(_size);
        individuals = new NQChromosome[_size];
        for(int i=0; i < getSize(); i++)
            individuals[i] = new NQChromosome(geneCount);
    }

    public NQChromosome getBest() { return best; }
    public void setBest(NQChromosome best) { this.best = best; }

    public NQChromosome[] getIndividuals() { return Arrays.copyOf(individuals, individuals.length); }
    public void setIndividuals(NQChromosome[] individuals) { this.individuals = Arrays.copyOf(individuals, individuals.length); }
    public NQChromosome getIndividuals(int pos) { return individuals[pos]; }
    public void setIndividuals(int pos, NQChromosome newChrom) { individuals[pos] = newChrom; }

    @Override
    public int evaluate() {
        NQChromosome bestIndividual = individuals[0];
        bestIndividual.evaluate();

        for(int i=0; i < getSize(); i++){
            individuals[i].evaluate();
            if(individuals[i].getFitness() <= bestIndividual.getFitness()) {
                bestIndividual = individuals[i];
            }
        }

        this.setBest(bestIndividual);
        return best.getFitness();
    }

    @Override
    public void crossover(int count) {
        /*
        * The last element of the array individuals can't take part in crossover, which means that
        * the second last element can't be the "left" element in the crossover.
        * To make sure that this also applies to odd sizes count can't be greater than size-2
        */

        if(count > this.getSize()-2)
        count = this.getSize()-2;

        for(int i=0; i < count; i+=2) {
            individuals[i].crossover(individuals[i+1]);
        }
    }

    public void populationSelection(int tmSize, boolean isElitist) {
        int i = this.getSize()-1;

        NQChromosome[] buffer = new NQChromosome[getSize()]; // buffer chromosomes, used in swapping etc.

        if(isElitist) {
            NQChromosome best = new NQChromosome(getBest());
            buffer[i] = best;
        }
        while(--i >= 0) {
            NQChromosome sel = new NQChromosome(tournamentSelection(tmSize));
            buffer[i] = sel;
        }

        setIndividuals(buffer);
    }

    public NQChromosome tournamentSelection(int tmSize) {
        NQChromosome compIndiv, tournamentBest;
        tournamentBest = this.getIndividuals(new Random().nextInt(getSize()));

        while(--tmSize > 0) {
            compIndiv = this.getIndividuals(new Random().nextInt(getSize()));
            if(tournamentBest.getFitness() > compIndiv.getFitness()) {
                tournamentBest = compIndiv;
            }
        }

        return tournamentBest;
    }

    @Override
    public void mutate(double prob) {
        for(int i=0; i < this.getSize()-1; i++)
        individuals[i].mutate(prob);
    }
}
