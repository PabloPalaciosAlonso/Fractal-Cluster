import numpy as np
def readMatrix(name,folder="",delimiter=" ",ignore="", decimal = ".", remove = 0):
     if len(folder)>0:
          folder+="/"
     File=open(folder+name,'r')
     Matrix=[]

     for line in File:
          line = line[remove:]
          if not line.replace(ignore,"")[0].isdigit() and line.replace(ignore,"")[0]!="-":
               continue
          
          linea=line.strip().replace(ignore,"").replace("\t"," ").replace(delimiter," ").replace(decimal, ".").split(" ")
          LineaNum=[]
          ncols = len(linea)     
          for num in linea:
               if len(num)==0:
                    continue
               if '.' in num or 'e' in num or "E" in num:
                    num=num.replace(" ","")
                    LineaNum+=[float(num)]
               else:
                    num=num.replace(" ","")
                    LineaNum+=[int(num)]
          
          if ncols>1:
               Matrix+=[LineaNum]
          else:
               Matrix+=LineaNum
     return np.array(Matrix)


def least_squares(x,y, xscale = 'linear', yscale = 'linear', go_throug_origin = False):

     nx = len(x)
     ny = len(y)
     if (nx!=ny):
          raise Exception("ERROR: The length of x and y are different")
     if yscale == 'log':
          positiveValues = np.where(y>0)[0]
          x = x[positiveValues]
          y = np.log(y[positiveValues])
          nx = len(x)
          ny = len(x)
     if xscale == 'log':
          positiveValues = np.where(x>0)[0]
          x = np.log(x[positiveValues])
          y = y[positiveValues]
          nx = len(x)
          ny = len(x)
     sx = np.sum(x)
     sy = np.sum(y)
     sxy = np.sum(x*y)
     sx2 = np.sum(x*x)
     s2x = sx*sx
     den = nx*sx2-s2x

     m = (nx*sxy-sx*sy)/den
     n = (sx2*sy-sx*sxy)/den

     S = np.sqrt(np.sum((y-m*x-n)*(y-m*x-n))/(nx-2))

     dm = S * np.sqrt((nx)/den)
     dn = S * np.sqrt(sx2/den)

     if go_throug_origin:
          n = 0
          dn = 0.0
          m = sxy/sx2

     return m,n,dm,dn
