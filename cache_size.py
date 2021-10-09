from timeit import default_timer as timer
from random import randint
import matplotlib.pyplot as plt

def add_rows(source, target, length: int):
    for i in range(length):
        target[i] += source[i]
    return target

def test_length(row, row_length: int, step_size: int):
    num_loops = 10
    for i in range(num_loops):
        for j in range(row_length/step_size):
            row[j] = row[j]
    




axis_label = [int(10**(i/8)) for i in range(16, 40)]
test_results = [test_length(j) for j in axis_label]
print(test_results)
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.plot(axis_label, test_results)
ax.set_xscale('log')

plt.show()