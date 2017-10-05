#!/usr/local/bin/python
import math
from os import listdir
from os.path import isfile, join
import mmap
import mysql.connector



class FillDB():
	def WriteToDB_CCD(self):
		'Initial population of ccd database with name and positions'
		parse_dir =  realpath(join(__file__ ,"../")) #not sure if this works on windows, better options in python 3+      

		name_aside = open(parse_dir+'/GlobalPostions/NameMaps/name_map_aside.txt', 'r')
		name_cside = open(parse_dir+'/GlobalPostions/NameMaps/name_map_cside.txt', 'r')

		gpos_baz_a = open(parse_dir+'/GlobalPostions/GP_output/baz_aside_pos.txt', 'r') 
		gpos_baz_c = open(parse_dir+'/GlobalPostions/GP_output/baz_cside_pos.txt', 'r') 
		gpos_bpl_a = open(parse_dir+'/GlobalPostions/GP_output/bpl_aside_pos.txt', 'r') 
		gpos_bpl_c = open(parse_dir+'/GlobalPostions/GP_output/bpl_cside_pos.txt', 'r') 

		fout_baz_a = open(parse_dir+'/ForDataBase/DB_Output/db_baz_aside.txt', 'w')
		fout_bpl_a = open(parse_dir+'/ForDataBase/DB_Output/db_bpl_aside.txt', 'w')
		fout_baz_c = open(parse_dir+'/ForDataBase/DB_Output/db_baz_cside.txt', 'w')
		fout_bpl_c = open(parse_dir+'/ForDataBase/DB_Output/db_bpl_cside.txt', 'w')    

		cnx = mysql.connector.connect(user='root', database='darkcurrent', passwd="")
		cursor = cnx.cursor()


		image_name = ""
		image_name2 = ""
		image_name3 = ""
		image_name4 = ""
		gpos_baz_a = open(parse_dir+'/GlobalPostions/GP_output/baz_aside_pos.txt', 'r') 
		for pos in gpos_baz_a:
			image_name = pos.strip().split()[0].strip()
			name_aside = open(parse_dir+'/GlobalPostions/NameMaps/name_map_aside.txt', 'r')
			for name in name_aside:
				image_name2 = name.strip().split()[1].strip()
				image_name3 = name.strip().split()[0].strip()
				if image_name3.find("BAZ_A") == -1: #somehting weird with name map - what's the bsd doing?
					continue                
				if image_name != image_name2:
					continue        
				fout_baz_a.write(image_name3+" "+image_name+(pos[len(image_name):]).rstrip()+"\n")#+(val[len(image_name3):]).rstrip()+"\n")
				thisline = pos.rstrip().split()
				nameimage = image_name3
				namearamys = thisline[0]
				xval = thisline[1]
				yval = thisline[2]
				zval = thisline[3]
				rval = thisline[4]
				add_entry = ("INSERT INTO `ccd` "
				             "(imageName, aramysName, x, y, z, r)"
				             " VALUES ('"+nameimage+"', '"+namearamys+"', "+xval+", "+yval+", "+zval+", "+rval+");")
				cursor.execute(add_entry)


		image_name = ""
		image_name2 = ""
		image_name3 = ""
		image_name4 = ""
		gpos_baz_c = open(parse_dir+'/GlobalPostions/GP_output/baz_cside_pos.txt', 'r') 
		for pos in gpos_baz_c:           
			image_name = pos.strip().split()[0].strip()          
			name_cside = open(parse_dir+'/GlobalPostions/NameMaps/name_map_cside.txt', 'r')
			for name in name_cside:
				image_name2 = name.strip().split()[1].strip()
				image_name3 = name.strip().split()[0].strip()
				if image_name3.find("BAZ_C") == -1:
					continue               
				if image_name != image_name2:
					continue        
				fout_baz_c.write(image_name3+" "+image_name+(pos[len(image_name):]).rstrip()+"\n")#+(val[len(image_name3):]).rstrip()+"\n")
				thisline = pos.rstrip().split()
				nameimage = image_name3
				namearamys = thisline[0]
				xval = thisline[1]
				yval = thisline[2]
				zval = thisline[3]
				rval = thisline[4]
				add_entry = ("INSERT INTO `ccd` "
				             "(imageName, aramysName, x, y, z, r)"
				             " VALUES ('"+nameimage+"', '"+namearamys+"', "+xval+", "+yval+", "+zval+", "+rval+");")
				cursor.execute(add_entry)                  

		image_name = ""
		image_name2 = ""
		image_name3 = ""
		image_name4 = ""
		gpos_bpl_a = open(parse_dir+'/GlobalPostions/GP_output/bpl_aside_pos.txt', 'r') 
		for pos in gpos_bpl_a:
			image_name = pos.strip().split()[0].strip()
			name_aside = open(parse_dir+'/GlobalPostions/NameMaps/name_map_aside.txt', 'r')
			for name in name_aside:
				image_name2 = name.strip().split()[1].strip()
				image_name3 = name.strip().split()[0].strip()
				if image_name3.find("BPL_A") == -1:
					continue                            
				if image_name != image_name2:
					continue        
				fout_bpl_a.write(image_name3+" "+image_name+(pos[len(image_name):]).rstrip()+"\n")#+(val[len(image_name3):]).rstrip()+"\n")
				thisline = pos.rstrip().split()
				nameimage = image_name3
				namearamys = thisline[0]
				xval = thisline[1]
				yval = thisline[2]
				zval = thisline[3]
				rval = thisline[4]
				add_entry = ("INSERT INTO `ccd` "
				             "(imageName, aramysName, x, y, z, r)"
				             " VALUES ('"+nameimage+"', '"+namearamys+"', "+xval+", "+yval+", "+zval+", "+rval+");")
				cursor.execute(add_entry)                

		image_name = ""
		image_name2 = ""
		image_name3 = ""
		image_name4 = ""
		gpos_bpl_c = open(parse_dir+'/GlobalPostions/GP_output/bpl_cside_pos.txt', 'r') 
		for pos in gpos_bpl_c:
			image_name = pos.strip().split()[0].strip()        
			name_cside = open(parse_dir+'/GlobalPostions/NameMaps/name_map_cside.txt', 'r')
			for name in name_cside:
				image_name2 = name.strip().split()[1].strip()
				image_name3 = name.strip().split()[0].strip()
				if image_name3.find("BPL_C") == -1:
					continue                
				if image_name != image_name2:
					continue        
				fout_bpl_c.write(image_name3+" "+image_name+(pos[len(image_name):]).rstrip()+"\n")#+(val[len(image_name3):]).rstrip()+"\n")
				thisline = pos.rstrip().split()
				nameimage = image_name3
				namearamys = thisline[0]
				xval = thisline[1]
				yval = thisline[2]
				zval = thisline[3]
				rval = thisline[4]
				add_entry = ("INSERT INTO `ccd` "
				             "(imageName, aramysName, x, y, z, r)"
				             " VALUES ('"+nameimage+"', '"+namearamys+"', "+xval+", "+yval+", "+zval+", "+rval+");")
				cursor.execute(add_entry)

		cnx.commit()
		cursor.close()
		cnx.close()                


	def AppendToDB_CCD(self, thepath, month):
		'Append avgIntensity reading for each ccd every month. Takes as input the path to the location of the .txt files'
		'created using LWDAQ Toolmaker script, and the month prefix (which must be a column in sql database listed as '
		'month_avgIntensity. The usual format is to have month - a misnomer - represented as MMMYY, eg. jul16'
		cnx = mysql.connector.connect(user='root', database='darkcurrent', passwd="")
		cursor = cnx.cursor()           

		onlyfiles = [f for f in listdir(thepath) if isfile(join(thepath, f))]
		for file in onlyfiles:
			image_name = file[:-4]
			infile = open(thepath+file, 'r')
			first_line = infile.readline().strip().split()

			avgIntensity = first_line[4]
			infile.close()

			update_entry_avg = ("UPDATE `ccd` SET "+month+"_avgIntensity="+avgIntensity+" WHERE imageName=\""+image_name+"\";")
			cursor.execute(update_entry_avg)

		cnx.commit()
		cursor.close()
		cnx.close()

		return 



	def WriteToDB_Pixels(self, thepath):
		'Initial population of pixel database with aramys name, image name, row and column numbers and positions'
		
		cnx = mysql.connector.connect(user='root', database='darkcurrent', passwd="")
		cursor = cnx.cursor()           

		onlyfiles = [f for f in listdir(thepath) if isfile(join(thepath, f))]
		for file in onlyfiles:
			image_name = file[:-4]
			infile = open(thepath+file, 'r')
			for line in infile:
				line = line.strip().split()
				row = line[0]
				col = line[1]
				full_name = image_name+"_"+row+"_"+col
				sqlq = "SELECT COUNT(1) FROM `ccd` WHERE imageName = '"+image_name+"'"
				cursor.execute(sqlq)
				if cursor.fetchone()[0]:
					add_entry = ("INSERT INTO `pixel` "
					             "(fullName, row_num, col_num, imageName)"
					             " VALUES ('"+full_name+"', "+row+", "+col+", '"+image_name+"');") 
					cursor.execute(add_entry)
			infile.close()
			cnx.commit()                      

		cursor.close()
		cnx.close() 

		return        


	def AppendToDB_Pixels(self, thepath, month):
		'Append each pixels intensity and difference from CCD average reading for every month. Takes as input the '
		'path to the location of the .txt files created using LWDAQ Toolmaker script, and the month prefix '
		'(which must be a column in sql database listed as month_avgIntensity. The usual format is to have '
		'month - a misnomer - represented as MMMYY, eg. jul16'		
		cnx = mysql.connector.connect(user='root', database='darkcurrent', passwd="")
		cursor = cnx.cursor()

		onlyfiles = [f for f in listdir(thepath) if isfile(join(thepath, f))]
		for file in onlyfiles:
			image_name = file[:-4]
			infile = open(thepath+file, 'r')
			for line in infile:
				line = line.strip().split()
				row = line[0]
				col = line[1]                
				intensity = line[3]
				diff = line[2]
				full_name = image_name+"_"+row+"_"+col
				sqlq = "SELECT COUNT(1) FROM `ccd` WHERE imageName = '"+image_name+"'"
				cursor.execute(sqlq)
				if cursor.fetchone()[0]:
					update_entry_avg = ("UPDATE `pixel` SET "+month+"_intensity="+intensity+" WHERE fullName=\""+full_name+"\";")
					cursor.execute(update_entry_avg)
					update_entry_diff = ("UPDATE `pixel` SET "+month+"_diffFromAvg="+diff+" WHERE fullName=\""+full_name+"\";")
					cursor.execute(update_entry_diff)
			infile.close()
			cnx.commit()                      

		cursor.close()
		cnx.close() 

		return            

def main():

	r = FillDB()    
	##r.WriteToDB_CCD()
	r.AppendToDB_CCD("/Users/dhaliwal/Work/Alignment/DarkCurrent/DC_Images/ForDB/Jul11/", "jul17")
	##r.WriteToDB_Pixels("/Users/dhaliwal/Work/Alignment/DarkCurrent/DC_Images/ForDB/May19/")
	#r.AppendToDB_Pixels("/Users/dhaliwal/Work/Alignment/DarkCurrent/DC_Images/ForDB/Jul11/", "jul17")
	#r.AppendToDB_Pixels("/Users/dhaliwal/Work/Alignment/DarkCurrent/DC_Images/ForDB/Mar21/", "mar17")
if __name__ == "__main__":
	main()

