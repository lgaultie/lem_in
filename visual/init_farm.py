#!/usr/bin/python
#coding: utf8

import sys

class anthill:

	def __init__(self):
		self.nb_ants	= None
		self.start		= None
		self.end		= None
		self.room		= []
		self.used_room	= []
		self.link		= []
		self.move	  	= []

# class Ant():
#
# 	def __init__(self, number, node_path=None,
# 				journey=None, color='g.'):
# 		self.number = number
# 		self.node_path = node_path
# 		self.journey = journey
# 		self.color = color
#
# 	def set_node_path(self, farm):
# 		self.node_path = []
# 		started = False
# 		self.node_path.append(farm.start)
# 		for turn in farm.move:
# 			for move in turn:
# 				if move[0] == str(self.number):
# 					self.node_path.append(move[1])
# 					started = True
# 			if not started:
# 				self.node_path.append(farm.start)
#
# 	def set_location(self, pos, farm):
# 		location = pos[farm.start]
# 		self.current_location = location
#
# 	def set_journey(self, pos, nb_steps, farm):
# 		location_list = []
# 		for num in range(len(self.node_path)):
# 			if num != 0:
# 				start_pos = pos[self.node_path[i - 1]]
# 				end_pos = pos[self.node_path[i]]
# 				x = np.linspace(start_pos[0], end_pos[0], num=nb_steps)
# 				y = np.linspace(start_pos[1], end_pos[1], num=nb_steps)
# 				location_list.extend(list(zip(x, y)))
# 			i += 1
# 		self.journey = location_list
