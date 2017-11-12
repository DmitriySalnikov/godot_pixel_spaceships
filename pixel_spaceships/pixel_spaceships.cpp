/* pixel_spaceships.cpp */

#include "pixel_spaceships.h"

//////////////////////////////////////////////////////////////////////////
// MASK
//////////////////////////////////////////////////////////////////////////
MaskData PixelSpaceshipsMask::get_data()
{
	return data;
}

PixelSpaceshipsMask* PixelSpaceshipsMask::set_data(MaskData _data, Vector2 _size)
{
	data = _data;
	if (_size != Vector2())
		size = _size;
	return this;
}

PixelSpaceshipsMask* PixelSpaceshipsMask::set_data_from_texture(Ref<Texture> tex)
{
	Ref<Image> img = tex->get_data();
	int w, h;
	size.width = w = tex->get_size().width;
	size.height = h = tex->get_size().height;

	MaskData tmp_data;
	tmp_data.resize(w*h);

	const auto white = Color(1, 1, 1, 1).to_rgba32();
	const auto red = Color(1, 0, 0, 1).to_rgba32();
	const auto green = Color(0, 1, 0, 1).to_rgba32();
	const auto blue = Color(0, 0, 1, 1).to_rgba32();

	img->lock();
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			Color col = img->get_pixel(i, j);

			int idx = j*w + i;
			auto col_int = col.to_rgba32();

			if (col_int == white)
			{
				tmp_data[idx] = 0;
			}
			else if (col_int == red)
			{
				tmp_data[idx] = -1;
			}
			else if (col_int == green)
			{
				tmp_data[idx] = 1;
			}
			else if (col_int == blue)
			{
				tmp_data[idx] = 2;
			}
		}
	}
	img->unlock();

	data = tmp_data;
	return this;
}

Vector2 PixelSpaceshipsMask::get_size()
{
	return size;
}

PixelSpaceshipsMask* PixelSpaceshipsMask::set_size(Vector2 _size)
{
	size = _size;

	return this;
}

bool PixelSpaceshipsMask::get_mirror_x()
{
	return mirrorX;
}

PixelSpaceshipsMask* PixelSpaceshipsMask::set_mirror_x(bool _mirrorX)
{
	mirrorX = _mirrorX;
	return this;
}

bool PixelSpaceshipsMask::get_mirror_y()
{
	return mirrorY;
}

PixelSpaceshipsMask* PixelSpaceshipsMask::set_mirror_y(bool _mirrorY)
{
	mirrorY = _mirrorY;
	return this;
}

void PixelSpaceshipsMask::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_data"), &PixelSpaceshipsMask::get_data);
	ClassDB::bind_method(D_METHOD("set_data", "data_array", "size"), &PixelSpaceshipsMask::set_data, DEFVAL(Vector2()));
	ClassDB::bind_method(D_METHOD("set_data_from_texture", "texture"), &PixelSpaceshipsMask::set_data_from_texture);

	ClassDB::bind_method(D_METHOD("get_size"), &PixelSpaceshipsMask::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &PixelSpaceshipsMask::set_size);

	ClassDB::bind_method(D_METHOD("get_mirror_x"), &PixelSpaceshipsMask::get_mirror_x);
	ClassDB::bind_method(D_METHOD("set_mirror_x", "is_mirror_x"), &PixelSpaceshipsMask::set_mirror_x);

	ClassDB::bind_method(D_METHOD("get_mirror_y"), &PixelSpaceshipsMask::get_mirror_y);
	ClassDB::bind_method(D_METHOD("set_mirror_y", "is_mirror_y"), &PixelSpaceshipsMask::set_mirror_y);


}

PixelSpaceshipsMask::PixelSpaceshipsMask()
{
	size = Vector2();
	data = MaskData();
	mirrorX = false;
	mirrorY = false;
}



PixelSpaceshipsMask::~PixelSpaceshipsMask()
{

}


//////////////////////////////////////////////////////////////////////////
// OPTIONS
//////////////////////////////////////////////////////////////////////////
bool PixelSpaceshipsOptions::get_colored()
{
	return colored;
}

PixelSpaceshipsOptions* PixelSpaceshipsOptions::set_colored(bool _colored)
{
	colored = _colored;
	return this;
}

float PixelSpaceshipsOptions::get_edge_brightness()
{
	return edge_brightnes;
}

PixelSpaceshipsOptions* PixelSpaceshipsOptions::set_edge_brightness(float _brightnes)
{
	edge_brightnes = _brightnes;
	if (edge_brightnes < 0)
		edge_brightnes = 0;
	if (edge_brightnes > 1)
		edge_brightnes = 1;
	return this;
}

