<?php

abstract class Population {
    private $size;

    public function __construct($_size) {
        if ($_size <= 0) throw new OutOfRangeException("Population size cannot be less than 1.");

        $this->size = $_size;
    }

    public function setSize($size) { $this->size = $size; }
    public function getSize() { return $this->size; }

    abstract public function evaluate();
    abstract public function crossover($count);
    abstract public function mutate($prob);
}