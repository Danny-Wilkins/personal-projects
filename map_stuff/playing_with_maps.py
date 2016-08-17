import numpy as np
import matplotlib.pyplot as plt
import cartopy.crs as ccrs
import cartopy.io.shapereader as shpreader
import csv, urllib, os, sys, zipfile


def country_select():

	country = raw_input("Enter country: ")
	full_file_name = ''

	with open('reg_codes/slim-3/slim-3.csv', 'r') as region_codes:
		csv_reader = csv.reader(region_codes, delimiter=',')
		for row in csv_reader:
			if country.lower() in row[0].lower():
				file_url = 'http://biogeo.ucdavis.edu/data/gadm2.8/shp/{}_adm_shp.zip'.format(row[1])
				file_name = '{}_adm_shp.zip'.format(row[1])
				full_file_name = os.path.join('shp', file_name)

				print("Downloading {}...".format(file_name))
				
				if os.path.exists(full_file_name):
					print("File exists. Proceeding...")
					print("Extracting...")
					extract(full_file_name[:-4])
					print("Files extracted. Proceeding...")
					
				else:
					download(file_url, full_file_name)
					print("Download complete. Proceeding...")
					print("Extracting...")
					extract(full_file_name[:-4])
					print("Files extracted. Proceeding...")

	return full_file_name[:-4]

def download(url, name):
	urllib.urlretrieve(url, filename=name)

def extract(path):
	if not os.path.exists(path):
		zipfile.ZipFile(path + '.zip').extractall(path)
		print("Files extracted. Proceeding...")
	
def main():
	path = country_select()

	shp_file = path + '/' + path[4:-4] + '0.shp'

	draw(shp_file)
	

def draw(fname):
	print("Building...")

	reader = shpreader.Reader(fname)

	shapes = list(reader.geometries())

	ax = plt.axes(projection=ccrs.PlateCarree())

	ax.add_geometries(shapes, ccrs.PlateCarree(), \
					  edgecolor='black', facecolor='white', alpha=0.5)

	#ax.set_extent([-180, 50, 0, 80], ccrs.PlateCarree())

	#plt.title('Countries')

	#ax.coastlines()

	print("Drawing...")

	plt.show()

if __name__=='__main__':
	main()