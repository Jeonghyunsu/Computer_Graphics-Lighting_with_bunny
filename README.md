# Lighting_with_bunny [Computre Graphics]

▶ Stanford Bunny

* bunny_oringin.txt

// # of points and triangles

453 

// 3D positions

0.875114 0.105216 0.020597

0.82129 0.124816 0.0228192

...


// Point indices for triangle

86 193 163

208 63 111

...

* Draw the bunny using GL_TRIANGLES

▶ Vertex Normal Vectors

▶ Light Sources

* Make a directional light, point light, and spot light

-In the best positions

-With the best parameters

* Rotate the position (and direction) of each light

-About the vector (1, 1, 1)

-1 rotation per 4 seconds

-‘p’/‘d’/‘s’ key to toggle the rotation of the point/directional/spot lights, respectively

▶ Cut-off Angle

* Change the cut-off angle of the spot light

-5 degree at the minimum

-25 degree at the maximum

-1 cycle per 4 seconds

-‘c’ key to toggle

* Use the timer function

-glutTimerFunc();

-void timer(int value);

▶ Shininess Coefficient

* Change the shininess coefficient of the spot light

-Within an appropriate range

-1 cycle per 4 seconds

-‘n’ key to toggle



