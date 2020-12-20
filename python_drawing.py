import turtle
from random import randint
import math

def hexagon_drawing(arr):
	colors = ['red', 'purple', 'blue', 'green', 'orange', 'yellow']
	t = turtle.Pen()
	turtle.bgcolor('black')
	for x in range(140):
	    t.pencolor(colors[x%6])
	    #print(turtle.xcor())
	    t.width(x/100 + 1)
	    t.forward(x)
	    t.left(58)
	    p = t.pos()               
	    arr.append([p[0] + 150, p[1] + 150])
	    #print(x,": ", p[0] + 150, " | y: ", p[1] + 150)

def random_triangle_drawing(arr):
	colors = ['red', 'purple', 'blue', 'green', 'orange', 'yellow']
	t = turtle.Pen()
	turtle.bgcolor('black')
	for x in range(15):
		t.pencolor('white')
		#t.up()
		rand_x = randint(50, 250)
		rand_y = randint(50, 250)
		t.goto(rand_x, rand_y)
		#t.down()
		arr.append([rand_x, rand_y])

		t.left(60)
		t.forward(50)
		arr.append([t.pos()[0], t.pos()[1]])

		t.right(120)
		t.forward(50)
		arr.append([t.pos()[0], t.pos()[1]])

		t.right(120)
		t.forward(50)
		arr.append([t.pos()[0], t.pos()[1]])

		#t.up()

def recursion_triangle_drawing(t, length, depth, arr):
	t.speed('fastest')
	if depth==0:
		for i in range(0,3):
			t.fd(length)
			print(t.pos()[0], t.pos()[1])
			arr.append([t.pos()[0], t.pos()[1]])
			t.left(120)
	else:
		recursion_triangle_drawing(t, length/2,depth-1, arr)
		arr.append([t.pos()[0], t.pos()[1]])
		print(t.pos()[0], t.pos()[1])
		t.fd(length/2)
		recursion_triangle_drawing(t, length/2,depth-1, arr)
		print(t.pos()[0], t.pos()[1])
		arr.append([t.pos()[0], t.pos()[1]])
		t.bk(length/2)
		print(t.pos()[0], t.pos()[1])
		arr.append([t.pos()[0], t.pos()[1]])
		t.left(60)
		t.fd(length/2)
		print(t.pos()[0], t.pos()[1])
		arr.append([t.pos()[0], t.pos()[1]])
		t.right(60)
		recursion_triangle_drawing(t, length/2,depth-1, arr)
		print(t.pos()[0], t.pos()[1])
		arr.append([t.pos()[0], t.pos()[1]])
		t.left(60)
		t.bk(length/2)
		print(t.pos()[0], t.pos()[1])
		arr.append([t.pos()[0], t.pos()[1]])
		t.right(60)

def nordic_triangle(t):
	t.speed(2)
	t.left(60)
	for x in range(50):
		t.forward(60)
		t.right(120)
		t.forward(50)
		t.up()
		t.forward(10)
		t.down()
		t.forward(20)
		t.right(120)
		t.forward(60)
		t.right(120)
		t.forward(50)
		t.up()
		t.forward(10)
		t.down()
		t.forward(20)
		t.right(120)
		t.forward(60)
		t.right(120)
		t.forward(50)
		t.up()
		t.forward(10)
		t.down()
		t.forward(20)
		t.right(120)

	

def circle_drawing(t):
	wn = turtle.Screen()
	wn.bgcolor('lightblue')
	fred = turtle.Turtle()
	sc = turtle.Screen()
	sc.reset()

	sc.setworldcoordinates(0,-1.5,360,1.5)
	for angle in range(360):
	    y = math.sin(math.radians(angle))
	    t.goto(angle,y)   

def plot_square():
	x1 = [1, 1]
	gcode_arr.append([x1[0], x1[1]])
	y1 = [2, 1]
	gcode_arr.append([y1[0], y1[1]])
	plt.plot(x1, y1)
	
	x2 = [2, 1]
	gcode_arr.append([x2[0], x2[1]])
	y2 = [2, 2]
	gcode_arr.append([y2[0], y2[1]])
	plt.plot(x2, y2)

	x3 = [2, 2]
	gcode_arr.append([x3[0], x3[1]])
	y3 = [1, 2]
	gcode_arr.append([y3[0], y3[1]])
	plt.plot(x3, y3)

	x4 = [1, 2]
	gcode_arr.append([x4[0], x4[1]])
	y4 = [1, 1]
	gcode_arr.append([y4[0], y4[1]])
	plt.plot(x4, y4)


def convert_to_gcode():
	gcode_arr = []


	''' 
	######################################################
	Infinite Hexagon
	######################################################
	'''
	#hexagon_drawing(gcode_arr)



	'''
	######################################################
	Random Triangles
	######################################################
	'''
	#random_triangle_drawing(gcode_arr)



	''' 
	######################################################
	Sierpinski Triangle
	######################################################
	'''
	#t = turtle.Turtle()
	#recursion_triangle_drawing(turtle, 300, 4, gcode_arr)



	''' 
	######################################################
	Nordic Triangle
	######################################################
	'''
	#t = turtle.Turtle()
	#nordic_triangle(turtle)



	'''
	######################################################
	Circle Drawing
	######################################################
	'''
	#t = turtle.Turtle()
	#circle_drawing(t)

	for i in range(len(gcode_arr)):
		gcode_arr[i][0] = round(gcode_arr[i][0], 5)
		gcode_arr[i][1] = round(gcode_arr[i][1], 5)
		print(gcode_arr[i])


if __name__ == "__main__":
	#print("Hello World")
	convert_to_gcode()