float PixelSpaceshipsOptions::get_color_variation()
{
	return color_variation;
}

PixelSpaceshipsOptions* PixelSpaceshipsOptions::set_color_variation(float _col)
{
	color_variation = _col;
	if (color_variation < 0)
		color_variation = 0;
	if (color_variation > 1)
		color_variation = 1;
	return this;
}

float PixelSpaceshipsOptions::get_brightness_noise()
{
	return brightness_noise;
}

PixelSpaceshipsOptions* PixelSpaceshipsOptions::set_brightness_noise(float _noise)
{
	brightness_noise = _noise;
	if (brightness_noise < 0)
		brightness_noise = 0;
	if (brightness_noise > 1)
		brightness_noise = 1;
	return this;
}

float PixelSpaceshipsOptions::get_saturation()
{
	return saturation;
}

PixelSpaceshipsOptions* PixelSpaceshipsOptions::set_saturation(float _saturation)
{
	saturation = _saturation;
	if (saturation < 0)
		saturation = 0;
	if (saturation > 1)
		saturation = 1;
	return this;
}

float PixelSpaceshipsOptions::get_hue()
{
	return hue;
}

PixelSpaceshipsOptions* PixelSpaceshipsOptions::set_hue(float _hue)
{
	hue = _hue;
	if (hue < 0)
		hue = -1.0f;
	if (hue > 1)
		hue = 1;
	return this;
}

void PixelSpaceshipsOptions::setup_options(bool _colored, float _edge_brightness, float _col_variations, float _brightness_noise, float _saturation)
{
	colored = _colored;
	edge_brightnes = _edge_brightness;
	color_variation = _col_variations;
	brightness_noise = _brightness_noise;
	saturation = _saturation;
}

void PixelSpaceshipsOptions::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_colored"), &PixelSpaceshipsOptions::get_colored);
	ClassDB::bind_method(D_METHOD("set_colored", "is_colored"), &PixelSpaceshipsOptions::set_colored);

	ClassDB::bind_method(D_METHOD("get_edge_brightness"), &PixelSpaceshipsOptions::get_edge_brightness);
	ClassDB::bind_method(D_METHOD("set_edge_brightness", "edge_brightness"), &PixelSpaceshipsOptions::set_edge_brightness);

	ClassDB::bind_method(D_METHOD("get_color_variation"), &PixelSpaceshipsOptions::get_color_variation);
	ClassDB::bind_method(D_METHOD("set_color_variation", "color_variation"), &PixelSpaceshipsOptions::set_color_variation);

	ClassDB::bind_method(D_METHOD("get_brightness_noise"), &PixelSpaceshipsOptions::get_brightness_noise);
	ClassDB::bind_method(D_METHOD("set_brightness_noise", "brightness_noise"), &PixelSpaceshipsOptions::set_brightness_noise);

	ClassDB::bind_method(D_METHOD("get_saturation"), &PixelSpaceshipsOptions::get_saturation);
	ClassDB::bind_method(D_METHOD("set_saturation", "saturation"), &PixelSpaceshipsOptions::set_saturation);

	ClassDB::bind_method(D_METHOD("get_hue"), &PixelSpaceshipsOptions::get_hue);
	ClassDB::bind_method(D_METHOD("set_hue", "hue"), &PixelSpaceshipsOptions::set_hue);

	ClassDB::bind_method(D_METHOD("setup_options", "is_colored", "edge_brightness", "color_variations", "brightness_noise", "saturation"), &PixelSpaceshipsOptions::setup_options, DEFVAL(true), DEFVAL(0.15f), DEFVAL(0.2f), DEFVAL(0.8f), DEFVAL(0.7f));

}

PixelSpaceshipsOptions::PixelSpaceshipsOptions()
{
	colored = true;
	edge_brightnes = 0.3f;
	color_variation = 0.2f;
	brightness_noise = 0.3f;
	saturation = 0.5f;
	hue = -1.0f;
}

PixelSpaceshipsOptions::~PixelSpaceshipsOptions()
{

}



//////////////////////////////////////////////////////////////////////////
// PIXEL SPACESHIPS
//////////////////////////////////////////////////////////////////////////
int PixelSpaceships::get_data(MaskData _mask_data, int x, int y, int width)
{
	int idx = pos_to_idx(x, y, width);
	if (idx >= _mask_data.size() || idx < 0)
		idx = 0;

	return _mask_data[idx];
}


int PixelSpaceships::pos_to_idx(int x, int y, int width)
{
	return y*width + x;
}


