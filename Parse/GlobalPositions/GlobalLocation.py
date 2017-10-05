#!/usr/local/bin/python
import math
from os import listdir
from os.path import isfile, join, realpath
import mmap
import sys

class WriteMapOfNames():
	def __init__(self, imagepath):
		self.imagepath = imagepath
		self.images_aside_dir = []
		self.images_cside_dir = []
		self.images_aside = []
		self.images_cside = []
		self.images_aside_notfound = []
		self.images_cside_notfound = []
		self.count_found_aside = 0
		self.count_notfound_aside = 0
		self.count_found_cside = 0
		self.count_notfound_cside = 0

	def ReadAvailableCCDImages(self):
		'Grabs the available .ccd files in some specified directory of darkcurrent readings (ccd files), and appends'
		'the available image names to a list. These are the images that will then get a mapping to aramys names'
		
		onlyfiles = [f for f in listdir(self.imagepath) if isfile(join(self.imagepath, f))]
		for file in onlyfiles:
			if file[4] == 'A':
				self.images_aside_dir.append("BCAM "+file[0:-4]+"_1")
			if file[4] == 'C':
				self.images_cside_dir.append("BCAM "+file[0:-4]+"_1")
		return


	def CheckImagesAgainstSensorsFile(self):
		'This is the function that actual maps the image name with the aramys name. aramys name is taken from'
		'sensors.db.gen files used in the alignment. The output is three text files (a side, c side, both sides) that list'
		'the image name and corresponding aramys name'
		
		parse_dir =  realpath(join(__file__ ,"../..")) #not sure if this works on windows, better options in python 3+      

		sensors_aside = open(parse_dir+'/ARAMyS_files/sensors.db.gen_aside', 'r')
		sensors_cside = open(parse_dir+'/ARAMyS_files/sensors.db.gen_cside', 'r')
		name_map_aside = open(parse_dir+'/GlobalPostions/NameMaps/name_map_aside.txt', 'w')
		name_map_cside = open(parse_dir+'/GlobalPostions/NameMaps/name_map_cside.txt', 'w')
		name_map = open(parse_dir+'/GlobalPostions/NameMaps/name_map.txt', 'w')

		for image in self.images_aside_dir:
			found = False
			s_aside = mmap.mmap(sensors_aside.fileno(), 0, access=mmap.ACCESS_READ)

			for line in iter(s_aside.readline, ""):
				if line.find(image) != -1:
					found = True
					self.images_aside.append(line.strip().split()[2])
					name_map_aside.write(line.strip().split()[1][:-2]+" "+line.strip().split()[2]+"\n")
					name_map.write(line.strip().split()[1][:-2]+" "+line.strip().split()[2]+"\n")
					break
				else:
					self.images_aside_notfound.append(line.strip().split()[1])
			if found == True:
				self.count_found_aside = self.count_found_aside + 1
			else:
				self.count_notfound_aside = self.count_notfound_aside + 1


		for image in self.images_cside_dir:
			found = False
			s_cside = mmap.mmap(sensors_cside.fileno(), 0, access=mmap.ACCESS_READ)

			for line in iter(s_cside.readline, ""):
				if line.find(image) != -1:
					found = True
					self.images_cside.append(line.strip().split()[2])
					name_map_cside.write(line.strip().split()[1][:-2]+" "+line.strip().split()[2]+"\n")
					name_map.write(line.strip().split()[1][-2]+" "+line.strip().split()[2]+"\n")
					break
				else:
					self.images_cside_notfound.append(line.strip().split()[1])
			if found == True:
				self.count_found_cside = self.count_found_cside + 1
			else:
				self.count_notfound_cside = self.count_notfound_cside + 1

		return


class FindGlobalPositions():
	def ReadPointsFiles(self):
		'Function takes information from aramys files used in alignment and writes out parsed information about global'
		'postions per aramys name. Output goes into GP_output dir, and there will be screen print outs too.'
		
		parse_dir =  realpath(join(__file__ ,"../..")) #not sure if this works on windows, better options in python 3+      
	
		sensors_aside = open(parse_dir+'/ARAMyS_files/sensors.db.gen_aside', 'r')		
		points_aside = open(parse_dir+'/ARAMyS_files/aside_points.txt', 'r')
		points_cside = open(parse_dir+'/ARAMyS_files/cside_points.txt', 'r')
		p_aside = mmap.mmap(points_aside.fileno(), 0, access=mmap.ACCESS_READ)
		p_cside = mmap.mmap(points_cside.fileno(), 0, access=mmap.ACCESS_READ)
		baz_aside_pos = open(parse_dir+'/GlobalPostions/GP_output/baz_aside_pos.txt', 'w')
		baz_cside_pos = open(parse_dir+'/GlobalPostions/GP_output/baz_cside_pos.txt', 'w')
		bpl_aside_pos = open(parse_dir+'/GlobalPostions/GP_output/bpl_aside_pos.txt', 'w')
		bpl_cside_pos = open(parse_dir+'/GlobalPostions/GP_output/bpl_cside_pos.txt', 'w')

		space = " "
		for line in points_aside:
			line = line.strip().split()
			name = line[7]
