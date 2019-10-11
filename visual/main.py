#!/usr/bin/python
#coding: utf8
import sys
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation as matAni
from init_farm import anthill
from parse import regex_compile, check_status, parse_room, parse_link, parse_move
# from animate import animate

def make_farm():
	farm = anthill()
	status = None
	patterns = regex_compile()
	for line in sys.stdin:
		status = check_status(farm, status, line)
		if (patterns["ants"].search(line)):
			farm.nb_ants = int(line)
		elif (patterns["start"].search(line)):
			status = "start"
		elif (patterns["end"].search(line)):
			status = "end"
		elif (patterns["comment"].search(line)):
			status = "comment"
		elif (patterns["room"].search(line)):
			parse_room(farm, line)
		elif (patterns["link"].search(line)):
			parse_link(farm, line)
		elif (patterns["move"].search(line)):
			parse_move(farm, line)
	print "nb_ants ---------------------------"
	print farm.nb_ants
	print "start et end ----------------------"
	print farm.start
	print farm.end
	print "les rooms ------------------------"
	print farm.room
	print "les links ------------------------"
	print farm.link
	print "les moves ------------------------"
	print farm.move
	return (farm)

# def create_data(farm):
# 	data = {}
# 	data['farm'] = farm

def draw_single_room(name, g, pos, color, size):
	node_list = []
	node_list.append(name) #cette liste contient qu'un element
	node = nx.draw_networkx_nodes(
	g,
	pos,
	nodelist = node_list,
	node_color = color,
	linewidths = 3,
	node_size = size)
	node.set_edgecolor('#00F6ED')

def draw_rooms(farm, g, pos):
	for name in farm.room:
		if name == farm.start:
			draw_single_room(name, g, pos, '#D81159', 600)
		elif name == farm.end:
			draw_single_room(name, g, pos, '#7CEA9C', 600)
		else:
			draw_single_room(name, g, pos, '#00F6ED', 400)

def draw_links(farm, g, pos):
	for link in farm.link:
		link_list = []
		link_list.append(farm.room)
		link = nx.draw_networkx_edges(
		g,
		pos,
		edge_color = '#00F6ED',
		width= 3,
		style = 'dashed',
		)
		return (link)

def draw_label(g, pos):
	nx.draw_networkx_labels(
	g,
	pos,
	# label = dict([(farm.start, 'START'), (farm.end, 'END')]),
	font_size= 18,
	font_family='sans-serif',
	font_color= '#2A324B')

def make_graph(farm):
	g = nx.Graph()
	g.add_nodes_from(farm.room)
	g.add_edges_from(farm.link)
	return (g)

arg = sys.argv
farm = make_farm() #parse rooms,links, move in farm
# data = create_data(farm)
g = make_graph(farm) #create graph with rooms and links
pos = nx.spring_layout(g) #A position will be assigned to every node in G.
draw_rooms(farm, g, pos)
draw_links(farm, g, pos)
draw_label(g, pos)
# ani = animate(farm, pos)
plt.show()
