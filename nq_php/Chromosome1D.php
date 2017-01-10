<?php

abstract class Chromosome1D {
    private $fitness;
    private $geneCount;
    private $genes = array();

    public function __construct($_geneCount)
    {
        if ($_geneCount <= 0) throw new OutOfRangeException("GeneCount cannot be less than 1.");
        $this->geneCount = $_geneCount;

        for ($i=0; $i < $this->geneCount; $i++)
            $this->genes[$i] = mt_rand(0, $_geneCount-1);

        $this->fitness = -1;
    }

    public function getFitness() { return $this->fitness; }
    public function setFitness($fitness) { $this->fitness = $fitness; }

    public function getGeneCount() { return $this->geneCount; }
    public function setGeneCount($geneCount) { $this->geneCount = $geneCount; }

    public function getGenes() { return $this->genes; }
    public function setGenes($genes) { $this->genes = clone $genes; }
    public function setGenesByPos($pos, $value) { $this->genes[$pos] = $value; }
    public function getGenesByPos($pos) { return $this->genes[$pos]; }

    abstract public function evaluate();
    abstract public function mutate($prob);
    abstract public function __toString();
}