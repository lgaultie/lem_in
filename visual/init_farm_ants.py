#!/usr/bin/python
#coding: utf8

import numpy as np

class anthill:

	def __init__(self):
		self.nb_ants	= None
		self.start		= None
		self.end		= None
		self.room		= []
		self.link		= []
		self.move	  	= []
		self.nb_move	= 0

class Ant:

	def __init__(self, number, node_path=None,
				journey=None, color='g.'):
		self.number			= number
		self.node_on_path	= node_path
		self.journey		= journey
		self.color			= color


	def parse_path(self, farm):
		self.node_on_path = []
		started = False
		self.node_on_path.append(farm.start)
		for turn in farm.move:
			for move in turn:
				if move[0] == str(self.number):
					self.node_on_path.append(move[1])
					started = True
			if not started:
				self.node_on_path.append(farm.start)


	def calc_journey(self, pos, num_steps, farm):
		location_list = []
		for i in range(len(self.node_on_path)):
			if i != 0:
				# take 2 nodes and calculate x y between thoses nodes
				start_pos = pos[self.node_on_path[i - 1]]
				end_pos = pos[self.node_on_path[i]]
				x = np.linspace(start_pos[0], end_pos[0], num=num_steps)
				y = np.linspace(start_pos[1], end_pos[1], num=num_steps)
				location_list.extend(list(zip(x, y)))
			i += 1
		self.journey = location_list
