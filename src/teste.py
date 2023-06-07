import numpy
import matplotlib.pyplot as plt

matrixY= [300,0,400,-1000,3300,-9900,30800,-94500,291400,-897000]

#polynomial regression of degree 9
polynomial = numpy.polyfit(range(0,10), matrixY, 9)
# plot 
x_axis = numpy.linspace(0, 10, 100)
y_axis = numpy.polyval(polynomial, x_axis)
plt.plot(x_axis, y_axis)
plt.show()


#return the derivate of each point
def derivate(matrixY):
  derivate = []
  for i in range(0,len(matrixY)-1):
      derivate.append(matrixY[i+1]-matrixY[i])
  return derivate

#return the derivate of each point
for i in range(0,len(matrixY)-1):
  print(derivate(matrixY)[i])

