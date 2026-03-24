import numpy as np


class DataReader:
    def __init__(self, filepath: str):
        self.filepath = filepath
        self.read_file()

    def read_file(self):
        with open(self.filepath, "r") as f:
            data = f.readlines()
            self.info = data[0]
            nums = data[1:]
            p = nums[0]
            p = np.array([float(i) for i in p.split()])
            self.p = p
            self.nums = np.array([[int(i) for i in s.split()]
                                 for s in nums[1:]])


class DataReader2:
    def __init__(self, filepath1: str, filepath2: str):
        self.filepath1 = filepath1
        self.filepath2 = filepath2
        self.nums1, self.p1 = self.read_file(filepath1)
        self.nums2, self.p2 = self.read_file(filepath2)

    def read_file(self, path):
        with open(path, "r") as f:
            nums = f.readlines()[1:]
            p = nums[0]
            p = np.array([float(i) for i in p.split()])
            nums = np.array([[int(i) for i in s.split()]
                             for s in nums[1:]])
            return nums, p
class DataReaderFloat2:
    def __init__(self, filepath1: str, filepath2: str):
        self.filepath1 = filepath1
        self.filepath2 = filepath2
        self.nums1, self.p1 = self.read_file(filepath1)
        self.nums2, self.p2 = self.read_file(filepath2)

    def read_file(self, path):
        with open(path, "r") as f:
            nums = f.readlines()[1:]
            p = nums[0]
            p = np.array([float(i) for i in p.split()])
            nums = np.array([[float(i) for i in s.split()]
                             for s in nums[1:]])
            return nums, p
