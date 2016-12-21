/**
 * Testing
 */
public class NQClient {
    public static void main(String[] args) {
        int n = 8;
        int popsize = 5000;
        int gencnt = 5000;
        int tmsize = 500;
        double mutprob = 0.2;

        Environment nqueen = new Environment(popsize, n);
        nqueen.natSelection(gencnt, tmsize, true, mutprob);
        Integer[] answer = nqueen.getAnswer();

        if (answer != null)
            System.out.println(nqueen.getStrAnswer());
        else
            System.out.println("no answer.");
    }
}
