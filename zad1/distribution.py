#!/usr/bin/env python3

import math
import collections
from matplotlib import pyplot

def read_symbols():
    lines = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        lines.append(line)
    return "".join(lines)


def calculate_probability(frequency):
    total_freq = sum(frequency.values())
    return {s: frequency[s] / total_freq for s in frequency.keys()}


def calculate_entropy(probability):
    return -sum(p * math.log2(p) for p in probability.values())


if __name__ == "__main__":
    frequency = collections.Counter(read_symbols())
    probability = calculate_probability(frequency)
    entropy = calculate_entropy(probability)
    print(frequency)
    print(probability)
    print(entropy)
    pyplot.plot(probability.keys(), probability.values(), "ro")
    pyplot.ylim([0,1])
    pyplot.savefig("distribution.png")