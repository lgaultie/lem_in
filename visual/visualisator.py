#!/usr/bin/python
#coding: utf8

import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from init_farm_ants import anthill, Ant
from parse import make_farm, regex_compile, check_status, parse_room, parse_link, parse_move


def draw_single_room(name, g, pos, color, size):
	node_list = []
	node_list.append(name) #this list contains one element
	node = nx.draw_networkx_nodes(
	g,
	pos,
	nodelist = node_list,
	node_color = color,
	width = 0,
	node_size = size)
	node.set_edgecolor('#e79e85')


def draw_rooms(farm, g, pos):
	for name in farm.room:
		if name == farm.start:
			draw_single_room(name, g, pos, '#bb5a5a', 800)
		elif name == farm.end:
			draw_single_room(name, g, pos, '#42b883', 800)
		else:
			draw_single_room(name, g, pos, '#eaceb4', 800)


def draw_links(farm, g, pos):
	for link in farm.link:
		link_list = []
		link_list.append(farm.room)
		link = nx.draw_networkx_edges(
		g,
		pos,
		edge_color = '#bb5a5a',
		width= 3,
		style = 'dashed',
		)
		return (link)


def draw_label(g, pos):
	nx.draw_networkx_labels(
	g,
	pos,
	font_size= 18,
	font_family='calibri',
	font_color= '#bb5a5a')

def draw_ant(position, color):
	ant = plt.plot([position[0]], [position[1]],
	color=color, marker='.', markersize = 20)
	return (ant)


def make_graph(farm):
	g = nx.Graph()
	g.add_nodes_from(farm.room)
	g.add_edges_from(farm.link)
	return (g)


def create_ants(farm, pos, nb_steps):
	ants = []
	for ant_num in range(1, (int(farm.nb_ants) + 1)):
		ant = Ant(ant_num)
		ant.set_node_path(farm)
		ant.set_location(pos, farm)
		ant.set_journey(pos, nb_steps, farm)
		ant.color = '#3c4245'
		ants.append(ant)
	return (ants)


def update(num, g, pos, nb_steps, farm, ants):

	fig.clear()

	draw_rooms(farm, g, pos)
	draw_links(farm, g, pos)

	for ant in ants:
		if num < len(ant.journey):
			draw_ant(ant.journey[num], ant.color)

	draw_label(g, pos)
	# background color
	fig.set_facecolor('#e79e85')
	# hide axis
	plt.axis('off')



# parse rooms,links and moves in farm
farm = make_farm()

# create the Graph with room and links
#nx.spring_layout: a position will be assigned to every node in G.
g = make_graph(farm)
pos = nx.spring_layout(g)

# create ants and init number of steps between nodes
nb_steps = 10
ants = create_ants(farm, pos, nb_steps)

# build figure
fig = plt.figure()

# animate
ani = FuncAnimation(
	fig,
	update, #arguments of upate are below
	frames = farm.nb_move * nb_steps,
	fargs = (
		g,
		pos,
		nb_steps,
		farm,
		ants),
	interval = 1,
	repeat = True
	)

# open canvas
plt.show()
