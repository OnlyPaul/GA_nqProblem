<?php include("NQChromosome.php"); ?>
<?php include("Population.php"); ?>
<?php

class NQPopulation extends Population {
    private $best;
    private $individuals = array();

    public function __construct($size, $geneCount) {
        parent::__construct($size);
        for ($i=0; $i < $this->getSize(); $i++)
            $this->individuals[] = new NQChromosome($geneCount);

        $this->best = new NQChromosome($geneCount);
        $this->best = $this->individuals[$this->getSize()-1];
    }

    public function getBest() { return $this->best; }
    public function setBest(NQChromosome $best) { $this->best = $best; }

    public function getIndividuals() { return $this->individuals; }
    public function setIndividuals($individuals) { $this->individuals = $individuals; }
    public function getIndividualsByPos($pos) { return clone $this->individuals[$pos]; }
    public function setIndividualsByPos($pos, $value) { $this->individuals[$pos] = $value; }

    public function evaluate() {
        $bestIndividual = $this->individuals[0];
        $bestIndividual->evaluate();

        for ($i=0; $i < $this->getSize(); $i++) {
            $this->individuals[$i]->evaluate();
            if ($this->individuals[$i]->getFitness() <= $bestIndividual->getFitness())
                $bestIndividual = $this->individuals[$i];
        }

        $this->setBest($bestIndividual);
        return $this->best->getFitness();
    }

    public function crossover($count) {
        if ($count > $this->getSize()-2) $count = $this->getSize()-2;

        for ($i=0; $i < $count; $i++)
            $this->individuals[$i]->crossover($this->individuals[$i+1]);
    }

    public function populationSelection($tmsize, $isElitist) {
        $i = $this->getSize()-1;

        $buffer = array();

        if ($isElitist) {
            $tempbest = clone $this->getBest();
            $buffer[$i] = $tempbest;
        }

        while (--$i >= 0) {
            $sel = $this->tournamentSelection($tmsize);
            $buffer[$i] = $sel;
        }

        $this->setIndividuals($buffer);
    }

    public function tournamentSelection($tmsize) {
        $tournamentBest = $this->getIndividualsByPos(mt_rand(0, $this->getSize()-1));

        while (--$tmsize > 0) {
            $compIndiv = $this->getIndividualsByPos(mt_rand(0, $this->getSize()-1));
            if ($tournamentBest->getFitness() > $compIndiv->getFitness())
                $tournamentBest = $compIndiv;
        }

        return $tournamentBest;
    }

    public function mutate($prob) {
        for ($i=0; $i < $this->getSize()-1; $i++)
            $this->individuals[$i]->mutate($prob);
    }
}