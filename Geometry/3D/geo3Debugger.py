from vpython import *
import sys
  
print("This is the name of the program:", sys.argv[0])
  
print("Argument List:", str(sys.argv))

def point(i):
    return tuple(float(next(i)) for j in range(3))
def getcolor(i):
    return getattr(color, next(i).strip())
def PT(i):
    pt = point(i)
    return points(pos=[vector(*pt)], radius=10, color=getcolor(i))
def SEG(i):
    pt1 = point(i)
    pt2 = point(i)
    return cylinder(pos=vector(*pt1), axis=vector(*pt2), radius=0.01,color = getcolor(i))
def POLY(i):
    n = int(next(i))
    l = [None]*n
    for j in range(n):
        l[j] = point(i)
    face = [None]*(n-2)
    mycolor = getcolor(i)
    for j in range(1,n-1):
        
        face[j-1] = triangle(
          v0=vertex( pos=vec(*l[0]),opacity = 0.4, color = mycolor),
          v1=vertex( pos=vec(*l[j]),opacity = 0.4, color = mycolor),
          v2=vertex( pos=vec(*l[j+1]),opacity = 0.4, color = mycolor) )
    # Very slow!
    # def order(n):
    #     for j in range(1,n-1):
    #         yield 0
    #         yield j
    #         yield j+1
    # pos = [l[k] for k in order(n)]
    # tri = faces(pos = pos,color = [[1.,0.,1.]*(n-2)])
    # return tri

    # tri.make_normals()
    # tri.make_twosided()
    return compound(face)

primitives = {"SEG":SEG,"PT":PT, "POLY":POLY}
scene.width = 1700
scene.height = 900
scene.title = "Geo 3Debugger"
stack = []
active = []
with open("convexhull.txt") as ss:
    for p in ss:
        p = p.strip()
        lijst = p.split(' ')
        i = iter(lijst)
        name = next(i)
        if name == "PAUSE":
            if len(active):
                stack.append(active)
                active = []
        else:
            tmp = primitives[name](i)
            active.append(tmp)
            pass
p = -1
def step(b):
    global p
    if p ==-1:
        for j in stack:
            for i in j:
                i.visible = False
        p+=1
        return
    if p==len(stack):
        return

    for i in stack[p]:
        i.visible = True
    p+=1
button( bind=step, text='Step')
scene.bind('keydown', step)

    
        
