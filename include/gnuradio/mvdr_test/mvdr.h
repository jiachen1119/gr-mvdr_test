/* -*- c++ -*- */
/*
 * Copyright 2023 Kepeng Luan.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_MVDR_TEST_MVDR_H
#define INCLUDED_MVDR_TEST_MVDR_H

#include <gnuradio/block.h>
#include <gnuradio/mvdr_test/api.h>

namespace gr {
namespace mvdr_test {

/*!
 * \brief <+description of block+>
 * \ingroup mvdr_test
 *
 */
class MVDR_TEST_API mvdr : virtual public gr::block
{
public:
    typedef std::shared_ptr<mvdr> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of mvdr_test::mvdr.
     *
     * To avoid accidental use of raw pointers, mvdr_test::mvdr's
     * constructor is in a private implementation
     * class. mvdr_test::mvdr::make is the public interface for
     * creating new instances.
     */
    static sptr make(int num_inputs,
                     float sampling_frequency,
                     int taps,
                     int target_prn,
                     int ms_to_process);
};

} // namespace mvdr_test
} // namespace gr

#endif /* INCLUDED_MVDR_TEST_MVDR_H */
