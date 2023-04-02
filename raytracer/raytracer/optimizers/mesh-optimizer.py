def read_mesh(file):
  """
  Reads a mesh from file.
  """
  vertices = read_vertices(file)
  return read_hierarchy(file, vertices)


def read_hierarchy(file, vertices):
  # Create empty stack
  stack = []

  while True:
    line = file.readline()

    if line.startswith('t'):  # Current line represents a triangle
      indices = [int(s) for s in line.split(' ')[1:]]
      triangle_vertices = [vertices[i] for i in indices]
      triangle = Triangle(triangle_vertices, indices)
      stack.append(triangle)

    elif line.startswith('b'):  # Current line represents a box
      nchildren = int(line.split(' ')[1])

      # Take last nchildren items off the stack
      children = stack[-nchildren:]
      stack = stack[:-nchildren]

      stack.append(Box(children))

    elif line.startswith('end'):
      # Last line in file
      return stack[-1]


def read_vertices(file):
  """
  Reads vertices from file and returns them as an array.
  """
  # Read number of vertices
  nvertices = int(file.readline().split(' ')[0])

  # Read all vertices
  return [read_vertex(file) for _ in range(nvertices)]


def read_vertex(file):
  """
  Reads in a single line and interprets it as XYZ coordinates.
  """
  return tuple(float(c) for c in file.readline().split(' '))


class Triangle:
    def __init__(self, vertices, indices):
        self.vertices = vertices
        self.indices = indices

        self.xmax = max([vertex[0] for vertex in vertices])
        self.xmin = min([vertex[0] for vertex in vertices])
        self.ymax = max([vertex[1] for vertex in vertices])
        self.ymin = min([vertex[1] for vertex in vertices])
        self.zmax = max([vertex[2] for vertex in vertices])
        self.zmin = min([vertex[2] for vertex in vertices])


class Box:
    def __init__(self, children):
        self.children = children
        self.children_count = len(children)
        
        self.xmax = max([child.xmax for child in children])
        self.xmin = min([child.xmin for child in children])
        self.ymax = max([child.ymax for child in children])
        self.ymin = min([child.ymin for child in children])
        self.zmax = max([child.zmax for child in children])
        self.zmin = min([child.zmin for child in children])


class BVH:
    def __init__(self, file):
        self.stack = read_mesh(file)
        self.triangles = self.stack.children
        self.bvh = self.build_bvh(self.triangles)

    def bounding_box(self, triangles):
        return Box(triangles)

    def longest_axis(self, box):
        x = box.xmax - box.xmin
        y = box.ymax - box.ymin
        z = box.zmax - box.zmin

        return max(x, y, z)

    def build_bvh(self, triangles):
        if len(triangles) <= 3:
            return triangles
        else:
            box = self.bounding_box(triangles)
            axis = self.longest_axis(box)

            if axis == box.xmax - box.xmin:
                triangles = sorted(triangles, key=lambda triangle: triangle.xmax)
            elif axis == box.ymax - box.ymin:
                triangles = sorted(triangles, key=lambda triangle: triangle.ymax)
            else:
                triangles = sorted(triangles, key=lambda triangle: triangle.zmax)

            print("making bvh with " + str(len(triangles)) + " triangles")
            print("left " + str(len(triangles[:len(triangles) // 2])) + " triangles")
            print("right " + str(len(triangles[len(triangles) // 2:])) + " triangles")
            
            return self.build_bvh(triangles[:len(triangles) // 2]), self.build_bvh(triangles[len(triangles) // 2:])


def write_optimized_mesh(bvh, outputfile):
    """
    Writes optimized mesh to file.
    """
    write_first_part(outputfile)

    with open('temp.txt', 'w') as temp:
        write_temp(bvh, temp)
        print("temp written")

    write_bvh(outputfile)
    print("bvh written")

    outputfile.write("end")
    print("end written")
   

def write_first_part(outputfile):
    """
    Writes first part of the file.
    """
    print("writing first part")
    with open("C:/Users/erdem/Desktop/buddha.mesh", 'r') as file:
        line = file.readline()
        while not line.startswith('t'):
            outputfile.write(line)
            line = file.readline()
    print("first part written")
    

def write_temp(bvh, outputfile):
    """
    Writes bvh to file.
    """
    print("writing bvh")

    # write bvh to file in a way that it can be read by read_mesh function 
    if isinstance(bvh, Triangle):
        outputfile.write("t " + str(bvh.indices[0]) + " " + str(bvh.indices[1]) + " " + str(bvh.indices[2]) + "\n")
    else:
        outputfile.write("b " + str(len(bvh)) + "\n")
        for child in bvh:
            write_temp(child, outputfile)


def write_bvh(outputfile):
    # read from temp file, reverse the order of the lines and write to output file
    with open('temp.txt', 'r') as temp:
        lines = temp.readlines()
        for line in reversed(lines):
            outputfile.write(line)


with open("C:/Users/erdem/Desktop/buddha.mesh", 'r') as file:
    with open('optimized-buddha.mesh', 'w') as outputfile:
        bvh = BVH(file)
        write_optimized_mesh(bvh.bvh, outputfile)