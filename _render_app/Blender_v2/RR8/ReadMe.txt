
RoyalRender Blender connection
=============================


##########################################################################
### Description:

Blender support for the Royal Render render manager

The Blender Python script rrSubmit_Blender_1+.py read the current Blender Scene Rendersetting like : StartFrame, EndFrame
output Path and so on and create a RoyalRender conform formated XML file. Then the rr_submitter.sh from RoyalRender is started with
this XML as first set of paramters. The RoyalRender Submitter gets all needed information from this XML.


##########################################################################
### Installation:

Requirements:
    This connection requires Royal Render version 8.0.04.
    
Instructions:
 1) Please copy the files in the subfolders of /render_apps into the same folders in your RR installation.
 2) Add Blender to the render app list of the client. Either via rrConfig or via a client command job "Search for installed render apps" in rrControl.
 3) Add the submission plugin to Blender. Either via rrWorkstationInstaller or via a client command job "Install submission plugins" in rrControl.
 
 
 
##########################################################################
### Usage:

Use the "Submit Scene" button in Blender.



##########################################################################
### Authors:

Based on:    Felix Bucella, Patrik Gleich
First version: Friedrich Wessel (Callisto FX GmbH)
Updated by:  Holger Schoenberger (Binary Alchemy)