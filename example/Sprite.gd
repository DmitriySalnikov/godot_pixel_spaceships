extends Node2D

onready var PS = PixelSpaceships.new()

onready var m = PixelSpaceshipsMask.new()
onready var o = PixelSpaceshipsOptions.new()

func _ready():
	randomize()
	$interface/Button.connect("pressed",self,"regen")
	
	var _size = Vector2(32,16)
	_size = Vector2(8,4)
	
	var _v_size = get_viewport_rect().size
	for x in range(_size.x):
		for y in range(_size.y):
			var sprite = Sprite.new()
			sprite.scale = Vector2(5,5)
			sprite.position = Vector2(_v_size.x/_size.x*x,_v_size.y/_size.y*y)
			sprite.centered = false
			add_child(sprite)
	
	m.set_mirror_x(true)
	m.set_data([
	0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 1,
	0, 0, 0, 0, 1,-1,
	0, 0, 0, 1, 1,-1,
	0, 0, 0, 1, 1,-1,
	0, 0, 1, 1, 1,-1,
	0, 0, 1, 1, 2, 2,
	0, 0, 1, 1, 2, 2,
	0, 0, 1, 1, 2, 2,
	0, 0, 1, 1, 1,-1,
	0, 0, 0, 1, 1, 1,
	0, 0, 0, 0, 0, 0
	],Vector2(6,12))
	
	#m.set_data_from_texture(load("res://mask.png"))
	m.set_data_from_texture(load("res://mask_tree.png"))
	regen()

func regen():
	var time = OS.get_ticks_msec()
	o.setup_options($interface/col.pressed,$interface/edge.value,$interface/var.value,$interface/bright.value,$interface/sat.value)
	#o.set_hue(0.4)
	
	for s in get_children():
		if s is Sprite:
			s.scale = Vector2($interface/scale.value,$interface/scale.value)
			s.texture = PS.generate_texture(m,o)
	
	print("Time: ",OS.get_ticks_msec()-time)