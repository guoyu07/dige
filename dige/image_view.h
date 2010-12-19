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
/*!
**\file   image_view.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Aug 21 12:53:21 2010
**
**\brief  image_view header.
**
**
*/

#ifndef DIGE_IMAGE_VIEW_H_
# define DIGE_IMAGE_VIEW_H_

# include <map>
# include <string>

# include <dige/displaylist.h>

namespace dg
{
  // Forward declaration.
  class gl_widget;

  /*!
  ** The image_view class allow to display the content of a displaylist
  ** in an OpenGL context.
  ** It listen to the image_view event (exposure, resizing...).
  */
  class image_view
  {
  public:
    /*!
    ** Constructor.
    ** Initialize a new image_view.
    **
    ** \param title The title of the image_view
    ** \param width width in pixels.
    ** \param height height in pixels.
    **
    */
    image_view(const std::string& title, unsigned width = 800, unsigned height = 600);
    /// Destructor.
    ~image_view();


    /// \return width of the image_view.
    unsigned width() const;

    /// \return height of the image_view.
    unsigned height() const;

    /*!
    ** Set \p l to be drawn in the image_view.
    **
    ** \param l a displaylist
    **
    ** \return the image_view.
    */
    image_view& operator<<=(displaylist& l);

    /// Refresh the image_view content.
    void refresh();

    gl_widget* widget();

    /// Displaylist accessor.
    displaylist& dlist();

    /// Set unresizable
    void set_unresizable();

    point2d<int> selected_coords() const;

    /*!
    ** Dump the image_view content to \p buffer.
    ** Resize it if needed
    **
    ** \param buffer
    ** \param buffer_size
    ** \param buffer_width
    ** \param buffer_height
    **
    ** \todo The size of the buffer should stay constant even during
    ** image_view resizing. We may need to use opengl FBO.
    */
    void dump_rgb_frame_buffer(char*& buffer,
                                      unsigned& buffer_size,
                                      unsigned& buffer_width,
                                      unsigned& buffer_height);

    /// Associate all the created image_views with theis names.
    static const std::map<const std::string, image_view*>& image_views();

  private:
    gl_widget* currentWidget_; /*!< Underlying qt widget. */
    displaylist dlist_;         /*!< Current displaylist. */

    friend image_view& display(const std::string& title, unsigned width,
                           unsigned height);
  };

  /*!
  ** image_view factory. Retrieve the image_view named \p title. Create it if
  ** it doesn't exists.
  **
  ** \param width image_view width in pixel.
  ** \param height image_view height in pixel.
  **
  ** \return the image_view.
  */
  image_view& display(const std::string& title, unsigned width = 400,
                      unsigned height = 400);

} // end of namespace dg.

#endif