#            if name.find('baz') != -1 and name.find('aei') != -1 and name[-4:] == "c2_p":
			if name.find('baz') != -1 and name[-2:] == "_p":
#            if name[-4:] == "c2_p":
				x_pos = float(line[1])
				y_pos = float(line[2])
				z_pos = float(line[3])
				r2 = math.sqrt( (x_pos)*(x_pos) + (y_pos)*(y_pos) )
				r3 = math.sqrt( (x_pos)*(x_pos) + (y_pos)*(y_pos) + (z_pos)*(z_pos) )
#                print line
				print "name = "+name+", x = "+str(x_pos)+", y = "+str(y_pos)+", z = "+str(z_pos)+", r2 = "+str(r2)+", r3 = "+str(r3)
				baz_aside_pos.write(name+space+str(x_pos)+space+str(y_pos)+space+str(z_pos)+space+str(r2)+space+str(r3)+"\n")

#            if name.find('baz') != -1 and name.find('aei') != -1 and name[-4:] == "c2_p":
			if name.find('bpl') != -1 and name[-2:] == "_p":
#            if name[-4:] == "c2_p":
				x_pos = float(line[1])
				y_pos = float(line[2])
				z_pos = float(line[3])
				r2 = math.sqrt( (x_pos)*(x_pos) + (y_pos)*(y_pos) )
				r3 = math.sqrt( (x_pos)*(x_pos) + (y_pos)*(y_pos) + (z_pos)*(z_pos) )
#                print line
				print "name = "+name+", x = "+str(x_pos)+", y = "+str(y_pos)+", z = "+str(z_pos)+", r2 = "+str(r2)+", r3 = "+str(r3)                
				bpl_aside_pos.write(name+space+str(x_pos)+space+str(y_pos)+space+str(z_pos)+space+str(r2)+space+str(r3)+"\n")

		for line in points_cside:
			line = line.strip().split()
			name = line[7]
#            if name.find('baz') != -1 and name.find('aei') != -1 and name[-4:] == "c2_p":
			if name.find('baz') != -1 and name[-2:] == "_p":
#            if name[-4:] == "c2_p":
				x_pos = float(line[1])
				y_pos = float(line[2])
				z_pos = float(line[3])
				r2 = math.sqrt( (x_pos)*(x_pos) + (y_pos)*(y_pos) )
				r3 = math.sqrt( (x_pos)*(x_pos) + (y_pos)*(y_pos) + (z_pos)*(z_pos) )
#                print line
				print "name = "+name+", x = "+str(x_pos)+", y = "+str(y_pos)+", z = "+str(z_pos)+", r2 = "+str(r2)+", r3 = "+str(r3)
				baz_cside_pos.write(name+space+str(x_pos)+space+str(y_pos)+space+str(z_pos)+space+str(r2)+space+str(r3)+"\n")

#            if name.find('baz') != -1 and name.find('aei') != -1 and name[-4:] == "c2_p":
			if name.find('bpl') != -1 and name[-2:] == "_p":
#            if name[-4:] == "c2_p":
				x_pos = float(line[1])
				y_pos = float(line[2])
				z_pos = float(line[3])
				r2 = math.sqrt( (x_pos)*(x_pos) + (y_pos)*(y_pos) )
				r3 = math.sqrt( (x_pos)*(x_pos) + (y_pos)*(y_pos) + (z_pos)*(z_pos) )
#                print line
				print "name = "+name+", x = "+str(x_pos)+", y = "+str(y_pos)+", z = "+str(z_pos)+", r2 = "+str(r2)+", r3 = "+str(r3)                
				bpl_cside_pos.write(name+space+str(x_pos)+space+str(y_pos)+space+str(z_pos)+space+str(r2)+space+str(r3)+"\n")


def main():

	
	#Execute all three below in sequence to recreate name files, should put this in a wrapper
	#w = WriteMapOfNames("/Users/dhaliwal/Dropbox/Work/Alignment/DarkCurrent/darkcurrent/DC_Images/May19")
	#w.ReadAvailableCCDImages()
	#w.CheckImagesAgainstSensorsFile()
	
	#Execute below for creating global postions file
	r = FindGlobalPositions()
	r.ReadPointsFiles()


if __name__ == "__main__":
	main()

