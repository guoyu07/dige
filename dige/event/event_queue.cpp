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
**\file   event_queue.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Sat Feb 26 19:55:57 2011
**
**\brief  event_queue implementation.
**
**
*/

# include <QApplication>
# include <dige/event/make_event.h>
# include <dige/event/event_queue.h>
# include <dige/process_events.h>

namespace dg
{

  namespace event
  {

    event_queue::event_queue(const any_event_set& s)
      : s_(s)
    {
      QApplication::instance()->installEventFilter(this);
    }

    event_queue::event_queue(const event_queue& q)
      : QObject(),
        queue_(q.queue_),
        s_(q.s_)
    {
      QApplication::instance()->installEventFilter(this);
    }

    event_queue&
    event_queue::operator=(const event_queue& q)
    {
      queue_ = q.queue_;
      s_ = q.s_;
      return *this;
    }

    event_queue::event_queue(const any_event& e)
      : s_(any_event(e))
    {
      QApplication::instance()->installEventFilter(this);
    }


    event_queue::~event_queue()
    {
      QApplication::instance()->removeEventFilter(this);
    }

    void
    event_queue::clear()
    {
      while (!queue_.empty())
        queue_.pop();
    }

    bool
    event_queue::is_empty() const
    {
      QApplication::processEvents();
      QApplication::sendPostedEvents();
      return queue_.empty();
    }

    unsigned
    event_queue::size() const
    {
      return queue_.size();
    }

    any_event
    event_queue::pop_front()
    {
      assert(!is_empty());
      QApplication::processEvents();
      QApplication::sendPostedEvents();

      any_event r = queue_.front();
      queue_.pop();
      return r;
    }

    bool
    event_queue::eventFilter(QObject *obj, QEvent *event)
    {
      any_event e = make_event(obj, event);

      if (dg::event::event_match(s_, e))
      {
        queue_.push(e);
        return false;
      }

      return false;
    }

  } // end of namespace event.

} // end of namespace dg.