Color PixelSpaceships::hsl2rgb(float h, float s, float l, Color rgb)
{
	int i;
	float f, p, q, t;
	i = Math::floor(h * 6);
	f = h * 6.0f - (float)i;
	p = l * (1.0f - s);
	q = l * (1.0f - f * s);
	t = l * (1.0f - (1.0f - f) * s);

	switch (i % 6)
	{
	case 0: rgb.r = l; rgb.g = t; rgb.b = p; break;
	case 1: rgb.r = q; rgb.g = l; rgb.b = p; break;
	case 2: rgb.r = p; rgb.g = l; rgb.b = t; break;
	case 3: rgb.r = p; rgb.g = q; rgb.b = l; break;
	case 4: rgb.r = t; rgb.g = p; rgb.b = l; break;
	case 5: rgb.r = l; rgb.g = p; rgb.b = q; break;
	}

	return rgb;
}

float PixelSpaceships::random()
{
	float ret = Math::random(0, 1);

	return ret;
}

void PixelSpaceships::generate_random_sample()
{
	for (int j = 0; j < HalfHeight; j++)
	{
		for (int i = 0; i < HalfWidth; i++)
		{
			int cell = get_data(ResultData, i, j, HalfWidth);

			if (cell == 1)
			{
				cell = cell*Math::round(random());
			}
			else if (cell == 2)
			{
				if (random() > 0.5)
				{
					cell = 1;
				}
				else
				{
					cell = -1;
				}
			}

			ResultData[pos_to_idx(i, j, HalfWidth)] = cell;
		}
	}
}

void PixelSpaceships::mirror_data()
{
	int w = Width;
	int h = Height;
	int tmpW = HalfWidth - 1;
	int tmpHH = HalfHeight - 1;
	MaskData MirroredData;
	MirroredData.resize(w*h);

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			int x = i <= tmpW ? i : tmpW - (i - tmpW) + 1;
			int y = j <= tmpHH ? j : tmpHH - (j - tmpHH) + 1;

			MirroredData[pos_to_idx(i, j, w)] = get_data(ResultData, x, y, HalfWidth);
		}
	}
	ResultData = MirroredData;
}

void PixelSpaceships::generate_edges()
{
	int w = Width;
	int h = Height;

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			if (get_data(ResultData, i, j, w) > 0)
			{
				if (j - 1 >= 0 && get_data(ResultData, i, j - 1, w) == 0)
				{
					ResultData[pos_to_idx(i, j - 1, w)] = -1;
				}
				if (j + 1 < h && get_data(ResultData, i, j + 1, w) == 0)
				{
					ResultData[pos_to_idx(i, j + 1, w)] = -1;
				}
				if (i - 1 >= 0 && get_data(ResultData, i - 1, j, w) == 0)
				{
					ResultData[pos_to_idx(i - 1, j, w)] = -1;
				}
				if (i + 1 < w && get_data(ResultData, i + 1, j, w) == 0)
				{
					ResultData[pos_to_idx(i + 1, j, w)] = -1;
				}
			}
		}
	}
}

void PixelSpaceships::generate_colors()
{
	ResultColors.clear();
	ResultColors.resize(ResultData.size());

	float IsVerticalGradient = random() > 0.5f;
	float Saturation = MAX(MIN(random()*PSOptions->get_saturation(), 1.0f), 0.0f);
	float hue = PSOptions->get_hue();

	if (hue < 0)
		hue = random();

	int ulen, vlen;
	if (IsVerticalGradient)
	{
		ulen = Height;
		vlen = Width;
	}
	else
	{
		ulen = Width;
		vlen = Height;
	}

	for (int u = 0; u < ulen; u++)
	{
		float IsNewColor = Math::abs((
			(random() * 2.0f - 1.0f)
			+ (random() * 2.0f - 1.0f)
			+ (random() * 2.0f - 1.0f)) / 3.0f);

		if (IsNewColor > (1 - PSOptions->get_color_variation()))
		{
			hue = random();
		}

		for (int v = 0; v < vlen; v++)
		{
			int val, idx;
			if (IsVerticalGradient)
			{
				idx = pos_to_idx(v, u, vlen);
			}
			else
			{
				idx = pos_to_idx(u, v, ulen);
			}
			val = ResultData[idx];

			Color rgb = Color(1, 1, 1, 1);

			if (val != 0)
			{
				if (PSOptions->get_colored())
				{
					float brightness =
						Math::sin((u / ulen)* 3.1415926f)*(1.0f - PSOptions->get_brightness_noise())
						+ random()*PSOptions->get_brightness_noise();

					rgb = hsl2rgb(hue, Saturation, brightness, rgb);
					if (val == -1)
					{
						rgb.r *= PSOptions->get_edge_brightness();
						rgb.g *= PSOptions->get_edge_brightness();
						rgb.b *= PSOptions->get_edge_brightness();
					}
				}
				else
				{
					if (val == -1)
					{
						rgb.r = 0;
						rgb.g = 0;
						rgb.b = 0;
					}
				}
			}
			else
			{
				rgb.a = 0;
			}

			ResultColors[idx] = rgb;
		}
	}
}

