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
**\file   push_button.cpp
**\author Matthieu Garrigues <matthieu.garrigues@gmail.com>
**\date   Wed Jan 26 21:55:12 2011
**
**\brief  push_button implementation
**
**
*/

# include <map>
# include <string>

# include <QPushButton>

# include <dige/named_object.h>
# include <dige/need_qapp.h>
# include <dige/widgets/push_button.h>


namespace dg
{

  namespace widgets
  {

    push_button::push_button(const std::string& title, bool checkable)
    {
      need_qapp();

      button_ = new QPushButton();
      button_->setText(QString::fromStdString(title));
      button_->setCheckable(checkable);
    }

    push_button::~push_button()
    {
      delete button_;
    }

    QWidget*
    push_button::widget() const
    {
      return button_;
    }

    event::any_event
    push_button::click()
    {
      return dg::event::click(button_);
    }

    bool
    push_button::is_checked()
    {
      return button_->isChecked();
    }


    push_button&
    PushButton(const std::string& title, bool checkable)
    {
      return named_instance<push_button>(title, checkable);
    }

  } // end of namespace widgets.

} // end of namespace dg.

