<?php include("Chromosome1D.php"); ?>
<?php

class NQChromosome extends Chromosome1D {
    public function __construct($_geneCount) {parent::__construct($_geneCount); }

    public function evaluate() {
        $collision = 0;
        if ($this->getFitness() >= 0) return;

        for ($i=0; $i < $this->getGeneCount(); $i++) {
            for ($j=$i+1; $j < $this->getGeneCount(); $j++) {
                $distance = abs($this->getGenesByPos($i) - $this->getGenesByPos($j));

                if ($distance == 0 || $distance == $j-$i)
                    $collision++;
            }
        }

        $this->setFitness($collision);
    }

    public function crossover(NQChromosome $NQChrom) {
        $crossoverpoint = mt_rand(0, $this->getGeneCount()-1);

        for ($i=$crossoverpoint; $i < $this->getGeneCount(); $i++) {
            $help = $this->getGenesByPos($i);
            $this->setGenesByPos($i, $NQChrom->getGenesByPos($i));
            $NQChrom->setGenesByPos($i, $help);
        }

        $this->setFitness(-1);
        $NQChrom->setFitness(-1);
    }

    public function mutate($prob) {
        if ($prob >= 1) throw new OutOfRangeException("Mutating probability must be less than 1.00");

        if (mt_rand(0,100)/100 >= $prob) return false;

        do {
            $this->setGenesByPos(mt_rand(0, $this->getGeneCount()-1), mt_rand(0, $this->getGeneCount()-1));
        } while (mt_rand(0,100)/100 < $prob);

        $this->setFitness(-1);
        return true;
    }

    public function __toString() {
        $strOut = "";

        for ($i=0; $i < $this->getGeneCount(); $i++)
            $strOut .= $this->getGenesByPos($i) . " ";
        $strOut .= "\n";

        return $strOut;
    }

    public function toBoard() {
        $strOut = "";

        for ($i=0; $i < $this->getGeneCount(); $i++) {
            for ($j=0; $j < $this->getGeneCount(); $j++) {
                if ($j == $this->getGenesByPos($i))
                    $strOut .= " Q ";
                else
                    $strOut .= " . ";
            }
            $strOut .= "\n";
        }

        return $strOut;
    }
}