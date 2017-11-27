#!/usr/bin/env python3

import math


def read_symbols():
    lines = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        lines.append(line)
    return "".join(lines)


def calculate_frequency(symbols):
    frequency = {}
    for x in symbols:
        if x in frequency:
            frequency[x] += 1
        else:
            frequency[x] = 1
    return frequency


def calculate_probability(frequency):
    total_freq = sum(frequency.values())
    return {s: frequency[s] / total_freq for s in frequency.keys()}


def calculate_entropy(probability):
    return -sum(p * math.log2(p) for p in probability.values())


if __name__ == "__main__":
    symbols = read_symbols()
    frequency = calculate_frequency(symbols)
    probability = calculate_probability(frequency)
    entropy = calculate_entropy(probability)
    print(frequency)
    print(probability)
    print(entropy)
