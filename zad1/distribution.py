#!/usr/bin/env python3

import math
import sys
from matplotlib import pyplot
from collections import Counter

def read_symbols(group_size):
    lines = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        lines.append(line)
    joined = "".join(lines)
    return [joined[i:i + group_size] for i in range(0, len(joined), group_size)]


def calculate_probability(frequency):
    total_freq = sum(frequency.values())
    return {s: frequency[s] / total_freq for s in frequency.keys()}


def calculate_entropy(probability):
    return -sum(p * math.log2(p) for p in probability.values())


if __name__ == "__main__":
    if len(sys.argv) == 1:
        group_size = 1
    else:
        group_size = int(sys.argv[1])

    frequency = Counter(read_symbols(group_size))
    probability = calculate_probability(frequency)
    entropy = calculate_entropy(probability)
    print(frequency)
    print(probability)
    print(entropy)

    pyplot.plot(probability.keys(), probability.values(), "ro")
    pyplot.ylim([0, 1])
    pyplot.savefig("distribution.png")
