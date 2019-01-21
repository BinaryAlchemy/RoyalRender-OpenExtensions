#python
# -*- coding: cp1252 -*-
######################################################################
#
# Royal Render Settings script for Blender
# Author:  Royal Render, Paolo Acampora
# 
######################################################################

import bpy
import addon_utils

print("RR - enable cycles GPU at startup")

cprefs = bpy.context.user_preferences.addons['cycles'].preferences
cprefs.compute_device_type = 'CUDA'

# Attempt to set GPU device types if available
for compute_device_type in ('CUDA', 'OPENCL', 'NONE'):
    try:
        cprefs.compute_device_type = compute_device_type
        break
    except TypeError:
        pass

# Enable all CPU and GPU devices
for device in cprefs.devices:
    device.use = True
