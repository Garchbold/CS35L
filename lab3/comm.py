#!/usr/bin/python                                                               

import re
import sys
from optparse import OptionParser
import locale
import string

class comm:
	def __init__(self, filename1, filename2, unsorted):
		if filename1 != "-":
			f = open (filename1, 'r')
			self.lines1 = f.read().strip().split('\n')
			f.close ()

		if filename1 == "-": 
			self.lines1 = sys.stdin.read().split('\n')

		if filename2 != "-":
			g = open (filename2, 'r')
			self.lines2 = g.read().strip().split('\n')
			g.close ()
		
		if filename2 == "-":
			self.lines2 = sys.stdin.read().split('\n') 
		
		self.p = re.compile(' *')
		self.list1 = []
		self.list2 = []
		self.list3 = []
		self.unsorted = unsorted
		self.finallist1 = []	
	def compare (self):
		i = 0
		j = 0
		
		if self.unsorted == True:
			for i in range(len(self.lines1)):
				for j in range(len(self.lines2)):
					if self.lines1[i] == self.lines2[j]:
					
						self.list1.append("        ")
						self.list2.append("        ")
						self.list3.append(self.lines1[i])
						del(self.lines2[j])  
						break
	
					elif j == len(self.lines2) - 1:
						self.list1.append(self.lines1[i])
						self.list2.append("")
						self.list3.append("")
					else:
						continue
			for k in range(len(self.lines2)):
				self.list1.append("        ")
				self.list3.append("")
			self.list2 += self.lines2					
		
		if self.unsorted == False:
			
			if self.lines1 != sorted(self.lines1):
				sys.stderr.write('comm.py: unsorted file1\n')
			if self.lines1 != sorted(self.lines1):
				sys.stderr.write('comm.py: unsorted file2\n')

			while i < len(self.lines1) and j < len(self.lines2):
			
				if self.lines1[i] == self.lines2[j]:
					self.list1.append("        ")
					self.list2.append("        ")
					self.list3.append(self.lines1[i])
					i += 1
					j += 1
				elif self.lines1[i] < self.lines2[j]:
					self.list1.append(self.lines1[i])
					self.list2.append("")
					self.list3.append("")
					i += 1
				else:
					self.list1.append("        ")
					self.list2.append(self.lines2[j])
					self.list3.append("")
					j += 1
			while i == len(self.lines1) and j < len(self.lines2):
				self.list2.append(self.lines2[j])
				self.list1.append("        ")
				self.list3.append("")
				j += 1

			while i < len(self.lines1) and j == len(self.lines2):				
				self.list1.append(self.lines1[i])
				self.list2.append("")
				self.list3.append("")
				i += 1


	def finalprint(self, sup1, sup2, sup3):	
		if sup1 == True:
			for i in range(len(self.list1)):
				self.list1[i] = ""

		if sup2 == True:
			for i in range(len(self.list2)):	
				self.list2[i] = ""

		if sup3 == True:
			for i in range(len(self.list3)):
				self.list3[i] = ""

		for i in range(len(self.list1)):
			if (self.list1[i] == "" or self.list1[i] == "        ") and (self.list2[i] == "" or self.list2[i] == "        ") and (self.list3[i] == "" or self.list3[i] == "        "):
				continue	
			else:
				print(self.list1[i] + self.list2[i] + self.list3[i])

			
def main():
	version_msg = "%prog 2.0"
	usage_msg = """%prog [OPTION]... FILE: Output randomly selected lines from FILE."""

	parser = OptionParser(version=version_msg, usage=usage_msg)
	parser.add_option("-u", action="store_true", dest="unsorted", default=False, help="Used on unsorted lists")
	parser.add_option("-1", action="store_true", dest="sup1", default=False, help="This flag suppresses the first column")
	parser.add_option("-2", action="store_true", dest="sup2", default=False, help="This flag suppresses the second column")
	parser.add_option("-3", action="store_true", dest="sup3", default=False, help="This flag suppresses the third column")
	options, args = parser.parse_args(sys.argv[1:])
	
	try:
		unsorted = bool(options.unsorted)
		sup1 = bool(options.sup1)
		sup2 = bool(options.sup2)
		sup3 = bool(options.sup3)


	except:
		parser.error("invalid unsorted: {0}")	

	input1 = args[0]
	input2 = args[1]

	if len(args) != 2:
		parser.error("incorrect number of inputs, must be 2 files")
	comp = comm(input1, input2, unsorted)
	comp.compare()
	comp.finalprint(sup1, sup2, sup3)
	
if __name__ == "__main__":
	main()

