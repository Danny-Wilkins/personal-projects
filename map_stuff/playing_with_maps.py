import numpy as np
import matplotlib.pyplot as plt
import cartopy.crs as ccrs
import cartopy.io.shapereader as shpreader
import csv, urllib, os, sys, zipfile


def country_select(country):

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

	if full_file_name == '':
		print("Country not found. Exiting...")
		sys.exit()

	return full_file_name[:-4]

def get_extent(country):

	with open('lat_lon_data/country-boundingboxes.csv', 'r') as lat_lon_data:
		csv_reader = csv.reader(lat_lon_data, delimiter=',')
		for row in csv_reader:
			if country.lower() in row[0].lower():
				return [float(row[2])-1, float(row[4])+1, float(row[3])-1, float(row[5])+1]

	return [-180, 180, -80, 80]

def download(url, name):
	urllib.urlretrieve(url, filename=name)

def extract(path):
	if not os.path.exists(path):
		with zipfile.ZipFile(path + '.zip', 'r') as zf:
			zf.extractall(path)
		print("Files extracted. Proceeding...")
	
def main():
	country = raw_input("Enter country: ")

	path = country_select(country)

	shp_file = path + '/' + path[4:-4] + '0.shp'

	draw(shp_file, get_extent(country))
	

def draw(fname, extent):
	print("Building...")

	reader = shpreader.Reader(fname)

	shapes = list(reader.geometries())

	ax = plt.axes(projection=ccrs.Mercator())

	ax.add_geometries(shapes, ccrs.Mercator(), \
					  edgecolor='black', facecolor='white')

	ax.set_extent(extent, ccrs.Mercator())

	print("Drawing...")

	plt.show()

if __name__=='__main__':
	main()