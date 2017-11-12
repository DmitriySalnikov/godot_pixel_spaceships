/* pixel_spaceships.h */
#pragma once
#ifndef DS_PIXEL_SPACESHIPS_H
#define DS_PIXEL_SPACESHIPS_H

#include "reference.h"
#include "scene/resources/texture.h"
#include "math/math_funcs.h"

typedef Vector<int> MaskData;
typedef Vector<Color> TextureColors;

//////////////////////////////////////////////////////////////////////////
// MASK
//////////////////////////////////////////////////////////////////////////
class PixelSpaceshipsMask : public Reference
{
	GDCLASS(PixelSpaceshipsMask, Reference);

private:
	MaskData data;
	Vector2 size;
	bool mirrorX;
	bool mirrorY;

protected:

	static void _bind_methods();

public:

	MaskData get_data();
	PixelSpaceshipsMask* set_data(MaskData, Vector2 size = Vector2());
	//WHITE = 0; RED = -1; GREEN = 1; BLUE = 2;!!!!!!!!!!
	PixelSpaceshipsMask* set_data_from_texture(Ref<Texture>);

	Vector2 get_size();
	PixelSpaceshipsMask* set_size(Vector2);

	bool get_mirror_x();
	PixelSpaceshipsMask* set_mirror_x(bool);

	bool get_mirror_y();
	PixelSpaceshipsMask* set_mirror_y(bool);

	PixelSpaceshipsMask();
	~PixelSpaceshipsMask();
};

//////////////////////////////////////////////////////////////////////////
// OPTIONS
//////////////////////////////////////////////////////////////////////////
class PixelSpaceshipsOptions : public Reference
{
	GDCLASS(PixelSpaceshipsOptions, Reference);
private:
	bool colored;
	float edge_brightnes;
	float color_variation;
	float brightness_noise;
	float saturation;
	float hue;

protected:

	static void _bind_methods();

public:

	bool get_colored();
	PixelSpaceshipsOptions* set_colored(bool);

	float get_edge_brightness();
	PixelSpaceshipsOptions* set_edge_brightness(float);

	float get_color_variation();
	PixelSpaceshipsOptions* set_color_variation(float);

	float get_brightness_noise();
	PixelSpaceshipsOptions* set_brightness_noise(float);

	float get_saturation();
	PixelSpaceshipsOptions* set_saturation(float);

	float get_hue();
	PixelSpaceshipsOptions* set_hue(float);

	void setup_options(bool _colored = true, float _edge_brightness = 0.15f, float _col_variations = 0.2f, float _brightness_noise = 0.8f, float _saturation = 0.7f);

	PixelSpaceshipsOptions();
	~PixelSpaceshipsOptions();
};

//////////////////////////////////////////////////////////////////////////
// PIXEL SPACESHIPS
//////////////////////////////////////////////////////////////////////////
class PixelSpaceships : public Reference
{
	GDCLASS(PixelSpaceships, Reference);

private:
	MaskData ResultData;
	TextureColors ResultColors;
	int Width;
	int Height;
	int HalfWidth;
	int HalfHeight;
	int Seed;
	Ref<PixelSpaceshipsMask> PSMask;
	Ref<PixelSpaceshipsOptions> PSOptions;

	int pos_to_idx(int, int, int);
	int get_data(MaskData, int, int, int);
	Color hsl2rgb(float, float, float,Color);
	float random();

	void generate_random_sample();
	void mirror_data();
	void generate_edges();
	void generate_colors();
	Ref<ImageTexture> make_texture();

protected:

	static void _bind_methods();

public:

	Ref<ImageTexture> generate_texture(Ref<PixelSpaceshipsMask>, Ref<PixelSpaceshipsOptions>, int = 0);
	void generate(Ref<PixelSpaceshipsMask>, Ref<PixelSpaceshipsOptions>, int = 0);

	Ref<PixelSpaceshipsMask> get_mask_object();
	Ref<PixelSpaceshipsOptions> get_options_object();

	Array get_mask_matrix();
	Array get_colors_matrix();

	PixelSpaceships();
	~PixelSpaceships();
};
#endif
