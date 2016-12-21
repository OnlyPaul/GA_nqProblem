import java.util.ArrayList;
import java.util.Arrays;

/**
 * Test test
 */
public abstract class Chromosome1D<T> {
	private int fitness;
	private int geneCount;
	private T[] genes;

	@SuppressWarnings("unchecked")
    public Chromosome1D(int _geneCount) {
		if(_geneCount <= 0)
			throw new IllegalArgumentException("Something goes against nature. Object cannot be constructed.");

		this.geneCount = _geneCount;
		genes = (T[])new Object[geneCount];

		this.fitness = -1;
	}

	public Chromosome1D(Chromosome1D<T> other) {
	    fitness = other.getFitness();
	    geneCount = other.getGeneCount();
	    this.setGenes(other.getGenes());
    }

    public int getFitness() { return fitness; }
    public void setFitness(int fitness) { this.fitness = fitness; }

    public int getGeneCount() { return geneCount; }
    public void setGeneCount(int geneCount) { this.geneCount = geneCount; }

    public T[] getGenes() { return Arrays.copyOf(genes, genes.length);}
    public void setGenes(T[] _genes) { this.genes = Arrays.copyOf(_genes, _genes.length); }
    public T getGenes(int pos) { return genes[pos]; }
    public void setGenes(int pos, T _genes) { this.genes[pos] = _genes; }

    public abstract void evaluate();
	public abstract boolean mutate(double prob);
	public abstract String toString();
}
