#!/usr/bin/python
#coding: utf8

import re
import sys
from init_farm import anthill

def	regex_compile():
	patterns = {}
	patterns["ants"] = re.compile("^\d+$")
	patterns["start"] = re.compile("^#{2}(start)$")
	patterns["end"] = re.compile("^#{2}(end)$")
	patterns["comment"] = re.compile("^#")
	patterns["room"] = re.compile("^([\d\w]+) \d+ \d+$")
	patterns["link"] = re.compile("^([\d\w]+)-([\d\w]+)$")
	patterns["moves"] = re.compile("^(L[\d]+)-([\d\w]+)")
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
