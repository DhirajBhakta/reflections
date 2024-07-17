_Take one point ...and find all nearest points_

Uber, Google Maps


#### Problem with Normal Index
(lat, lng in 2 columns in a table)
Lets say you put index on  lat.

To find a given point, you can traverse the lat index and run a range query. Now youve gotten billions of points between two latitudes. You cannot really hope to get a range query of(lng start, lng end) on this subset of billions of points. You have to run a scan on this subset of billions of points.

But you can use a BTree or a LSM Tree to make a geospatial index

## GeoHash
_As length of geohash increases, the size of the bounding box of the geohash decreases_

When you take all the geohashes and sort them, geohashes of closest bounding boxes would be close together!
If theyre close to one another on the index, they're close to each other in the real world too!


#### Finding nearby points
Find all points < 2km from (42.122, 12)
- convert start point to geohash (find the bounding box of the point and get its geohash)
- say the geohash is "9122vq3"
- you remove the "3" from the end, you get the parent bounding box "9122vq"..and so on.
- Find all points having the parent bounding box..and you get the set of points that you need to filter on

> if youre on the border of a bounding box, you lose out on points on the border of another bounding box, but net distance from points are actually minimal!
> this is a big CON (siblings of the parent box)

get all points between 9122vq3 < p < 9122vq4


#### Scaling a Geospatial Index
Cant store all points on one machine.

Partition on GeoHash.

The Tree stucture makes it easier to partition.
- box "A" and all its children on one node
- box "BA" and all its children on one node (box B is a hotspot)

#### Redis as a Geospatial Index
Lyft uses redis for storing geospatial index

#### Hexagons
Uber uses hexagons in place of squares. 
Hexagons are closer to circles.hence..


#### R-Tree
theyre not geohashes, but seem close




