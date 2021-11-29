#! /usr/bin/python3
import sys
import heapq

# Author: Andreas Zeijlon (andze132)
# Date 2020-01-29

vertices = []
num_vertices = int(sys.stdin.readline())
neighbours = [0]*(num_vertices+1)

for i in sys.stdin:
	vertices.append(int(i))
	neighbours[int(i)-1]+=1

if(vertices[-1]-1 != num_vertices):
	print("Error")
else:
	q = []

	for i in range(len(neighbours)):
		if(neighbours[i] == 0):
			heapq.heappush(q, i+1)

	if not q:
		print("Error")
	else:
		for i in range(num_vertices):
			if not q:
				print("Error")
				break
			next_item = heapq.heappop(q)
			print(next_item)
			neighbours[vertices[i]-1]-=1

			if(neighbours[vertices[i]-1] == 0):
				heapq.heappush(q, vertices[i])