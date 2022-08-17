Df=2
kf=1
radius=1

for i in {1..12}
do
    ((nParticles=5*(2**$i)))
    filename="FC"$nParticles".out"
    ./fc -N $nParticles -Df $Df -kf $kf -radius $radius -filename $filename
done
python testFractals.py $Df $kf $radius
rm FC*.out
    
