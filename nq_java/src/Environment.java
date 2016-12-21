/**
 * test test test
 */
public class Environment {
    private NQPopulation crowd;

    Environment(int crowdSize, int geneCount) {
        crowd = new NQPopulation(crowdSize, geneCount);
    }

    public void natSelection(int cycleCount, int tmSize, boolean isElitist, double mutProb) {
        while (crowd.evaluate() != 0 && --cycleCount >= 0) {
            crowd.populationSelection(tmSize, isElitist);
            crowd.crossover(crowd.getSize());
            crowd.mutate(mutProb);
        }
    }

    public Integer[] getAnswer() {
        if (crowd.getBest().getFitness() == 0) {
            Integer[] answer = new Integer[crowd.getBest().getGeneCount()];
            for(int i=0; i < crowd.getBest().getGeneCount(); i++)
                answer[i] = crowd.getBest().getGenes(i);
            return answer;
        } else return null;
    }

    public String getStrAnswer() { return crowd.getBest().toString(); }

    public String getBoardAnswer() { return crowd.getBest().toBoard(); }
}
