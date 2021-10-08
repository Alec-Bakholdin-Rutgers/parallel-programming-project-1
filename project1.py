import resource
import timeit
import matplotlib.pyplot as plt

class Bandwidth:
    def __init__(self):
        self.arr = []
        self.data_sizes = []
        self.bandwidths = []
        self.exec_times = []

    def __getSize(self, x):
        # Memory before creating matrix
        start_data = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
        self.arr = [[0 for i in range(x)] for j in range(x)]
        end_data = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss

        return [self.arr, end_data - start_data]

    # clear memory used by matrix
    def __clear(self):
        self.arr.clear

    def getBandwidth(self, matDimensions):

        size = self.__getSize(matDimensions)[1]
        self.data_sizes.append(size)
        print(f"Array Memory Size: {size} bytes")

        start = timeit.default_timer()
        for i in range(matDimensions):
            for j in range(matDimensions):
                
                # i and j swapped to avoid data reuse
                x = self.arr[j][i]   # load instruction used for addition on integer elements
                x += 3

        end = timeit.default_timer()
        
        exec = end - start
        bandwidth = size / exec

        self.exec_times.append(exec)
        self.bandwidths.append(bandwidth)

        print(f"Exec time: {exec} seconds")
        print(f"Memory Bandwidth: {bandwidth} bytes / second\n")
        self.__clear()

    def plot(self, sizes):
        for i in sizes:
            self.getBandwidth(i)
        plt.plot(self.data_sizes, self.bandwidths)
        plt.show()



sizes = [4000, 5000, 6000, 7000, 8000, 9000]
test = Bandwidth()
test.getBandwidth(12000)

# when looping through the matrix sizes we get smaller data sizes and faster execution times
# running each matrix size individually seems to be more accurate
# for i in sizes:
    # test.getBandwidth(i)
