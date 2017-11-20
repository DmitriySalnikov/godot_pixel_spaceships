# godot_pixel_spaceships
The implementation of Pixel Spaceships for Godot Engine as a module.

Based on https://github.com/zfedoran/pixel-sprite-generator

This module was developed for Godot 3.0

<a href="https://github.com/DmitriySalnikov/godot_pixel_spaceships/blob/master/pic_0.png"><img src="https://github.com/DmitriySalnikov/godot_pixel_spaceships/blob/master/pic_0.png" width="50%" ></a><a href="https://github.com/DmitriySalnikov/godot_pixel_spaceships/blob/master/pic_1.png"><img src="https://github.com/DmitriySalnikov/godot_pixel_spaceships/blob/master/pic_1.png" width="50%" ></a>
<a href="https://github.com/DmitriySalnikov/godot_pixel_spaceships/blob/master/pic_2.png"><img src="https://github.com/DmitriySalnikov/godot_pixel_spaceships/blob/master/pic_2.png" width="50%" ></a>

## Installation

To install, clone latest version of Godot Engine and drop the `pixel_spaceships` directory into the `godot/modules` directory and compile it.

## Example

```gdscript
extends Node2D

onready var PS = PixelSpaceships.new()
onready var m = PixelSpaceshipsMask.new()
onready var o = PixelSpaceshipsOptions.new()

func _ready():
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
	  
  $Sprite.texture = PS.generate_texture(m,o)
```
Options can be set like this:
```gdscript
o.setup_options(true, 0.4, 0.5, 0.6, 0.3)
```
Or like this:
```gdscript
o.set_colored(true).set_hue(0.334).set_saturation(0.7)
```
Setting the mask using the texture:
```gdscript
m.set_data_from_texture(load("res://mask.png"))
```
Mask texture must have 4 colors!

White(255,255,255) = 0 = Always empty

Red(255,0,0) = -1 = Always solid

Green(0,255,0) = 1 = "Body" empty/Avoid by seed

Blue(0,0,255) = 2 = "Cockpit" empty/Avoid by seed

Like this:

<a href="https://github.com/DmitriySalnikov/godot_pixel_spaceships/blob/master/example/mask.png"><img src="https://github.com/DmitriySalnikov/godot_pixel_spaceships/blob/master/example/mask.png" width="128" ></a>

## Functions:
```
PixelSpaceshipsMask:
  PoolIntArray get_data()
    #Return array with mask
  Vector2 get_size()
    #Return size of mask
  bool get_mirror_x()
  bool get_mirror_y()
  
  PixelSpaceshipsMask set_data( PoolIntArray data_array, Vector2 size )
  PixelSpaceshipsMask set_data_from_texture( Texture texture )
  PixelSpaceshipsMask set_mirror_x( bool is_mirror_x )
  PixelSpaceshipsMask set_mirror_y( bool is_mirror_y )
  PixelSpaceshipsMask set_size( Vector2 size )
  
PixelSpaceshipsOptions:
  bool get_colored()
  float get_brightness_noise()
  float get_color_variation()
  float get_edge_brightness()
  float get_hue()
  float get_saturation()
  
  PixelSpaceshipsOptions set_colored( bool is_colored )
  PixelSpaceshipsOptions set_brightness_noise( float brightness_noise )
  PixelSpaceshipsOptions set_color_variation( float color_variation )
  PixelSpaceshipsOptions set_edge_brightness( float edge_brightness )
  PixelSpaceshipsOptions set_hue( float hue )
  PixelSpaceshipsOptions set_saturation( float saturation )
  
  void setup_options( bool is_colored, float edge_brightness, float color_variations, float brightness_noise, float saturation )
  
PixelSpaceships:
  void generate( PixelSpaceshipsMask m, PixelSpaceshipsOptions o, int seed )
    #Only generate mask
  ImageTexture generate_texture( PixelSpaceshipsMask m, PixelSpaceshipsOptions o, int seed)
    #Generate ImageTexture object from given info
  Array get_colors_matrix()
  Array get_mask_matrix()
  PixelSpaceshipsMask get_mask_object()
  PixelSpaceshipsOptions get_options_object()
```

## Algorithm

The sprites are generated by using a two dimensional mask. The values in the mask are then randomized and mirrored.

<a href="http://web.archive.org/web/20080228054410/http://www.davebollinger.com/works/pixelspaceships/"><img src="https://github.com/zfedoran/pixel-sprite-generator/raw/master/doc/algorithm-1.png"></a>

The algorithm is explained in more detail on [Dave Bollinger's](http://web.archive.org/web/20080228054410/http://www.davebollinger.com/works/pixelspaceships/) website.

<a href="http://web.archive.org/web/20080228054410/http://www.davebollinger.com/works/pixelspaceships/"><img src="https://github.com/zfedoran/pixel-sprite-generator/raw/master/doc/algorithm-0.png"></a>
