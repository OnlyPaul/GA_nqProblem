/**
 * Test
 */
public abstract class Population {
    private int size;

    public Population(int _size) {
        if(_size <= 0)
            throw new IllegalArgumentException("Something goes against nature. Object cannot be constructed.");
        this.size = _size;
    }

    public int getSize() { return size; }
    public void setSize(int _size) { this.size = _size; }

    public abstract int evaluate();
    public abstract void crossover(int count);
    public abstract void mutate(double prob);
}
