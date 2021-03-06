// Copyright (C) 2010 Matthieu Garrigues
//
// This file is part of dige.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include <cstdlib>
#include <ctime>

// Dige includes.
#include <dige/window.h>
#include <dige/widgets/image_view.h>
#include <dige/image.h>
#include <dige/pick_coords.h>
#include <dige/event/wait.h>
#include <dige/event/click.h>
#include <dige/event/key_release.h>

// A simple rgb image type
struct rgb_image
{
  rgb_image(unsigned w, unsigned h)
    : width(w),
      height(h),
      image_size(w * h * 3)
  {
    data = new unsigned char[image_size];
  }

  ~rgb_image()
  {
    delete[] data;
  }

  unsigned width;
  unsigned height;
  unsigned image_size;
  unsigned char* data;
};

namespace dg
{
  // Adapt our rgb_image type into the dige image type.
  image<trait::format::rgb, unsigned char>
  adapt(const rgb_image& i)
  {
    return image<trait::format::rgb, unsigned char>
      (i.width, i.height, i.data);
  }
}

int main()
{
  using dg::display; // Dige display.
  using dg::dl; // Dige list starter

  srand(time(0));
  rgb_image img(200, 200);

  unsigned t = clock();
  //  while (clock() - t < 5 * CLOCKS_PER_SEC)

  int x = 0, y = 0;

  dg::Window("Random test [Press enter to quit]", 500, 300) <<=
    (dg::hbox_start -
     display("random") -
     dg::hbox_end);

  display("random") <<= dl() - img;

  //  while (true)
  for_each_event_until(e, dg::click() |
                    dg::key_release(dg::key_e) |
                    dg::key_release(dg::key_r) |
                    dg::key_release(dg::key_right) |
                    dg::key_release(dg::key_y),
                    dg::key_release(dg::key_return))
  {
    for (unsigned i = 0; i < img.image_size; i++)
      img.data[i] = rand();

    dg::pick_coords("random", x, y);

    if (x >= 0)
    {
      for (unsigned i = 0; i < 200; i++)
      {
        img.data[y * 200 * 3 + i * 3 + 0 ] = 1;
        img.data[y * 200 * 3 + i * 3 + 1 ] = 2;
        img.data[y * 200 * 3 + i * 3 + 2 ] = 3;
      }
      for (unsigned i = 0; i < 200; i++)
      {
        img.data[i * 200 * 3 + x * 3 + 0 ] = 1;
        img.data[i * 200 * 3 + x * 3 + 1 ] = 2;
        img.data[i * 200 * 3 + x * 3 + 2 ] = 3;
      }

    }
    // Display in a 300*200 window called "random" 3 copy of our image.
    // It will looks like:
    //
    //  |-------------|
    //  | img     img |
    //  |             |
    //  |             |
    //  |     img     |
    //  |-------------|
    //
    //  std::cout << " create dl "  << std::endl;
    ImageView("random", 300, 200)
      <<=
      dl() - img - img +
                    img;

    //      <<= dl() - img;

    // int x = 0, y = 0;
    // dg::pick_coords("random", x, y);
    // std::cout << x << ' ' << y << std::endl;
  }

  // Pause the program on the last image.
  //  dg::pause();
}
