# Computer Graphics lab Assignments

This repo contains the computer graphics lab assignments all implemented in C++ using the QT-5 
framework.

The assignments are :

* Drawing : Contains the implementation of a raster screen with axes to show pixels where pixel size
can be varied using a spin box. It provides mouse interactivity for colouring pixels on the screen.

* Line Drawing: It is made on top of the raster screen. It contains the implementation of the two 
line drawing algorithms and compares the speed on painting a line with the two respective algorithms.

- DDA : It is based on the concept of slopes and involves floating point calculations which causes 
the algirithm to be comparitively slower than Bressenham algorithm.

- Bressenham : It is based on the difference of the distance between the perfect line and the 
corresponding pixel painted to signify a part of the line. A recurrence relation is formed due to 
which it avoids totally the use of floating point calculations due to which this algorithm is much 
faster than DDA algorithm.
