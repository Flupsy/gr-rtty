/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef INCLUDED_RTTY_decode_FF_H
#define INCLUDED_RTTY_decode_FF_H

#include <gnuradio/block.h>

class rtty_decode_ff;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr::blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<rtty_decode_ff> rtty_decode_ff_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of rtty_decode_ff.
 *
 * To avoid accidental use of raw pointers, rtty_decode_ff's
 * constructor is private.  rtty_make_decode_ff is the public
 * interface for creating new instances.
 */
rtty_decode_ff_sptr rtty_make_decode_ff (float rate, float baud, bool polarity);

/*!
 * \brief decode a stream of floats to rtty char.
 * \ingroup block
 *
 * \sa rtty_decode2_ff for a version that subclasses gr_sync_block.
 */
class rtty_decode_ff : public gr::block
{
private:
  // The friend declaration allows rtty_make_decode_ff to
  // access the private constructor.

  friend rtty_decode_ff_sptr rtty_make_decode_ff (float rate, float baud, bool polarity);

  rtty_decode_ff (float rate, float baud, bool polarity);  	// private constructor
  
  enum { WAITING_FOR_START, DATA, LOOKING_FOR_STOP } state;
  enum { LETTERS, FIGURES } charset;
  float _baud;
  float _rate;
  bool mark, space;
  float _spb;
  int datapos;

 public:
  ~rtty_decode_ff ();	// public destructor
  void forecast(int noutput_items, gr_vector_int &ninput_items_required);

  // Where all the action really happens

  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
		    
};

#endif /* INCLUDED_RTTY_decode_FF_H */
