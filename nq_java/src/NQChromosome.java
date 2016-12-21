import java.util.Random;

/**
 * Test
 */
public class NQChromosome extends Chromosome1D<Integer> {
    public NQChromosome(int _geneCount) {
        super(_geneCount);
        for(int i=0; i < getGeneCount(); i++)
            this.setGenes(i, new Random().nextInt(getGeneCount()));
    }

    public NQChromosome(NQChromosome other) { super(other); }

    @Override
    public void evaluate() {
        if (this.getFitness() >= 0) return; // fitness of this queen is determined
        int distance; // distance between the queens
        int collision = 0; // how many queens threaten this queen

        for(int i=0; i < this.getGeneCount(); i++) {
            for(int j=i+1; j < this.getGeneCount(); j++) {
                distance = Math.abs(getGenes(i) - getGenes(j));

                if((distance == 0) || (distance == j-i))
                    collision++;
            }
        }

        this.setFitness(collision);
    }

    public void crossover(NQChromosome _chromosome) {
        int crossoverpoint = new Random().nextInt(getGeneCount()); // random
        int help; // swapping buffer

        for(int i=crossoverpoint; i < this.getGeneCount(); i++) {
            help = this.getGenes(i);
            this.setGenes(i, _chromosome.getGenes(i));
            _chromosome.setGenes(i, help);
        }

        this.setFitness(-1); //invalidate fitness
        _chromosome.setFitness(-1); //invalidate fitness
    }

    @Override
    public boolean mutate(double prob) {
        if (new Random().nextDouble() >= prob) return false;

        do {
            this.setGenes(new Random().nextInt(getGeneCount()), new Random().nextInt(getGeneCount()));
        } while(new Random().nextDouble() < prob);

        this.setFitness(-1);
        return true;
    }

    @Override
    public String toString() {
        String strOut = "";

        for(int i=0; i < getGeneCount(); i++)
            strOut += getGenes(i) + " ";
        strOut += '\n';

        return strOut;
    }

    public String toBoard() {
        String strOut = "";

        for(int j=0; j < getGeneCount(); j++) {
            for(int k=0; k < getGeneCount(); k++) {
                if(k == getGenes(j)) {
                    strOut += " Q ";
                } else {
                    strOut += " . ";
                }
            }
            strOut +=  '\n';
        }

        return strOut;
    }
}
