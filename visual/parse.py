#!/usr/bin/python
#coding: utf8

import re
import sys
from init_farm_ants import anthill

def	regex_compile():
	patterns = {}
	patterns["ants"] = re.compile("^\d+$")
	patterns["start"] = re.compile("^#{2}(start)$")
	patterns["end"] = re.compile("^#{2}(end)$")
	patterns["comment"] = re.compile("^#")
	patterns["room"] = re.compile("^([\d\w]+) \d+ \d+$")
	patterns["link"] = re.compile("^([\d\w]+)-([\d\w]+)$")
	patterns["move"] = re.compile("^(L[\d]+)-([\d\w]+)")
	return (patterns)


def check_status(farm, status, line):
	if (status == None):
		return status
	elif (status == "start"):
		farm.start = line.split(" ")[0]
	elif (status == "end"):
		farm.end = line.split(" ")[0]
	elif (status == "comment"):
		pass
	status = None
	return status


def parse_room(farm, line):
	line_split = line.split(" ")
	room_name = line_split[0]
	farm.room.append(room_name)


def parse_link(farm, line):
	line_split = line.strip().split("-")
	farm.link.append(line_split)


def parse_move(farm, line):
	final = []
	line_split = line.strip().split(" ")
	for element in line_split:
		line_split2 = element.split("-")
		ant = line_split2[0].strip('L')
		room = line_split2[1]
		pre_final = []
		pre_final.append(ant)
		pre_final.append(room)
		final.append(pre_final)
	farm.move.append(final)

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
			farm.nb_move += 1
	return (farm)
