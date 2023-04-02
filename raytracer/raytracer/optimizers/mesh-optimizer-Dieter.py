#import read_mesh as read_mesh   

import sys
import time
sys.setrecursionlimit(50000)

def read_mesh(filename):

    vertices = []
    triangles = []

    with open(filename) as f:
        lines = f.readlines()

    amount_of_vertices = int(lines[0].split()[0])

    print("amount of lines: " + str(amount_of_vertices))

    for i in range(1,amount_of_vertices+1):
        try:
            x,y,z = lines[i].split(" ")
            vertices.append([float(x), float(y), float(z)])
        except:
            print("error on line: " + str(i))
            print(lines[i])

    for i in range(amount_of_vertices+1, len(lines)-2):
        try:
            t, v1, v2, v3 = lines[i].split(" ")
            triangles.append([int(v1), int(v2), int(v3)])
        except:
            print("error on line: " + str(i))
            print(lines[i])
        
    b,box = lines[-2].split(" ")

    return vertices, triangles, box

class BoundingVolumeHierarchy:
    def __init__(self, filename):
        self.vertices, self.triangles, self.box = read_mesh(filename)
        self.bvh = self.build_bvh2(self.triangles)

    def get_longest_axis(self, bounding_box):
        # Calculate the range (max value - min value) along each axis
        x_range = bounding_box[3] - bounding_box[0]
        y_range = bounding_box[4] - bounding_box[1]
        z_range = bounding_box[5] - bounding_box[2]

        # Return the index of the axis with the largest range
        if x_range > y_range and x_range > z_range:
            return 0
        elif y_range > x_range and y_range > z_range:
            return 1
        else:
            return 2

    def get_bounding_box(self, triangles):
        # Initialize the bounding box with the first vertex of the first triangle
        v1 = self.vertices[triangles[0][0]]
        min_x, min_y, min_z = v1[0], v1[1], v1[2]
        max_x, max_y, max_z = v1[0], v1[1], v1[2]

        # Iterate through all the triangles and vertices, updating the bounding box as needed
        for triangle in triangles:
            for vertex in triangle:
                v = self.vertices[vertex]
                min_x = min(min_x, v[0])
                min_y = min(min_y, v[1])
                min_z = min(min_z, v[2])
                max_x = max(max_x, v[0])
                max_y = max(max_y, v[1])
                max_z = max(max_z, v[2])

        # Return the bounding box as a list
        return [min_x, min_y, min_z, max_x, max_y, max_z]



    def build_bvh2(self,triangles):
        #if you have 3 triangles or less, return the triangles
        if len(triangles) <= 512:
            return triangles

        else:
            #get the bounding box of the triangles and get the longest axis
            bounding_box = self.get_bounding_box(triangles)
            longest_axis = self.get_longest_axis(bounding_box)

            #order the triangles by the longest axis
            if longest_axis == 0:
                triangles.sort(key=lambda x: self.vertices[x[0]][0])
            elif longest_axis == 1:
                triangles.sort(key=lambda x: self.vertices[x[0]][1])
            elif longest_axis == 2:
                triangles.sort(key=lambda x: self.vertices[x[0]][2])

            #split the triangles into two groups
            triangles_left = triangles[:len(triangles)//2]
            triangles_right = triangles[len(triangles)//2:]
            

            #print the length of the left and right triangles
            print("left: " + str(len(triangles_left)))
            print("right: " + str(len(triangles_right)))
            
            #recursively build the BVH for the two groups of triangles
            left_bvh = self.build_bvh2(triangles_left)
            right_bvh = self.build_bvh2(triangles_right)

            #return the BVH for this node
            return [left_bvh, right_bvh]

    def check_bvh_structure(self, bvh):
        # If the input node is a leaf node, return 0
        if isinstance(bvh, list) and len(bvh) == 3:
            return 0
        # If the input node has two children (internal node),
        # recursively check the left and right children
        elif isinstance(bvh, list) and len(bvh) == 2:
            left_depth = self.check_bvh_structure(bvh[0])
            right_depth = self.check_bvh_structure(bvh[1])
            return max(left_depth, right_depth) + 1
        # If the input node has a different structure, return -1
        else:
            return -1


    def write_bvh(self, bvh, file):
    # If the input node is a leaf node, write the triangles to the file
        if isinstance(bvh, list) and len(bvh) == 3 and isinstance(bvh[0], int):
            file.write('t ' + str(bvh[0]) + ' ' + str(bvh[1]) + ' ' + str(bvh[2]) + '\n')
        # If the input node is an internal node, recursively write the left and right children
        elif isinstance(bvh, list) and (len(bvh) == 2):
            file.write('b ' + str(len(bvh))+ '\n')
            self.write_bvh(bvh[0], file)
            self.write_bvh(bvh[1], file)

    
        elif isinstance(bvh, list) and (len(bvh) == 3):
            file.write('b ' + str(len(bvh))+ '\n')
            self.write_bvh(bvh[0], file)
            self.write_bvh(bvh[1], file)
            self.write_bvh(bvh[2], file)
        # If the input node has a different structure, raise an exception
        else:
            print(bvh)
            raise Exception('Invalid BVH structure')

    
    def save_bvh(self, filename):
        # Open the file in write mode
        with open(filename, 'w') as file:
            # Write the BVH tree to the file
            self.write_bvh(self.bvh, file)
            
def main():
    bvh = BoundingVolumeHierarchy("buddha.mesh")
    check = bvh.check_bvh_structure(bvh.bvh)
    print("BVH structure is correct: " + str(check >= 0))
    print("BVH depth: " + str(check))
    bvh.save_bvh("buddha-optimized.mesh")

    #read the bunny-optmized.bvh file and put it into a list split on new lines
    with open("buddha-optimized.mesh","r") as f:
        bvh_list = f.read().splitlines()


    #read bunny.mesh file and copy all the lines starting from the first line untill a line that starts with "t x y z" where x y z are 3 integers
    with open("buddha.mesh","r") as f:
        mesh_start = f.readlines()
        for i in range(len(mesh_start)):
            if mesh_start[i].startswith("t"):
                mesh_start = mesh_start[:i]
                break


    #write the bvh list to a new file
    with open("buddha-optimized2.bvh", "w") as f:
        #write mesh_start
        f.write(''.join(mesh_start))
        #write bvh_list
        f.write('\n'.join(bvh_list[::-1]) + '\n')
        f.write('end')
            


main()