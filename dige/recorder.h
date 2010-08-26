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
**\file   recorder.h
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Thu Aug 26 18:36:08 2010
**
**\brief  recorder header.
**
**
*/

#ifndef DIGE_RECORDER_H_
# define DIGE_RECORDER_H_

# include <map>
# include <fstream>
# include <boost/shared_ptr.hpp>

extern "C"
{
# include <libavcodec/avcodec.h>
# include <libswscale/swscale.h>
# include <libavcodec/opt.h>
}
# include <dige/window.h>

namespace dg
{

  /*!
  ** Recorder build an avi video from the content of the windows
  ** passed by recorder::operator<<=.
  **
  */
  class recorder
  {
    /*!
    ** Private constructor.
    ** Build a new recorder that will record the video \p output_video_filepath.
    **
    ** \param video_output_filepath output video filepath.
    ** \note Use record to create a new recorder.
    **
    */
    inline recorder(const std::string& output_video_filepath);

  public:
    /*!
    ** Destructor.
    **
    ** Close the video.
    */
    inline ~recorder();

    /*!
    ** Append a capture of \p w to the video.
    **
    ** \param w a window.
    */
    inline void operator<<=(window& w);

    /// Associate all the created recorder with theirs video filepath.
    static inline std::map<const std::string, boost::shared_ptr<recorder> >& recorders();

  private:
    /*!
    ** Initialize the window
    **
    ** \param width
    ** \param height
    */
    inline void init_context(unsigned width, unsigned height);

    /// Associate all the created recorder with theirs video filepath.
    static std::map<const std::string, boost::shared_ptr<recorder> > recorders_;

    /// Remember if ffmpeg has been initialized.
    static bool ffmpeg_initialized_;

    AVCodec* avcodec_;          /*!< ffmpeg codec. */
    AVCodecContext* avcontext_; /*!< ffmpeg context. */
    SwsContext* swcontext_;     /*!< swscale context. */
    AVFrame* yuvframe_;         /*!< current yuv frame. */
    AVFrame* rgbframe_;         /*!< current rgb frame. */
    uint8_t* video_buffer_;     /*!< encoding buffer. */
    int video_buffer_size_;     /*!< encoding buffer size. */
    std::ofstream output_;      /*!< output stream. */
    bool init_failed_;          /*!< remember a failed initialization. */
    char* window_capture_;      /*!< rgbframe buffer use to capture windows content. */
    unsigned window_capture_size_; /*!< rgbframe buffer size. */
    unsigned window_capture_width_; /*!< rgbframe width. */
    unsigned window_capture_height_; /*!< rgbframe height. */

    friend recorder& record(const std::string& video_filepath);
  };

  /*!
  ** recorder factory. Retrieve the recorder recording \p
  ** video_filepath. Create it if it doesn't exists.
  **
  ** \param video_filepath the output video filepath.
  **
  ** \return the recorder.
  */
  inline recorder& record(const std::string& video_filepath);

} // end of namespace dg.

# include <dige/recorder.hpp>

#endif
