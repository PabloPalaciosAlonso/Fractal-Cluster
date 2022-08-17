# Fractal cluster
P. Palacios Alonso 2022.

fc - Generates a random set of positions of spheres in a fractal cluster.

In a fractal cluster the number of particles in the cluster and its gyration radius verifies,

$N = k_f \cdot (R_g/a)^{D_f}$ (1)

Where:

   - N = Number of spheres in the cluster.
   - a = Radius of the spheres.
   - Df = Fractal dimension of the cluster.
   - kf = Fractal prefactor of the cluster.
   - $R_g$ = Gyration radius of the cluster $R_g^2 = 1/N \cdot \sum (\mathbf{r_i}-\mathbf{c_m})^2$.
   
# Compile with
```bash
$ make
```
You can test the code after compiling with:
```bash
$ cp fc test/fc; chmod +x test.bash; ./test.bash
```
It will generate some clusters with different number of spheres and then compute the gyration radius of the aggregates as a function of the number of particles composing the cluster, in order to test if relation 1 is verified. If it is verified in a log-log plot the gyration radius a a funtion of the number of particles should be a straigh line with slope $D_f$ and y-intercept equals to $ln(k_f/a^{D_f})$.

You can edit the file test.bash to choose the different paramters. 

# Usage

 ```bash
 ./fc [INPUTS]
 ```
 
 - Required inputs
   - -N: Number of the spheres in the cluster.
   - -Radius: Radius of the spheres.
   - -Df: Fractal dimension of the cluster.
   - -kf: Fractal prefactor of the cluster.
 - Optional inputs
   - -filename: Name of a file in which to store the positions of the particles. If no filename is provided the positions are displayed in the comand line.
   - -h: Prints a help message.
  
# Example
```bash
./fc -N 5000 -Df 1.8 -kf 1.1 -radius 0.5 -filename fc.out
 ```
 
 It will generate a fractal cluster with N = 5000 spheres, fractal dimension Df = 1.8, fractal prefactor kf = 1.1 and radius = 0.5 and store the x y z coordinates of the centers of the spheres in the file fc.out.
 
 <img src="https://github.com/PabloPalaciosAlonso/Fractal-Cluster/blob/main/res/example.png" width="600">
 
Generated cluster visualized with superpunto (https://github.com/RaulPPelaez/superpunto).
   
