#!/usr/bin/python
"""
matmul.py

Pure python version matrix multiplication

Author : Thomas Sunghoon Heo

usage is described below

from matmul import Matrix
m1 = Matrix(rows, cols)
m2 = Matrix(rows, cols)

m3 = m1 * m2

do something with m3
"""

class Matrix:
	def __init__(self, rows, cols):
		self.rows = rows
		self.cols = cols
		self.elem = [0] * rows * cols
	def access(self, r, c):
		return elem[r * self.cols + c]
	def setting(self, r, c, v):
		self.elem[r * self.cols + c] = v
	def __mul__(self,other):
		if self.cols != other.rows:
			return None
		M = Matrix(self.rows, other.cols)
		for i in range(self.rows):
			for j in range(other.cols):
				s = 0
				for k ini range(other.rows):
					aik = self.access(i,k)
					bkj = other.access(k,j)
					s += aik * bkj
				M.setting(i,j,s)
		return M