Ref<ImageTexture> PixelSpaceships::make_texture()
{
	Image* img = memnew(Image(Width, Height, true, Image::Format::FORMAT_RGBA8));
	ImageTexture* tex = memnew(ImageTexture());

	img->lock();
	for (int j = 0; j < Height; j++)
	{
		for (int i = 0; i < Width; i++)
		{
			img->set_pixel(i, j, ResultColors[pos_to_idx(i, j, Width)]);
		}
	}
	img->unlock();

	tex->create_from_image(img, ImageTexture::Flags::FLAG_ANISOTROPIC_FILTER || ImageTexture::Flags::FLAG_MIPMAPS);

	return tex;
}
Ref<ImageTexture> PixelSpaceships::generate_texture(Ref<PixelSpaceshipsMask> _mask, Ref<PixelSpaceshipsOptions> _options, int _seed)
{
	if (_mask == 0 || _options == 0)
		return 0;

	generate(_mask, _options, _seed);
	
	generate_colors();
	return make_texture();
}

void PixelSpaceships::generate(Ref<PixelSpaceshipsMask> _mask, Ref<PixelSpaceshipsOptions> _options, int _seed)
{
	ERR_FAIL_COND(_mask == 0);
	ERR_FAIL_COND(_options == 0);

	Seed = _seed;
	if (Seed == 0)
		Math::randomize();
	else
		Math::seed(Seed);

	PSMask = _mask;
	PSOptions = _options;
	ResultData = PSMask->get_data();

	HalfWidth = PSMask->get_size().width;
	HalfHeight = PSMask->get_size().height;
	Width = PSMask->get_mirror_x() ? HalfWidth * 2 : HalfWidth;
	Height = PSMask->get_mirror_y() ? HalfHeight * 2 : HalfHeight;

	generate_random_sample();
	mirror_data();
	generate_edges();
}

Ref<PixelSpaceshipsMask> PixelSpaceships::get_mask_object()
{
	return PSMask;
}

Ref<PixelSpaceshipsOptions> PixelSpaceships::get_options_object()
{
	return PSOptions;
}

Array PixelSpaceships::get_mask_matrix()
{
	Array matrix;
	if (ResultData.size() != Height*Width)
		return matrix;

	for (int j = 0; j < Height; j++)
	{
		Array newArr;
		for (int i = 0; i < Width; i++)
		{
			newArr.append(ResultData[pos_to_idx(i, j, Width)]);
		}
		matrix.append(newArr);
	}

	return matrix;
}

Array PixelSpaceships::get_colors_matrix()
{
	Array matrix;
	if (ResultColors.size() != Height*Width)
		return matrix;

	for (int j = 0; j < Height; j++)
	{
		Array newArr;
		for (int i = 0; i < Width; i++)
		{
			newArr.append(ResultColors[pos_to_idx(i, j, Width)]);
		}
		matrix.append(newArr);
	}

	return matrix;
}

void PixelSpaceships::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("generate_texture", "pixel_spaceship_mask", "pixel_spaceship_options", "seed"), &PixelSpaceships::generate_texture, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("generate", "pixel_spaceship_mask", "pixel_spaceship_options", "seed"), &PixelSpaceships::generate, DEFVAL(0));

	ClassDB::bind_method(D_METHOD("get_mask_object"), &PixelSpaceships::get_mask_object);
	ClassDB::bind_method(D_METHOD("get_options_object"), &PixelSpaceships::get_options_object);

	ClassDB::bind_method(D_METHOD("get_mask_matrix"), &PixelSpaceships::get_mask_matrix);
	ClassDB::bind_method(D_METHOD("get_colors_matrix"), &PixelSpaceships::get_colors_matrix);
}

PixelSpaceships::PixelSpaceships()
{
	ResultData = MaskData();
	ResultColors = TextureColors();
	Width = 0;
	Height = 0;
	HalfWidth = 0;
	HalfHeight = 0;
	Seed = 0;
}

PixelSpaceships::~PixelSpaceships()
{

}

