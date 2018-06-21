import hou

def isRenderable(node):
    """
    Checks if a node is renderable and is not rop network itself
    """
    return isinstance(node, hou.RopNode) and node.type().name() != "ropnet"

def getRopNodesAtPath(root_path):
    """
    Returns child renderable nodes found at specified location

    Returns a list of hou.Node objects
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
        return None

def getSceneRopNodes():
    """
    If a node is selected, finds all renderable nodes in it, if not, then finds all renderable nodes in the scene
    
    Returns a list of hou.Node objects
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
                found_nodes = getRopNodesAtPath("/")
                if found_nodes:
                    for node in found_nodes:
                        out_nodes.append(node)
    # if user did not select anything
    else:
        found_nodes = getRopNodesAtPath("/")
        if found_nodes:
            out_nodes = found_nodes
        else:
            return
    
    return out_nodes

def getSceneTakes():
    """
    Rutrns a dict containing takes information
    """
    takes = {}
    takes["current_take"] = hou.takes.currentTake().name()
    takes["all_takes"] = []

    for take in hou.takes.takes():
        takes["all_takes"].append( take.name() )
    
    return takes

class GenericNode(object):
    """
    Abstract class for storing information about a node
    """
    def __init__(self, node):
        self.node_object = node
        self.node_name = node.name()
        self.node_path = node.path()
        self.render_engine = self.getRenderEngine()
        self.render_engine_version = self.getRenderEngineVersion()
        self.parms = NodeParms(self)
    
    def getRenderEngine(self):
        """
        Returns a string specifying render engine, supported nodes must be specified here, otherwise an exception will be raised
        """
        type_name = self.node_object.type().name()

        if type_name.lower().startswith("redshift"):
            return "redshift"
        elif type_name.lower().startswith("arnold"):
            return "arnold"
        elif type_name.lower() == "ifd":
            return "mantra"
        elif type_name.lower() == "geometry":
            return "geometry"
        elif type_name.lower() == "alembic":
            return "alembic"
        elif type_name.lower() == "fetch":
            return "fetch"
        elif type_name.lower() == "merge":
            return "merge"
        elif type_name.lower() == "wedge":
            return "wedge"
        elif type_name.lower() == "opengl":
            return "opengl"
        else:
            raise NameError('Node "{}" of type "{}" is not supported'.format(self.node_object.name(), type_name))
    
    def getRenderEngineVersion(self):
        """
        Returns a string specifying render engine version, or Houdini version if renderer is houdini/mantra
        """
        if self.render_engine == "arnold":
            try:
                import arnold
                return arnold.AiGetVersionString()
            except ImportError:
                raise ImportError('Failed to import "arnold" python module, htoa is not available.')
        elif self.render_engine == "redshift":
            return hou.hscript('Redshift_version')
        else:
            return hou.applicationVersionString()

class WedgeNode(GenericNode):
    """
    Class representing wedge node

    self.wedge_method can be either "channel" or "take"
    """
    def __init__(self, node):
        super(WedgeNode, self).__init__(node)
        self.prefix = self.node_object.parm("prefix").eval()
        self.wedge_method = self.node_object.parm("wedgemethod").evalAsString()
        self.driver_node_path = self.node_object.parm("driver").evalAsNode().path()

        node_inputs = self.node_object.inputs()
        if len( node_inputs ) == 1:
            self.driver_node_path = node_inputs[0].path()

class RenderNode(GenericNode):
    """
    Class representing remder node
    """
    def __init__(self, node):
        super(RenderNode, self).__init__(node)

class NodeParms(object):
    """
    Class for storing information about parameters from ROP node
    """
    def __init__(self, generic_node):
        self.generic_node_object = generic_node
        self.node_object = generic_node.node_object
        self.cam_path = self.getCameraPath()
        self.cam_stereo = self.isCamStereo()
        #self.start
        #self.end
        #self.steps
        #self.output_path
        #self.aovs
        pass

    def getCameraPath(self):
        """
        Returns string containing path to camera
        """
        if self.generic_node_object.render_engine == "arnold" or self.generic_node_object.render_engine == "mantra" or self.generic_node_object.render_engine == "opengl":
            return self.node_object.parm("camera").evalAsNode().path()
        elif self.generic_node_object.render_engine == "redshift":
            return self.node_object.parm("RS_renderCamera").evalAsNode().path()
        else:
            return None
    
    def isCamStereo(self):
        """
        Returns boolean if camera is stereo, or None if there is no camera
        """
        if self.cam_path:
            cam_node = hou.node(self.cam_path)
            if cam_node.type().name().lower().startswith("stereo"):
                return True
            else:
                return False
        else:
            return None