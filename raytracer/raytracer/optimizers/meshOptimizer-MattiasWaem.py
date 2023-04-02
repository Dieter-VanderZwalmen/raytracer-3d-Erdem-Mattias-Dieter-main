#increase the recursion limit
# import sys
# sys.setrecursionlimit(100000)

def write_optimization_to_file(inputfile, outputfile):
    """
    Writes the optimized mesh to a file.
    """
    mesh = str(optimizeMesh(open(inputfile))).replace('[', '').replace(',', '')
    print(mesh)
    stringOutputfile = str(outputfile)
    with open(inputfile, 'r') as f:
        with open(stringOutputfile, 'w') as outputfile:
            first_line = f.readline()
            outputfile.write(first_line)
            nvertices = int(first_line.split(' ')[0])
            for i in range(1, nvertices + 1):
                new_line = f.readline()
                outputfile.write(new_line)
    with open(stringOutputfile, 'a') as outputfile:
            outputfile.write('t ')
            stackTriangles = 1
            list_mesh = mesh.split(' ')
            for item in list_mesh:
                aantal = item.count(']')
                if item == list_mesh[-1]:
                    outputfile.write(item.rstrip(']') + '\n')
                    outputfile.write('b ' + str(stackTriangles) + '\n')
                    while aantal != 2:
                        outputfile.write('b ' + str(2) + '\n')
                        aantal -= 1
                    outputfile.write('end')
                elif aantal == 0:
                    outputfile.write(item + ' ')
                elif aantal == 1:
                    outputfile.write(item.rstrip(']') + '\n' + 't ')
                    stackTriangles += 1
                elif aantal == 2:
                    outputfile.write(item.rstrip(']') + '\n' + 'b ' + str(stackTriangles) + '\n' + 't ')
                    stackTriangles = 1
                elif aantal >= 3:
                    outputfile.write(item.rstrip(']') + '\n')
                    outputfile.write('b ' + str(stackTriangles) + '\n')
                    while aantal != 2:
                        outputfile.write('b ' + str(2) + '\n')
                        aantal -= 1
                    stackTriangles = 1
                    outputfile.write('t ')
            return "Done!"

def optimizeMesh(file):
    """
    Optimizes a mesh by merging vertices and removing triangles.
    """
    first_line = file.readline()
    nvertices = int(first_line.split(' ')[0])
    dictornary = {i: list(float(c) for c in file.readline().split(' ')) for i in range(0, nvertices)}
    all_vertices = list_all_vertices(file)
    orderedListOfVertices = rearrangeVertices(dictornary, all_vertices)
    return orderedListOfVertices

    
def rearrangeVertices(dictornary, all_vertices):

    if len(all_vertices) <= 5:
        return all_vertices
    else:
        list_of_all_x = []
        for item in all_vertices:
            list_of_all_x.append(dictornary.get(item[0])[0])
        list_of_all_y = []
        for item in all_vertices:
            list_of_all_y.append(dictornary.get(item[1])[1])
        list_of_all_z = []
        for item in all_vertices:
            list_of_all_z.append(dictornary.get(item[2])[2])

        smallest_x = min(list_of_all_x)
        biggest_x = max(list_of_all_x)
        smallest_y = min(list_of_all_y)
        biggest_y = max(list_of_all_y)
        smallest_z = min(list_of_all_z)
        biggest_z = max(list_of_all_z)
        biggest_difference = max(biggest_x - smallest_x, biggest_y - smallest_y, biggest_z - smallest_z)

        if biggest_x - smallest_x == biggest_difference:
            middlepoint = (biggest_x + smallest_x) / 2
            list_of_biggest_x = []
            list_of_smallest_x = []
            for item in all_vertices:
                if dictornary.get(item[0])[0] >= middlepoint:
                    list_of_biggest_x.append(item)
                else:
                    list_of_smallest_x.append(item)
            return [rearrangeVertices(dictornary, list_of_biggest_x)] + [rearrangeVertices(dictornary, list_of_smallest_x)]   
        elif biggest_y - smallest_y == biggest_difference:
            middlepoint = (biggest_y + smallest_y) / 2
            list_of_biggest_y = []
            list_of_smallest_y = []
            for item in all_vertices:
                if dictornary.get(item[1])[1] >= middlepoint:
                    list_of_biggest_y.append(item)
                else:
                    list_of_smallest_y.append(item)
            return [rearrangeVertices(dictornary, list_of_biggest_y)] + [rearrangeVertices(dictornary, list_of_smallest_y)]
        elif biggest_z - smallest_z == biggest_difference:
            middlepoint = (biggest_z + smallest_z) / 2
            list_of_biggest_z = []
            list_of_smallest_z = []
            for item in all_vertices:
                if dictornary.get(item[2])[2] >= middlepoint:
                    list_of_biggest_z.append(item)
                else:
                    list_of_smallest_z.append(item)
            return [rearrangeVertices(dictornary, list_of_biggest_z)] + [rearrangeVertices(dictornary, list_of_smallest_z)]

def middlePointOfTriangle(p1, p2, p3):
    x = (p1[0] + p2[0] + p3[0]) / 3
    y = (p1[1] + p2[1] + p3[1]) / 3
    z = (p1[2] + p2[2] + p3[2]) / 3
    return (x, y, z)

def list_all_vertices(file):
    list_of_vertices = []
    while True:
        line = file.readline()
        if line.startswith('t'):
            indices = [int(s) for s in line.split(' ')[1:]]
            list_of_vertices.append(indices)
        elif line.startswith('end'):
            return list_of_vertices

write_optimization_to_file('bunny.mesh', 'bunny_optimized.mesh')


        
