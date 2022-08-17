# Fractal cluster
P. Palacios Alonso 2022.

fc-Generates a random set of positions of spheres in a fractal cluster.

In a fractal cluster the number of particles in the cluster and its gyration radius verifies,

$N = k_f \cdot (R_g/radius)^D_f$ (1)

Where:

   - N = Number of spheres in the cluster.
   - Radius = Radius of the spheres.
   - Df = Fractal dimension of the cluster.
   - kf = Fractal prefactor of the cluster.
   - R_g = Gyration radius of the cluster $R_g^2 = 1/N \cdot \sum (\mathbf{r_i}-\mathbf{c_m})^2$.
   
# Compile with
   $ make
You can test the code after compiling with:

   $ cp fc test/fc; chmod +x test.bash; ./test.bash
   
It will generate some clusters with different number of spheres and copmute the gyration radius as a function of the number of particles to see if relation 1 is verified.
You can edit the file test.bash to choose the different paramters. 

  
