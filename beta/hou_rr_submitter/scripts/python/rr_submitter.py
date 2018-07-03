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

def getSceneWedges():
    """
    Returns a list of wedge nodes in the whole scene
    """
    rops = getRopNodesAtPath("/")
    wedges = []

    for node in rops:
        if node.type().name() == "wedge":
            wedges.append(node)
    
    return wedges

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

def expandPathParm(parm):
    """
    Returns processed and expanded path from input parameter
    """
    in_path = hou.pwd().path()
    hou.cd(parm.node().path())

    if len(parm.keyframes()) == 0:
        expr = parm.unexpandedString()
    else:
        expr = parm.eval()

    expr = expr.replace("$ACTIVETAKE", "<Channel>")
    expr = expr.replace("${ACTIVETAKE}", "<Channel>")

    path = hou.expandString(expr)

    hou.cd(in_path)
    return path

class GenericNode(object):
    """
    Abstract class for storing information about a node

    input node parameter is of hou.Node type
    """
    def __init__(self, node):
        self.node_object = node
        self.node_name = node.name()
        self.node_path = node.path()
        self.render_engine = self.getRenderEngine()
        self.render_engine_version = self.getRenderEngineVersion()
    
    def getRenderEngine(self):
        """
        Returns a string specifying render engine, supported nodes must be specified here, otherwise an exception will be raised
        """
        type_name = self.node_object.type().name()

        if type_name.lower() == "redshift_rop":
            return "redshift"
        elif type_name.lower() == "Redshift_Proxy_Output":
            return "redshift_proxy"
        elif type_name.lower() == "arnold":
            return "arnold"
        elif type_name.lower() == "arnold_denoiser":
            return "arnold_denoiser"
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
        if self.render_engine.startswith("arnold"):
            try:
                import arnold
                return arnold.AiGetVersionString()
            except ImportError:
                raise ImportError('Failed to import "arnold" python module, htoa is not available.')
        elif self.render_engine.startswith("redshift"):
            ver = hou.hscript('Redshift_version')[0]
            if not ver.startswith("Unknown"):
                return ver
            else:
                raise ImportError('Failed to run "Redshift_version" command, redshift is not available.')
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
        self.driver_path = self.node_object.parm("driver").evalAsNode().path()

        node_inputs = self.node_object.inputs()
        if len( node_inputs ) == 1:
            self.driver_path = node_inputs[0].path()
        
        self.driver = RenderNode( hou.node(self.driver_path) )
        self.wedge_parms = self.getWedgeParms()
    
    def getWedgeParms(self):
        """
        Returns a dictionary of wedge parameters in this structure:
        {
            "name 1"  : {
                "start" : 1,
                "end" : 10,
                "steps" : 1
            },
            "name 2" : {
                ...
            },
            ...
        }
        """
        multiparm = self.node_object.parm("wedgeparams")
        wedges_num = multiparm.eval()
        wedges = {}
        child_parms = multiparm.multiParmInstances()
        child_parms = [p.name() for p in child_parms]

        for i in xrange(1, wedges_num + 1):
            wedge_name = self.node_object.parm("name{num}".format(num = i)).eval()
            wedge_start = self.node_object.parm("range{num}x".format(num = i)).eval()
            wedge_end = self.node_object.parm("range{num}y".format(num = i)).eval()
            wedge_steps = self.node_object.parm("steps{num}".format(num = i)).eval()

            wedges[wedge_name] = {
                "start" : wedge_start,
                "end" : wedge_end,
                "steps" : wedge_steps
            }
        
        return wedges

class RenderNode(GenericNode):
    """
    Class representing remder node
    """
    def __init__(self, node):
        super(RenderNode, self).__init__(node)
        self.parms = RenderParms(self)

class RenderParms(object):
    """
    Class for storing information about parameters from ROP node
    """
    def __init__(self, generic_node):
        self.generic_node_object = generic_node
        self.node_object = generic_node.node_object
        self.cam_path = self.getCameraPath()
        self.cam_stereo = self.isCamStereo()
        self.start, self.end, self.steps = self.getFrameRange()
        self.output_path = self.getOutputPath()
        self.aovs = self.getAOVs()

    def getCameraPath(self):
        """
        Returns string containing path to camera
        """
        renderer = self.generic_node_object.render_engine
        if renderer == "arnold" or renderer == "mantra" or renderer == "opengl":
            return self.node_object.parm("camera").evalAsNode().path()
        elif renderer == "redshift":
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
    
    def getFrameRange(self):
        """
        Returns a touple of (start, end, steps) frame range in a node
        """
        start = self.node_object.parm("f1").eval()
        end = self.node_object.parm("f2").eval()
        steps = self.node_object.parm("f3").eval()

        return (start, end, steps)
    
    def getOutputPath(self):
        """
        Returns expanded string containing path to the output picture
        """
        renderer = self.generic_node_object.render_engine
        parm = None

        if renderer == "arnold":
            parm = "ar_picture"
        elif renderer == "arnold_denoiser":
            parm = "output"
        elif renderer == "redshift":
            parm = "RS_outputFileNamePrefix"
        elif renderer == "redshift_proxy":
            parm = "RS_archive_file"
        elif renderer == "mantra":
            parm = "vm_picture"
        elif renderer == "geometry":
            parm = "sopoutput"
        elif renderer == "alembic":
            parm = "filename"
        elif renderer == "opengl":
            parm = "picture"
        
        if parm:
            parm_obj = self.node_object.parm(parm)
            path = expandPathParm(parm_obj)
            return path
        else:
            return None
    
    def getAOVs(self):
        """
        Returns a dict of aovs in this form { "name" : "path" }
        """
        renderer = self.generic_node_object.render_engine
        if renderer == "arnold":
            multiparm_name = "ar_aovs"
            parm_aov_enable = "ar_enable_aov{num}"
            parm_aov_name = "ar_aov_label{num}"
            parm_aov_file = "ar_aov_separate_file{num}"
            parm_aov_use_file = "ar_aov_separate{num}"
        elif renderer == "mantra":
            multiparm_name = "vm_numaux"
            parm_aov_enable = "vm_disable_plane{num}" # inverted
            parm_aov_name = "vm_variable_plane{num}"
            parm_aov_file = "vm_filename_plane{num}"
            parm_aov_use_file = "vm_usefile_plane{num}"
        elif renderer == "redshift":
            multiparm_name = "RS_aov"
            parm_aov_enable = "RS_aovEnable_{num}"
            parm_aov_name = "RS_aovSuffix_{num}"
            parm_aov_file = "RS_aovCustomPrefix_{num}"
            parm_aov_use_file = 1
        
        multiparm = self.node_object.parm(multiparm_name)
        aovs_num = multiparm.eval()
        aovs = {}
        child_parms = multiparm.multiParmInstances()
        child_parms = [p.name() for p in child_parms]

        for i in xrange(1, aovs_num + 1):
            aov_enable = self.node_object.parm( parm_aov_enable.format(num = i) ).eval()
            if renderer == "mantra":
                aov_enable = 1 - aov_enable
            
            if aov_enable == 1:
                aov_name = self.node_object.parm( parm_aov_name.format(num = i) ).eval()
                aov_file = expandPathParm( self.node_object.parm( parm_aov_file.format(num = i) ) )
                
                if parm_aov_use_file == 1:
                    aov_use_file = 1
                else:
                    aov_use_file = self.node_object.parm( parm_aov_use_file.format(num = i) ).eval()

                if aov_use_file == 1 and aov_file != "":
                    aovs[aov_name] = aov_file
                else:
                    aovs[aov_name] = self.output_path
        
        return aovs