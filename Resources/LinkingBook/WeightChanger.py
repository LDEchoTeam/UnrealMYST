import bpy

o = bpy.context.active_object

bpy.ops.object.mode_set(mode="OBJECT")

vs = [v for v in o.data.vertices if v.select]

for v in vs:
	for g in v.groups:
		if g.group == o.vertex_groups['Back'].index:
			o.vertex_groups['Back'].add([v.index], g.weight + 0.0025, 'REPLACE')
		elif g.group == o.vertex_groups['Page'].index:
			o.vertex_groups['Page'].add([v.index], g.weight - 0.00125, 'REPLACE')

bpy.ops.object.mode_set(mode="EDIT")