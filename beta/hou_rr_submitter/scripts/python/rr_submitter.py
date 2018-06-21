import hou

def isRenderable(node):
    """
    Checks if a node is renderable and is not rop network itself
    """
    return isinstance(node, hou.RopNode) and node.type().name() != "ropnet"

def getRopNodesAtPath(root_path):
    """
    Returns child renderable nodes found at root_path location
    """
    node = hou.node(root_path)
    if not node:
        print('Node "{}" does not exist'.format(root_path))
        return None

    node_children = node.allSubChildren()
    node_list = []

    # check if node is renderable
    if isRenderable(node):
        node_list.append(node)
        return node_list
    # if not, then looks into its children
    elif len(node_children) > 0:
        for n in node_children:
            if isRenderable(n):
                node_list.append(n)

    if len(node_list) > 0:
        return node_list
    else:
        print("No render nodes were found.\n")        
        return None

def getSceneRopNodes():
    """
    If a node is selected, finds all renderable nodes in it, if not, then finds all renderable nodes in the scene
    """
    out_nodes = []

    selection = hou.selectedNodes()

    # if user has selected some nodes
    if bool( selection ):
        for selected in selection:
            found_nodes = getRopNodesAtPath( selected.path() )
            if found_nodes:
                for node in found_nodes:
                    out_nodes.append(node)
            else:
                return
    # if user did not select anything
    else:
        found_nodes = getRopNodesAtPath("/")
        if found_nodes:
            out_nodes = found_nodes
        else:
            return
    
    return out_nodes