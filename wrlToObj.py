import re
import sys


def wrl_to_obj(wrl_file_path, obj_file_path):
    # Read the .wrl file
    with open(wrl_file_path, 'r') as file:
        lines = file.readlines()

    # Containers for vertices and lines
    vertices = []
    edges = []

    # Parse the .wrl file
    for line in lines:
        if line.strip().startswith('point'):
            # Extracting vertices
            vertex_lines = line.strip('point [\n').strip(']\n').split(',\n')
            for vertex in vertex_lines:
                if vertex.strip():
                    vertices.append(vertex.strip())
        elif line.strip().startswith('coordIndex'):
            # Extracting lines
            edge_lines = line.strip(
                'coordIndex [\n').strip(']\n').split(', -1,\n')
            for edge in edge_lines:
                if edge.strip():
                    edges.append([int(e.strip()) for e in edge.split(',')])

    # Write to the .obj file
    with open(obj_file_path, 'w') as file:
        for vertex in vertices:
            file.write('v ' + vertex + '\n')
        for edge in edges:
            for i in range(len(edge) - 1):
                # OBJ files are 1-indexed
                file.write('l {} {}\n'.format(edge[i] + 1, edge[i + 1] + 1))


# If there's an argument provided, use that as the input filename
if __name__ == "__main__":
    if len(sys.argv) > 1:
        wrl_filename = sys.argv[1]
        obj_filename = wrl_filename.rsplit('.', 1)[0] + '.obj'
        wrl_to_obj(wrl_filename, obj_filename)
