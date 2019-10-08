#!/usr/bin/python
#coding: utf8
import sys
from init_farm import anthill
from parse import regex_compile, check_status

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
			# farm.start = line.split(" ", 2)[0]
		elif (patterns["end"].search(line)):
			status = "end"
		elif (patterns["comment"].search(line)):
			status = "comment"
		elif (patterns["room"].search(line)):
			line_split = line.split(" ")
			room_name = line_split[0]
			farm.room.append(room_name)
		elif (patterns["link"].search(line)):
			line_split2 = line.strip().split("-")
			farm.link.append(line_split2)
		elif (patterns["moves"].search(line)):
			print "on a un move"
		# checker encore room, limk, moves
		print status
			# farm.end = line.split(" ", 2)[0]
		print line
	print farm.nb_ants
	print farm.start
	print farm.end
	print farm.room
	print farm.link
	return (farm)
# for arg in sys.argv:
# 	print arg
# Chaque argument passé au programme est ajouté à l'objet liste sys.argv

# a faire: 1/creer ma data -> farm et graph
# pour se faire, parser avec un for line in sys.stdin et recuperer les infos
# pour le graph avec nx.Graph et add nodes/edges from farm.nodes / farm.links
arg = sys.argv
farm = make_farm()
